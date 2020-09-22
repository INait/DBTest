#pragma once

#include <string>

namespace DBProject
{
	struct Reply;
	struct Request;

	/// The common handler for all incoming requests.
	class RequestHandler
	{
	public:

		RequestHandler() = default;
		virtual ~RequestHandler() = default;

		RequestHandler(const RequestHandler&) = delete;
		RequestHandler& operator=(const RequestHandler&) = delete;

		/// Handle a request and produce a reply.
		virtual void handle_request(const Request& req, Reply& rep) = 0;
	};

};

