
#include <regex>

#include "network/request.h"
#include "network/reply.h"
#include "network/mimeTypes.h"

#include "query.h"
#include "dbRequestHandler.h"

namespace DBProject
{
    void RequestHandlerDB::handle_request(const Request& req, Reply& rep)
    {
        db.executeQuery(req.uri);

        // Fill out the reply to be sent to the client.
        rep.status = Reply::StatusType::ok;

        const char result[] =
            "<html>"
            "<head><title>Query executed</title></head>"
            "<body><h1>Query executed</h1></body>"
            "</html>";

        rep.content = result;
        rep.headers.resize(2);
        rep.headers[0].name = "Content-Length";
        rep.headers[0].value = std::to_string(rep.content.size());
        rep.headers[1].name = "Content-Type";
        rep.headers[1].value = MimeTypes::extension_to_type("html");
	}
}
