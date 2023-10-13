#pragma once
#include "SFML/Graphics.hpp"
#include "Layer.h"


class InputManager 
{
public:
    InputManager(sf::RenderWindow& window_, Layer& layer);
    
    void handleEvents();

private:
    sf::RenderWindow& window;
    Layer& layer;
  
};