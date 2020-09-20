
#include "connectionManager.h"

namespace DBProject
{
    ConnectionManager::ConnectionManager()
    {
    }

    void ConnectionManager::start(ConnectionPtr c)
    {
        connections_.insert(c);
        c->start();
    }

    void ConnectionManager::stop(ConnectionPtr c)
    {
        connections_.erase(c);
        c->stop();
    }

    void ConnectionManager::stop_all()
    {
        for (auto c : connections_)
            c->stop();
        connections_.clear();
    }
}
