#pragma once

#include <memory>
#include <string>

#include <boost/asio.hpp>

namespace DBProject
{
	class Server
	{
	public:
		Server(const Server&) = delete;
		Server& operator=(const Server&) = delete;

		/// Construct the server to listen on the specified TCP address and port, and
		/// serve up files from the given directory.
		explicit Server(const std::string& address, const std::string& port,
			const std::string& doc_root);

		/// Run the server's io_context loop.
		void run();

	private:
		/// Perform an asynchronous accept operation.
		void do_accept();

		/// Wait for a request to stop the server.
		void do_await_stop();

		/// The io_context used to perform asynchronous operations.
		boost::asio::io_context io_context_;

		/// The signal_set is used to register for process termination notifications.
		boost::asio::signal_set signals_;

		/// Acceptor used to listen for incoming connections.
		boost::asio::ip::tcp::acceptor acceptor_;
	};
};

