#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <unordered_map>
#include "astart.hpp"

class Area;

class Grid : public INoder
{
public:
    Area *area;
    int X, Y;
    bool IsLock;

    Grid(Area *a, int x, int y) : area(a), X(x), Y(y), IsLock(false) {}

    virtual std::vector<std::shared_ptr<INoder>> Neighbor() override;
    virtual int CalcG(INoder *to) override
    {
        return to->G + 1; // Assuming G is a public member of INoder
    }
    virtual float CalcH(INoder *to) override
    {
        Grid *other = static_cast<Grid *>(to);
        return std::abs(other->X - X) + std::abs(other->Y - Y);
    }
    virtual bool operator==(const INoder &Other) const override
    {
        const Grid &other = static_cast<const Grid &>(Other);
        return X == other.X && Y == other.Y;
    }
};

class Area
{
public:
    int CntX, CntY;
    std::unordered_map<std::string, std::shared_ptr<Grid>> Grids;

    Area(int cntX, int cntY) : CntX(cntX), CntY(cntY)
    {
        for (int i = 0; i < CntX; i++)
        {
            for (int j = 0; j < CntY; j++)
            {
                std::string key = calAlias(i, j);
                Grids[key] = std::make_shared<Grid>(this, i, j);
            }
        }
    }

    void LockGrid(int x, int y)
    {
        Grids[calAlias(x, y)]->IsLock = true;
    }

    std::shared_ptr<Grid> GetGrid(int x, int y)
    {
        return Grids[calAlias(x, y)];
    }

    static std::string calAlias(int x, int y)
    {
        return std::to_string(x) + "|" + std::to_string(y);
    }

    void PrintMap(std::shared_ptr<Grid> c, std::shared_ptr<Grid> e)
    {
        auto path = AStart(c, e);

        std::unordered_map<std::string, bool> link;
        for (auto &node : path)
        {
            auto grid = std::dynamic_pointer_cast<Grid>(node);
            if (grid)
            {
                link[calAlias(grid->X, grid->Y)] = true;
            }
        }

        for (int i = 0; i < CntY; i++)
        {
            for (int j = 0; j < CntX; j++)
            {
                std::string alias = calAlias(j, i);
                if (Grids[alias]->IsLock)
                {
                    std::cout << "= ";
                }
                else if (link.find(alias) != link.end())
                {
                    std::cout << "* ";
                }
                else
                {
                    std::cout << "# ";
                }
            }
            std::cout << "\n";
        }
    }
};

std::vector<std::shared_ptr<INoder>> Grid::Neighbor()
{
    int dirs[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    std::vector<std::shared_ptr<INoder>> neighbors;

    for (auto &dir : dirs)
    {
        int newX = X + dir[0];
        int newY = Y + dir[1];
        auto key = Area::calAlias(newX, newY);
        auto neighbor = area->Grids.find(key);
        if (neighbor != area->Grids.end() && !neighbor->second->IsLock)
        {
            neighbors.push_back(neighbor->second);
        }
    }

    return neighbors;
}
