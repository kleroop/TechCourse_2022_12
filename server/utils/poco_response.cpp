#include "poco_response.h"

void prepareServerResponse(Poco::Net::HTTPServerResponse& response)
{
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");
}
