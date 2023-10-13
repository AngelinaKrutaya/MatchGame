#pragma once
#include "Bonus.h"

class BombBonus : public Bonus
{
public:
    ~BombBonus() override = default;
    void apply(int row, int col, std::vector<std::shared_ptr<Tile>>& tiles, int size) override;
};
