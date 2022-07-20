#include "handlers_factory.h"

Poco::Net::HTTPRequestHandler * HandlersFactory::createRequestHandler(const Poco::Net::HTTPServerRequest &request)
{
    auto findIndex = routes.find(request.getURI());
    if (findIndex == routes.end())
        return new NotFound();

    return getHandler(findIndex->second);
}

HandlersFactory::HandlersFactory()
{
    routes["/"] = Handlers::RootHandler;
    routes["/auth"] = Handlers::AuthHandler;
    routes["/shutdown"] = Handlers::ShutdownHandler;
}

Poco::Net::HTTPRequestHandler * HandlersFactory::getHandler(Handlers handler)
{
    // Should be useful to make shure that all routes have handlers
    assert((Handlers::HandlersCount == routes.size()) && "Switch case for routes doesn't match the number of routes");

    switch (handler) {
        case Handlers::RootHandler:
            return new Root();
        case Handlers::AuthHandler:
            return new Auth();
        case Handlers::ShutdownHandler:
            return new Shutdown();
        default:
            return new NotFound();
    }
}
