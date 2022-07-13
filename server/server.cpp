#include "server.h"

int Server::main(const std::vector<std::string> &args)
{
    Poco::Net::HTTPServer server(handlersFactory, serverSocket, serverParams);
    server.start();

    std::cout << "Server successfully running on " << server.port() << " port" << "\n";

    waitForTerminationRequest();
    server.stopAll();

    return 0;
}

Server::Server() : handlersFactory(new HandlersFactory()), serverParams(new Poco::Net::HTTPServerParams()), serverSocket(PORT)
{
    serverParams->setMaxQueued(MAX_QUEUED);
    serverParams->setMaxThreads(MAX_THREADS);
}

Server::~Server()
{
    delete handlersFactory;
}
