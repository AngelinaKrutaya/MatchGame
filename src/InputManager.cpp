#include "InputManager.h"

InputManager::InputManager(sf::RenderWindow& window_, Layer& layer): window(window_), layer(layer)
{
}

void InputManager::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        if (event.key.code == sf::Keyboard::Escape)
        {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Left) layer.move(Direction::Left);
            if (event.key.code == sf::Keyboard::Right) layer.move(Direction::Right);
            if (event.key.code == sf::Keyboard::Up) layer.move(Direction::Up);
            if (event.key.code == sf::Keyboard::Down) layer.move(Direction::Down);
        }
    }
}
