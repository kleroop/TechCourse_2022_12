#include "categories.h"
#include "auth_utils.h"
#include "models/categories_model.h"
#include "categories_utils.h"
#include "poco_request.h"

void GetCategories::handleRequest(Poco::Net::HTTPServerRequest &request,
                                  Poco::Net::HTTPServerResponse &response)
{
    AUTH

            // TODO: add macro for admin only users

            CategoriesTree categoriesTree = fromDal();
    CategoriesTreeResponse categoriesTreeResponse(categoriesTree);

    ostream << categoriesTreeResponse.serialize().dump();
}

void UpdateCategories::handleRequest(Poco::Net::HTTPServerRequest &request,
                                     Poco::Net::HTTPServerResponse &response)
{
    AUTH

            CategoriesTree categoriesTree;
    UpdateCategoriesRequest updateCategoriesRequest(categoriesTree);

    json requestData = toJson(request.stream());
    updateCategoriesRequest.deserialize(requestData);

    if (updateCategoriesRequest.error != "") {
        responseJson["status"] = 400;
        responseJson["data"] = { { "message",
                                   "Deserialization error: " + updateCategoriesRequest.error } };

        ostream << responseJson.dump();
        return;
    }

    DAL::Category cDAL;
    auto categoriesDAL = cDAL.Select("", {});

    for (auto &categoryDAL : categoriesDAL)
        categoryDAL.Delete();

    for (auto &category : updateCategoriesRequest.categoriesTree.categories) {
        DAL::Category categoryDAL(category.title, category.isHidden);
        categoryDAL.Create();

        for (auto &subCategory : category.children) {
            DAL::SubCategory subCategoryDAL(subCategory.title, subCategory.isHidden, &categoryDAL);
            subCategoryDAL.Create();

            for (auto &team : subCategory.children) {
                ICategory teamm = team;
                team.dateCreated = fixDate(team.dateCreated);
                auto dalIcon = Poco::Nullable<Poco::Data::BLOB>();
                if (!team.icon.empty()){
                    dalIcon.assign(team.icon);
                }
                DAL::Team teamDAL(team.title, team.isHidden, &subCategoryDAL, team.location,
                                  Poco::DateTime(team.dateCreated),dalIcon);
                teamDAL.Create();
            }
        }
    }

    CategoriesTree categoriesTreeUpdated = fromDal();
    CategoriesTreeResponse categoriesTreeResponse(categoriesTreeUpdated);

    ostream << categoriesTreeResponse.serialize().dump();
}
