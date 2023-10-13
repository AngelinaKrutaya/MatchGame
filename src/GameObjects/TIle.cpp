#include "Tile.h"

thread_local std::mt19937 gen(std::random_device{}());

Tile::Tile(TextureType type, TextureManager& tm): type(type), texture_manager(tm),
                                                  sprite(tm.getTexture(), tm.getTextureRect(type))
{
}

void Tile::draw(sf::RenderWindow& window, int x_, int y_)
{
    sprite.setPosition(x_, y_);
    x = x_;
    y = y_;
    window.draw(sprite);
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite);
}

void Tile::makeBonus(std::shared_ptr<Bonus>& bonus_, TextureType type_)
{
    bonuses.push_back(bonus_);
    sprite.setTextureRect(texture_manager.getTextureRect(type_));
    type = TextureType::DiamondGreen;
}

void Tile::applyBonus(int row, int col, std::vector<std::shared_ptr<Tile>>& tiles, int size)
{
    for (auto& bonus : bonuses)
    {
        if (bonus)
        {
            bonus->apply(row, col, tiles, size);
        }
    }
    bonuses.clear();
}

void Tile::burnTile(std::vector<std::shared_ptr<Tile>>& tiles, int col, int row, int size)
{
    applyBonus(row, col, tiles, size);
    replaceTileWithTexture(getRandomTileType(), tiles[row * size + col]);
}

TextureType Tile::getRandomTileType()
{
    std::uniform_int_distribution<> dis_(0, TEXTURE_TYPE_COUNT);
    return static_cast<TextureType>(dis_(gen));
}

void Tile::replaceTileWithTexture(TextureType texture_type, std::shared_ptr<Tile>& tile) const
{
    int x = tile->getX();
    int y = tile->getY();
    tile = std::make_shared<Tile>(texture_type, texture_manager);
    tile->setPos(x, y);
}

void Tile::setSpriteColor(sf::Color color)
{
    sprite.setColor(color);
}

void Tile::tileSwap(std::shared_ptr<Tile>& tile2)
{
    int x = getX();
    int y = getY();
    setPos(tile2->getX(), tile2->getY());
    tile2->setPos(x, y);
}

void Tile::setPos(int x_, int y_)
{
    x = x_;
    y = y_;
    sprite.setPosition(x_, y_);
}
