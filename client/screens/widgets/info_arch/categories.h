#ifndef QTWORLD_CATEGORIES_H
#define QTWORLD_CATEGORIES_H

#include <string>
#include <utility>
#include <vector>

enum CategoryTypes {
    CATEGORY,
    SUBCATEGORY,
    TEAM
};

//todo move to models
class ICategory {
public:
    explicit ICategory(int id, std::string title, ICategory *parent = nullptr) {
        this->id = id;
        this->title = std::move(title);
        this->parent = parent;
    }

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
    Category(int id, std::string title, ICategory *parent = nullptr) : ICategory(id, std::move(title), parent) {
        this->type = CategoryTypes::CATEGORY;
    }
};

class SubCategory : public ICategory {
public:
    SubCategory(int id, std::string title, ICategory *parent = nullptr) : ICategory(id, std::move(title), parent) {
        this->type = CategoryTypes::SUBCATEGORY;
    }
};

class Team : public ICategory {
public:
    Team(int id, std::string title, ICategory *parent = nullptr) : ICategory(id, std::move(title), parent) {
        this->type = CategoryTypes::TEAM;
    }
};

#endif
