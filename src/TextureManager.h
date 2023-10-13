#pragma once
#include "SFML/Graphics.hpp"
#include "string"

constexpr int SPRITE_SIZE = 120;
constexpr int TEXTURE_TYPE_COUNT = 4;
const std::string MAIN_TEXTURE = "../../assets/icons/icons_game.jpg";

enum class TextureType
{
    DiamondGreen = 0,
    DiamondRed = 1,
    DiamondYellow = 2,
    DiamondPurple = 3,
    DiamondOrange = 4,
    BombBonus = 5
};

class TextureManager
{
public:
    TextureManager();

    sf::Texture& getTexture() { return texture; }

    sf::IntRect getTextureRect(TextureType& type);

private:
    sf::Texture texture;
};
