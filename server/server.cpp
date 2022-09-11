#include "server.h"

int Server::main(const std::vector<std::string> &argv)
{
    if (argv.size() != 5) {
        puts("Can't connect to db, required command line options are: host port username dbname "
             "password");
        return EXIT_FAILURE;
    }
    string host = argv[0], port = argv[1], username = argv[2], dbname = argv[3], password = argv[4];
    Poco::Net::HTTPServer server(handlersFactory, serverSocket, serverParams);
    if (DAL::Init(host, port, username, dbname, password) != DAL::DAL_OK) {
        puts("Couldn't init DAL connection");
        return EXIT_FAILURE;
    }
    server.start();

    std::cout << "Server successfully running on " << server.port() << " port"
              << "\n";
    std::cout << "To shutdown server call 'http://localhost:5000/shutdown' or CTR + C in terminal "
                 "(SIGTERM)"
              << "\n";

    waitForTerminationRequest();
    server.stop();
    DAL::Quit();

    return 0;
}

Server::Server()
    : handlersFactory(new HandlersFactory()),
      serverParams(new Poco::Net::HTTPServerParams()),
      serverSocket(PORT)
{
    serverParams->setMaxQueued(MAX_QUEUED);
    serverParams->setMaxThreads(MAX_THREADS);
}

Server::~Server()
{
    delete handlersFactory;
}
