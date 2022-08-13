#ifndef QTWORLD_CATEGORIES_H
#define QTWORLD_CATEGORIES_H

#include <string>
#include <utility>
#include <vector>

enum categoryTypes {
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
    categoryTypes type;
    //todo add position and show/hide
};

class CategoriesTree {
public:
    std::vector<ICategory> categories;
};

class Category : public ICategory {
public:
    Category(int id, std::string title, ICategory *parent = nullptr) : ICategory(id, std::move(title), parent) {
        this->type = categoryTypes::CATEGORY;
    }
};

class SubCategory : public ICategory {
public:
    SubCategory(int id, std::string title, ICategory *parent = nullptr) : ICategory(id, std::move(title), parent) {
        this->type = categoryTypes::SUBCATEGORY;
    }
};

class Team : public ICategory {
public:
    Team(int id, std::string title, ICategory *parent = nullptr) : ICategory(id, std::move(title), parent) {
        this->type = categoryTypes::TEAM;
    }
};

#endif
