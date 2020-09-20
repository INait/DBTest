#pragma once

#include <string>
#include <vector>
#include <boost/asio/buffer.hpp>

namespace DBProject
{
    /// A reply to be sent to a client.
    struct Reply
    {
        /// The content to be sent in the reply.
        std::string content;

        /// Convert the reply into a vector of buffers. The buffers do not own the
        /// underlying memory blocks, therefore the reply object must remain valid and
        /// not be changed until the write operation has completed.
        std::vector<boost::asio::const_buffer> to_buffers();

        /// Get a stock reply.
        static Reply stock_reply();
    };
};

