#pragma once
#include "vector"
#include "memory"

class Tile;

class Bonus
{
public:
    virtual ~Bonus() = default;
    virtual void apply(int row, int col, std::vector<std::shared_ptr<Tile>>& tiles, int size) = 0;
};
