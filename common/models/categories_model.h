#ifndef QTWORLD_CATEGORIES_MODEL_H
#define QTWORLD_CATEGORIES_MODEL_H

#include <string>
#include <utility>
#include <vector>
#include "ISerializable.h"

enum CategoryTypes {
    CATEGORY,
    SUBCATEGORY,
    TEAM
};

class ICategory : ISerializable {
public:
    explicit ICategory(int id, std::string title, bool isHidden, ICategory *parent = nullptr) {
        this->id = id;
        this->title = std::move(title);
        this->isHidden = isHidden;
        this->parent = parent;
    }

    json serialize() override;
    void deserialize(json data) override;

    int id;
    ICategory *parent;
    std::string title;
    std::vector<ICategory> children = {};
    CategoryTypes type;
    bool isHidden = false;
    //todo add position
};

class CategoriesTree {
public:
    std::vector<ICategory> categories;
};

class Category : public ICategory {
public:
    Category(int id, std::string title, bool isHidden, ICategory *parent = nullptr) : ICategory(id, std::move(title), isHidden, parent) {
        this->type = CategoryTypes::CATEGORY;
    }
};

class SubCategory : public ICategory {
public:
    SubCategory(int id, std::string title, bool isHidden, ICategory *parent = nullptr) : ICategory(id, std::move(title), isHidden, parent) {
        this->type = CategoryTypes::SUBCATEGORY;
    }
};

class Team : public ICategory {
public:
    Team(int id, std::string title, bool isHidden, ICategory *parent = nullptr) : ICategory(id, std::move(title), parent) {
        this->type = CategoryTypes::TEAM;
    }
};

class CategoriesTreeResponse : ISerializable {
public:
    explicit CategoriesTreeResponse(CategoriesTree& _categoriesTree);

    json serialize() override;
    void deserialize(json data) override;

    CategoriesTree categoriesTree;
};

#endif
