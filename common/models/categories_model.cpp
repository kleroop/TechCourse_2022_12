#include "categories_model.h"

#include <utility>

json ICategory::serialize()
{
    json response;
    response["id"] = id;
    response["title"] = title;
    response["isHidden"] = isHidden;

    std::vector<json> children_json;

    for (auto child : children)
        children_json.push_back(child.serialize());
    response["children"] = children_json;

    return response;
}

void ICategory::deserialize(json data)
{}

CategoriesTreeResponse::CategoriesTreeResponse(CategoriesTree& _categoriesTree) : categoriesTree(_categoriesTree)
{}

json CategoriesTreeResponse::serialize()
{
    json response;

    response["status"] = 200;

    std::vector<json> categoriesTreeJson;

    for (auto category : categoriesTree.categories)
        categoriesTreeJson.push_back(category.serialize());

    response["data"]["categoriesTree"] = categoriesTreeJson;

    return response;
}

void CategoriesTreeResponse::deserialize(json data)
{}
