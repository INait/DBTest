
#include "reply.h"

namespace DBProject
{
	Reply Reply::stock_reply()
	{
		Reply rep;
		rep.content = "REPLY";
		return rep;
	}


	std::vector<boost::asio::const_buffer> Reply::to_buffers()
	{
		std::vector<boost::asio::const_buffer> buffers;
		buffers.push_back(boost::asio::buffer(content));
		return buffers;
	}
}
