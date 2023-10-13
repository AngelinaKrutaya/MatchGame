#pragma once

#include "InputManager.h"
#include "Layer.h"

constexpr int WINDOW_WIDTH = 700;
constexpr int WINDOW_HEIGHT = 700;
constexpr int GAME_OVER_WIDTH = 400;
constexpr int GAME_OVER_HEIGHT = 200;
const std::string WINDOW_NAME = "MatchGame";
const std::string END_WINDOW_NAME = "GameOver";
const std::string RESTART_BUTTON = "../../assets/icons/play_button.png";
const std::string GAME_OVER_TEXT = "../../assets/icons/game_over.jpg";
constexpr int TILES = 5;
constexpr int TOTAL_TILES = TILES * TILES;

class Game : public sf::Transformable
{
public:
    Game();
    ~Game() { delete layer; }
    void init();
    void run();
    void endGameWindow();
    void restart();

private:
    sf::RenderWindow window;
    Layer* layer;
    sf::Clock clock;
    float deltaTime;
    std::unique_ptr<InputManager> input_manager;
    std::unique_ptr<TextureManager> texture_manager;
};
