#pragma once
#include "../TextureManager.h"
#include "../Bonuses/Bonus.h"
#include "random"

extern thread_local std::mt19937 gen;


class Tile : public sf::Drawable
{
public:
    Tile(TextureType type, TextureManager& tm_);

    ~Tile() = default;

    void draw(sf::RenderWindow& window, int x_, int y_);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void makeBonus(std::shared_ptr<Bonus>& bonus_, TextureType type_);

    void applyBonus(int row, int col, std::vector<std::shared_ptr<Tile>>& tiles, int size);

    void burnTile(std::vector<std::shared_ptr<Tile>>& tiles, int col, int row, int size);

    TextureType getRandomTileType();

    void replaceTileWithTexture(TextureType texture_type, std::shared_ptr<Tile>& tile) const;

    void setSpriteColor(sf::Color color);

    void tileSwap(std::shared_ptr<Tile>& tile2);

    TextureType getType() { return type; }

    void setPos(int x_, int y_);

    int getX() const { return x; }

    int getY() const { return y; }

    sf::Sprite& getSprite() { return sprite; }

    TextureType get_texture_id() const { return type; }

private:
    std::vector<std::shared_ptr<Bonus>> bonuses;
    int x = 0, y = 0;
    TextureType type;
    sf::Sprite sprite;
    TextureManager& texture_manager;
};
