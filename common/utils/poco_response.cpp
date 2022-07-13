#include "poco_response.h"

void prepare_server_response(Poco::Net::HTTPServerResponse& response)
{
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");
}
