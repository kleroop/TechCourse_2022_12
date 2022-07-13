#include "handlers_factory.h"

Poco::Net::HTTPRequestHandler * HandlersFactory::createRequestHandler(const Poco::Net::HTTPServerRequest &request)
{
    auto findIndex = routes.find(request.getURI());
    if (findIndex == routes.end())
        return nullptr;

    return getHandler(findIndex->second);
}

HandlersFactory::HandlersFactory()
{
    routes["/"] = Handlers::RootHandler;
    routes["/shutdown"] = Handlers::ShutdownHandler;
}

Poco::Net::HTTPRequestHandler * HandlersFactory::getHandler(Handlers handler)
{
    switch (handler) {
        case Handlers::RootHandler:
            return new Root();
    }
}
