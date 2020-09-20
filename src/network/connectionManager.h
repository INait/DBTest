#pragma once

#include <set>
#include "connection.h"

namespace DBProject
{
	/// Manages open connections so that they may be cleanly stopped when the server
	/// needs to shut down.
	class ConnectionManager
	{
	public:
		ConnectionManager(const ConnectionManager&) = delete;
		ConnectionManager& operator=(const ConnectionManager&) = delete;

		/// Construct a connection manager.
		ConnectionManager();

		/// Add the specified connection to the manager and start it.
		void start(ConnectionPtr c);

		/// Stop the specified connection.
		void stop(ConnectionPtr c);

		/// Stop all connections.
		void stop_all();

	private:
		/// The managed connections.
		std::set<ConnectionPtr> connections_;
	};

};

