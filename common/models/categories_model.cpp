#include "categories_model.h"

#include <utility>

struct tm fixDate(struct tm date)
{
    if (date.tm_year == 0 && date.tm_sec == 0 && date.tm_hour == 0) {
        date.tm_year = 2022;
        date.tm_mon = 1;
        date.tm_mday = 1;
        date.tm_hour = 1;
        date.tm_min = 1;
        date.tm_sec = 1;
    }

    return date;
};

static inline string serialize_iso8601(struct tm tt)
{
    tt = fixDate(tt);
    char timestamp[] = "YYYY-MM-ddTHH:mm:ss.SSS+00:00Z";
    sprintf(timestamp, "%04d-%02d-%02dT%02d:%02d:%06.03fZ", 1970 + tt.tm_year, 1 + tt.tm_mon,
            tt.tm_mday, tt.tm_hour, tt.tm_min, (double)tt.tm_sec);
    return timestamp;
}

static inline struct tm deserialize_iso8601(string s)
{
    struct tm tt = { 0 };
    double seconds;

    if (sscanf(s.c_str(), "%04d-%02d-%02dT%02d:%02d:%lfZ", &tt.tm_year, &tt.tm_mon, &tt.tm_mday,
               &tt.tm_hour, &tt.tm_min, &seconds)
        != 6)
        return tt;
    tt.tm_sec = (int)seconds;
    tt.tm_mon -= 1;
    tt.tm_year -= 1970;

    tt = fixDate(tt);

    return tt;
};

json ICategory::serialize()
{
    json response;
    response["title"] = title;
    response["isHidden"] = isHidden;
    if (type == CategoryTypes::TEAM) {
        response["location"] = location;
        response["dateCreated"] = serialize_iso8601(dateCreated);
    }

    std::vector<json> children_json;

    for (auto child : children)
        children_json.push_back(child.serialize());
    response["children"] = children_json;

    return response;
}

void ICategory::deserialize(json data)
{
    if (!data.contains("title") || data["title"] == "") {
        error = "'title' field is required";
        return;
    }

    if (!data.contains("isHidden")) {
        error = "'isHidden' field is required";
        return;
    }

    if (!data.contains("children")) {
        error = "'children' field is required";
        return;
    }

    title = data["title"];
    isHidden = data["isHidden"];

    if (data.contains("location")) {
        location = data["location"];
    }

    if (data.contains("dateCreated")) {
        dateCreated = deserialize_iso8601(data["dateCreated"]);
    }

    for (auto &child : data["children"]) {
        ICategory category;
        category.deserialize(child);

        category.parent = this;
        children.push_back(category);
    }
}

json Team::serialize()
{
    json response;
    response["title"] = title;
    response["isHidden"] = isHidden;

    response["children"] = json();

    return response;
}

void Team::deserialize(json data)
{
    if (!data.contains("title") || data["title"] == "") {
        error = "'title' field is required";
        return;
    }

    if (!data.contains("isHidden")) {
        error = "'isHidden' field is required";
        return;
    }

    if (!data.contains("children")) {
        error = "'children' field is required";
        return;
    }

    title = data["title"];
    isHidden = data["isHidden"];
}

void deserializeCategoryTree(json &data, CategoriesTree &categoriesTree, std::string &error)
{
    for (auto &category : data) {
        ICategory categoryModel;
        categoryModel.deserialize(category);

        if (categoryModel.error != "") {
            error = "Deserialization error: " + categoryModel.error;
            return;
        }

        categoriesTree.categories.push_back(categoryModel);
    }
}

CategoriesTreeResponse::CategoriesTreeResponse(CategoriesTree &_categoriesTree)
    : categoriesTree(_categoriesTree)
{
}

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
    if (data["status"] != 200) {
        error = data["data"]["message"];
        return;
    }
    deserializeCategoryTree(data["data"]["categoriesTree"], categoriesTree, error);
}

UpdateCategoriesRequest::UpdateCategoriesRequest(CategoriesTree &_categoriesTree)
    : categoriesTree(_categoriesTree)
{
}

json UpdateCategoriesRequest::serialize()
{
    std::vector<json> categoriesTreeJson;

    for (auto category : categoriesTree.categories)
        categoriesTreeJson.push_back(category.serialize());

    return categoriesTreeJson;
}

void UpdateCategoriesRequest::deserialize(json data)
{
    deserializeCategoryTree(data, categoriesTree, error);
}

void CategoriesTree::updateLists()
{
    this->subcategories.clear();
    this->teams.clear();
    for (auto &cat : this->categories) {
        for (auto &scat : cat.children) {
            scat.parent = &cat;
            this->subcategories.push_back(&scat);
            for (auto &team : scat.children) {
                team.parent = &scat;
                this->teams.push_back(&team);
            }
        }
    }
}
