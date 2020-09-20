#pragma once

#include <string>

namespace DBProject
{
	/// A request received from a client.
	struct Request
	{
		std::string method;
		std::string uri;
	};
};

