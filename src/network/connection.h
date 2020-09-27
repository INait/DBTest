#pragma once

#include <memory>
#include <string>

#include <boost/asio.hpp>
#include "requestHandler.h"
#include "request.h"
#include "reply.h"
#include "requestParser.h"

namespace DBProject
{
    class ConnectionManager;

    /// Represents a single connection from a client.
    class Connection
        : public std::enable_shared_from_this<Connection>
    {
    public:
        Connection(const Connection&) = delete;
        Connection& operator=(const Connection&) = delete;

        /// Construct a connection with the given socket.
        explicit Connection(boost::asio::ip::tcp::socket socket,
            ConnectionManager& manager, RequestHandler& handler);

        /// Start the first asynchronous operation for the connection.
        void start();

        /// Stop all asynchronous operations associated with the connection.
        void stop();

    private:
        /// Perform an asynchronous read operation.
        void do_read();

        /// Perform an asynchronous write operation.
        void do_write();

        /// Socket for the connection.
        boost::asio::ip::tcp::socket socket_;

        /// The manager for this connection.
        ConnectionManager& connection_manager_;

        /// The handler used to process the incoming request.
        RequestHandler& request_handler_;

        /// Buffer for incoming data.
        std::array<char, 65536> buffer_;

        /// The incoming request.
        Request request_;

        /// The parser for the incoming request.
        RequestParser request_parser_;

        /// The reply to be sent back to the client.
        Reply reply_;
    };

    using ConnectionPtr = std::shared_ptr<Connection>;
};

