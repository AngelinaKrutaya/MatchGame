#pragma once
#include "GameObjects/Tile.h"
#include "Bonuses/Bonus.h"

enum class Direction
{
    Left = 0,
    Right = 1,
    Up = 2,
    Down = 3
};

class Layer:public sf::Transformable, sf::Shader,public sf::Drawable
{
public:
    
    Layer(int n,TextureManager& tm,sf::RenderWindow& window);

    void initializeTiles();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void swapTiles(std::shared_ptr<Tile>& tile1, std::shared_ptr<Tile>& tile2 );
    
    void move(Direction direction);

    void burnTiles(std::vector<int>& indexes_to_delete);
    
    bool tilesMatch(int y, int x);

    std::vector<int> checkMatch(int col, int row, bool horizontal_match);
    
    bool matchesAvailable();

    void delay(const float duration_);

    void setDeltaTime(float delta){ deltaTime = delta; }

    bool gameOver(){ return game_over; }
    
    void draw(sf::RenderWindow& window);
    
    std::vector<std::shared_ptr<Tile>> tiles;
    
private:
    
    int getIndex(int col, int row, bool horizontal_match) {
        return horizontal_match ? col * size + row : row * size + col;
    }

    TextureType getRandomTileType() {
        std::uniform_int_distribution<> dis_(0, TEXTURE_TYPE_COUNT);
        return static_cast<TextureType>(dis_(gen));
    }

    int current_index = 0;
    int size;
    float deltaTime;
    bool game_over = false;
    sf::Clock clock;
    sf::Shader burnShader_;
    sf::RenderWindow& window;
    TextureManager& texture_manager;
    std::shared_ptr<Bonus> bonus;
};
