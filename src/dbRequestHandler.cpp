
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
        static constexpr char DefaultResult[] = "Query executed";
    }

    void RequestHandlerDB::handle_request(const Request& req, Reply& rep)
    {
        std::string result = DefaultResult;

        std::string decodedUri = req.uri;
 
        decodedUri = std::regex_replace(decodedUri, std::regex("/"), "");
        decodedUri = std::regex_replace(decodedUri, std::regex("%20"), " ");

        auto queryResult = db.executeQuery(decodedUri);
        if (queryResult)
        {
            result = queryResult->toString();
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
