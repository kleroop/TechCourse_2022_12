#ifndef QTWORLD_CATEGORIES_MODEL_H
#define QTWORLD_CATEGORIES_MODEL_H

#include <string>
#include <utility>
#include <vector>
#include "ISerializable.h"

enum CategoryTypes { CATEGORY, SUBCATEGORY, TEAM };

class ICategory : public ISerializable
{
public:
    explicit ICategory(std::string title = "", bool isHidden = false, ICategory *parent = nullptr)
    {
        this->title = std::move(title);
        this->isHidden = isHidden;
        this->parent = parent;
    }

    json serialize() override;
    void deserialize(json data) override;

    ICategory *parent;
    std::string title;
    std::vector<ICategory> children = {};
    CategoryTypes type;
    bool isHidden = false;
    std::string location;
    struct tm dateCreated = {};

    // todo add position
};

struct tm fixDate(struct tm date);

class Category : public ICategory {
public:
    Category(std::string title, bool isHidden, ICategory *parent = nullptr)
        : ICategory(std::move(title), isHidden, parent)
    {
        this->type = CategoryTypes::CATEGORY;
    }
};

class SubCategory : public ICategory
{
public:
    SubCategory(std::string title, bool isHidden, ICategory *parent = nullptr)
        : ICategory(std::move(title), isHidden, parent)
    {
        this->type = CategoryTypes::SUBCATEGORY;
    }
};

class Team : public ICategory
{
public:
    Team(std::string title, bool isHidden, ICategory *parent, std::string location = "", struct tm dateCreated = {})
        : ICategory(std::move(title), isHidden, parent)
    {
        this->type = CategoryTypes::TEAM;
        this->location = std::move(location);
        this->dateCreated = fixDate(dateCreated);
    }
    json serialize() override;
    void deserialize(json data) override;
};

class CategoriesTree
{
public:
    std::vector<ICategory> categories;
    void updateLists();
    std::vector<ICategory *> teams;
    std::vector<ICategory *> subcategories;
};

void deserializeCategoryTree(json &data, CategoriesTree &categoriesTree, std::string &error);

class CategoriesTreeResponse : public ISerializable
{
public:
    explicit CategoriesTreeResponse(CategoriesTree &_categoriesTree);

    json serialize() override;
    void deserialize(json data) override;

    CategoriesTree categoriesTree;
};

class UpdateCategoriesRequest : public ISerializable
{
public:
    explicit UpdateCategoriesRequest(CategoriesTree &_categoriesTree);
    json serialize() override;
    void deserialize(json data) override;

    CategoriesTree categoriesTree;
};


#endif
