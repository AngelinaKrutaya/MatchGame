#include "TextureManager.h"

TextureManager::TextureManager()
{
    if (!texture.loadFromFile(MAIN_TEXTURE))
    {
        sf::err() << "Failed to load the texture from ../assets/icons/icons_game.jpg" << std::endl;
    }
}

sf::IntRect TextureManager::getTextureRect(TextureType& type)
{
    switch (type)
    {
    case TextureType::DiamondGreen:
        return {2 * SPRITE_SIZE, 1 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE};
    case TextureType::DiamondRed:
        return {0 * SPRITE_SIZE, 1 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE};
    case TextureType::DiamondYellow:
        return {1 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE};
    case TextureType::DiamondPurple:
        return {0, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE};
    case TextureType::DiamondOrange:
        return {1 * SPRITE_SIZE, 1 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE};
    case TextureType::BombBonus:
        return {2 * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE};
    default:
        return {2 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE};
    }
}
