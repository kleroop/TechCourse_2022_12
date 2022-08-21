#include "server.h"

int Server::main(const std::vector<std::string> &args)
{
    Poco::Net::HTTPServer server(handlersFactory, serverSocket, serverParams);
    DAL::Init();
    server.start();

    std::cout << "Server successfully running on " << server.port() << " port" << "\n";
    std::cout << "To shutdown server call 'http://localhost:5000/shutdown' or CTR + C in terminal (SIGTERM)" << "\n";

    waitForTerminationRequest();
    server.stop();
    DAL::Quit();

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
