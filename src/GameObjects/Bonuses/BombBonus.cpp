#include "BombBonus.h"
#include "../GameObjects/Tile.h"

void BombBonus::apply(int row, int col, std::vector<std::shared_ptr<Tile>>& tiles, int size)
{
    // burn tiles from col and row of bonus tile
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0) continue;

            int new_row = row + i;
            int new_col = col + j;

            if (new_row >= 0 && new_row < size && new_col >= 0 && new_col < size)
            {
                int index = new_row * size + new_col;
                for (int alpha = 255; alpha >= 0; alpha -= 5)
                {
                    tiles[index]->setSpriteColor(sf::Color(255, 255, 255, alpha));
                }
                tiles[index]->replaceTileWithTexture(tiles[index]->getRandomTileType(), tiles[index]);
            }
        }
    }
}
