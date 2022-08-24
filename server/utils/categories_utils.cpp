#include "categories_utils.h"

CategoriesTree fromDal()
{
    DAL::Category c;
    auto categories = c.Select("", {});

    CategoriesTree categoriesTree;

    for (const auto& category : categories)
    {
        Category categoryModel(category.id, category.name, category.isHidden);
        auto scats = category.scats;

        for (const auto& subCategory : scats)
        {
            SubCategory subCategoryModel(subCategory.id, subCategory.name, subCategory.isHidden, &categoryModel);
            auto teams = subCategory.teams;

            for (const auto& team : teams)
            {
                Team teamModel(team.id, team.name, team.isHidden, &subCategoryModel);
                subCategoryModel.children.push_back(teamModel);
            }

            categoryModel.children.push_back(subCategoryModel);
        }

        categoriesTree.categories.push_back(categoryModel);
    }

    return categoriesTree;
}
