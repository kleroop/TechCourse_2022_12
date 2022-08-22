#include "categories.h"
#include "auth_utils.h"
#include "models/categories_model.h"
#include "categories_utils.h"

void GetCategories::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    AUTH

    // TODO: add macro for admin only users

    CategoriesTree categoriesTree = fromDal();
    CategoriesTreeResponse categoriesTreeResponse(categoriesTree);

    ostream << categoriesTreeResponse.serialize().dump();
}
