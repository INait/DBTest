#pragma once

#include <memory>
#include <string>

#include "db.h"
#include "network/requestHandler.h"

namespace DBProject
{
	class RequestHandlerDB : public RequestHandler
	{
	public:
		RequestHandlerDB(DB& db_)
			: db(db_)
		{}

		void handle_request(const Request& req, Reply& rep) override;

	private:
		DB& db;
	};
};

