
#include <regex>
#include <sstream>

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
    }

    void RequestHandlerDB::handle_request(const Request& req, Reply& rep)
    {
        std::string result = DefaultResult;

        std::string decodedUri = req.uri;

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
                decodedUri = std::regex_replace(decodedUri, std::regex("%20"), " ");

                auto queryResult = db.executeQuery(decodedUri);
                if (queryResult)
                {
                    result = queryResult->toString();
                }
            }
        }

        std::stringstream ss;
        ss << "<html>";
        ss << "<head><title>Query executed</title></head>";
        ss << "<body><h1>" << result << "</title></head>";
        ss << "</html>";

        // Fill out the reply to be sent to the client.
        rep.status = Reply::StatusType::ok;

        rep.content = ss.str();
        rep.headers.resize(2);
        rep.headers[0].name = "Content-Length";
        rep.headers[0].value = std::to_string(rep.content.size());
        rep.headers[1].name = "Content-Type";
        rep.headers[1].value = MimeTypes::extension_to_type("html");
	}
}
