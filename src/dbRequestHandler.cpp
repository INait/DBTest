
#include <regex>

#include "network/request.h"
#include "network/reply.h"
#include "network/mimeTypes.h"

#include "query.h"
#include "dbRequestHandler.h"

namespace DBProject
{
    namespace
    {
        static constexpr char DefaultResult[] = "Bad request";

        void decodeUriSpecialSymbols(std::string& uri)
        {
            uri = std::regex_replace(uri, std::regex("%20"), " ");
            uri = std::regex_replace(uri, std::regex("%2C"), ",");
            uri = std::regex_replace(uri, std::regex("%2C"), ",");
            uri = std::regex_replace(uri, std::regex("%28"), "(");
            uri = std::regex_replace(uri, std::regex("%29"), ")");
            uri = std::regex_replace(uri, std::regex("%3B"), ";");
            uri = std::regex_replace(uri, std::regex("%2A"), "*");
        }
    }

    void RequestHandlerDB::handle_request(const Request& req, Reply& rep)
    {
        std::string result = DefaultResult;

        std::string decodedUri = req.uri;

        if (req.method == "POST")
        {
            auto slashIdx = decodedUri.find("/");
            decodedUri.erase(0, slashIdx + 1);

            auto nextSlashIdx = decodedUri.find("/");
            auto requestString = decodedUri.substr(0, nextSlashIdx);
            if (requestString == "import")
            {
                auto doubleDotsIndex = decodedUri.find(":");
                std::string tableName = decodedUri.substr(doubleDotsIndex + 1);

                db.importTableFromCSV(tableName, req.data);
                result = "Success";
            }
        }
        else if (req.method == "GET")
        {
            auto slashIdx = decodedUri.find("/");
            auto questionMarkIdx = decodedUri.find("?");
            auto requestString = decodedUri.substr(slashIdx + 1, questionMarkIdx - 1);
            if (requestString == "query")
            {
                auto equalSignIdx = decodedUri.find_first_of("=");
                auto firstParam = decodedUri.substr(questionMarkIdx + 1, equalSignIdx - questionMarkIdx - 1);
                if (firstParam == "sql")
                {
                    decodedUri = decodedUri.substr(equalSignIdx + 1);
                    decodeUriSpecialSymbols(decodedUri);

                    auto queryResult = db.executeQuery(decodedUri);
                    if (queryResult)
                    {
                        result = queryResult->toString();
                    }
                }
            }
        }

        // Fill out the reply to be sent to the client.
        rep.status = Reply::StatusType::ok;

        rep.content = result;
        rep.headers.resize(2);
        rep.headers[0].name = "Content-Length";
        rep.headers[0].value = std::to_string(rep.content.size());
        rep.headers[1].name = "Content-Type";
        rep.headers[1].value = MimeTypes::extension_to_type("plaintext");
	}
}
