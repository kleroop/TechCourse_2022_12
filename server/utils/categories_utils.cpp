#include "categories_utils.h"

CategoriesTree fromDal()
{
    DAL::Category c;
    auto categories = c.Select("", {});

    CategoriesTree categoriesTree;

    for (const auto &category : categories) {
        Category categoryModel(category.name, category.isHidden);
        auto scats = category.scats;

        for (const auto &subCategory : scats) {
            SubCategory subCategoryModel(subCategory.name, subCategory.isHidden, &categoryModel);
            auto teams = subCategory.teams;

            for (const auto &team : teams) {
                Team teamModel(team.name, team.isHidden, &subCategoryModel, team.location,
                               team.dateCreated.makeTM());
                subCategoryModel.children.push_back(teamModel);
            }

            categoryModel.children.push_back(subCategoryModel);
        }

        categoriesTree.categories.push_back(categoryModel);
    }

    return categoriesTree;
}
