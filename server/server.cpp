#include "server.h"

int Server::main(const std::vector<std::string> &args)
{
    Poco::Net::HTTPServer server(handlersFactory, serverSocket, serverParams);
    server.start();

    std::cout << "Server successfully running on " << server.port() << " port" << "\n";
    std::cout << "To shutdown server call 'http://localhost:5000/shutdown'" << "\n";

    waitForTerminationRequest();
    server.stop();

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
