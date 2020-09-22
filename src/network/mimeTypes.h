#pragma once

#include <string>
#include <vector>
#include <boost/asio/buffer.hpp>

namespace DBProject
{
	namespace MimeTypes {

		/// Convert a file extension into a MIME type.
		std::string extension_to_type(const std::string& extension);

	} // namespace MimeTypes
};

