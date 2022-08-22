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
{
    if(!data.contains("title") || data["title"] == "")
    {
        error = "'title' field is required";
        return;
    }

    if (!data.contains("isHidden"))
    {
        error = "'isHidden' field is required";
        return;
    }

    if (!data.contains("children"))
    {
        error = "'children' field is required";
        return;
    }

    title = data["title"];
    isHidden = data["isHidden"];

    for (auto& child : data["children"])
    {
        ICategory category;
        category.serialize();

        category.parent = this;
        children.push_back(category);
    }
}

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
{
    if (data["status"] != 200)
    {
        error = data["data"]["message"];
        return;
    }

    for (auto& category : data["data"]["categoriesTree"])
    {
        ICategory categoryModel;
        categoryModel.deserialize(category);

        if (categoryModel.error != "")
        {
            error = "Deserialization error: " + categoryModel.error;
            return;
        }

        categoriesTree.categories.push_back(categoryModel);
    }
}
