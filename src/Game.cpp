#include "Game.h"

Game::Game(): window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME, sf::Style::Close)
{
    window.setPosition(sf::Vector2i(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - window.getSize().x / 2,
                                                 sf::VideoMode::getDesktopMode().height / 2 - window.getSize().y / 2)));

    init();
}

void Game::init()
{
    texture_manager = std::make_unique<TextureManager>();
    layer = new Layer(TILES, *texture_manager, window);
    input_manager = std::make_unique<InputManager>(window, *layer);
}

void Game::run()
{
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        deltaTime = elapsed.asSeconds();

        window.clear();
        layer->setDeltaTime(deltaTime);
        layer->draw(window);
        window.draw(*layer);
        input_manager->handleEvents();
        if (layer->gameOver())
        {
            endGameWindow();
        }
        window.display();
    }
}

void Game::endGameWindow()
{
    // create window
    sf::RenderWindow window_(sf::VideoMode(GAME_OVER_WIDTH, GAME_OVER_HEIGHT), END_WINDOW_NAME);

    // text message
    sf::Texture play;
    if (!play.loadFromFile(RESTART_BUTTON))
    {
        sf::err() << "Failed to load the texture from ../../assets/icons/button_restart.jpg" << std::endl;
    }
    // button restart
    sf::Texture game_over;
    if (!game_over.loadFromFile(GAME_OVER_TEXT))
    {
        sf::err() << "Failed to load the texture from ../../assets/icons/game_over.jpg" << std::endl;
    }

    sf::Sprite button;
    button.setTexture(play);
    button.setPosition(125, 80);

    sf::Sprite text;
    text.setTexture(game_over);
    text.setPosition(125, 20);


    while (window_.isOpen())
    {
        sf::Event event;
        while (window_.pollEvent(event))
        {
            //restart game
            if (event.type == sf::Event::Closed)
            {
                restart();
                window_.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window_));

                //restart game
                if (button.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    restart();
                    window_.close();
                }
            }
        }

        window_.clear();
        window_.draw(button);
        window_.draw(text);
        window_.display();
    }
}

void Game::restart()
{
    delete layer;
    layer = nullptr;
    layer = new Layer(TILES, *texture_manager, window);
}
