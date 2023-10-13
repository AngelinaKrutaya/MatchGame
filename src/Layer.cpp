#include "Layer.h"

#include "Game.h"
#include "Bonuses/BombBonus.h"

Layer::Layer(int n, TextureManager& tm, sf::RenderWindow& window): size(n), texture_manager(tm), window(window),
                                                                   tiles(n * n)
{
    initializeTiles();
}

void Layer::initializeTiles()
{
    //create tiles
    int start_x = (WINDOW_WIDTH - (SPRITE_SIZE * size)) / 2;
    int start_y = (WINDOW_HEIGHT - (SPRITE_SIZE * size)) / 2;
    for (int i = 0; i < size; ++i)
    {
        tiles.emplace_back();
        for (int j = 0; j < size; ++j)
        {
            tiles[i * size + j] = std::make_shared<Tile>(getRandomTileType(), texture_manager);
            tiles[i * size + j]->draw(window, start_x + j * SPRITE_SIZE, start_y + i * SPRITE_SIZE);
        }
    }

    //create bomb bonus
    std::uniform_int_distribution<> dis_(0, size - 1);
    bonus = std::make_shared<BombBonus>();
    int rand_col = dis_(gen);
    int rand_row = dis_(gen);
    tiles[rand_col, rand_row]->makeBonus(bonus, TextureType::BombBonus);
}

void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //draw tiles
    for (int y = 0; y < size; ++y)
    {
        for (int x = 0; x < size; ++x)
        {
            target.draw(*tiles[y * size + x]);

            if (current_index == y * size + x)
            {
                tiles[current_index]->setSpriteColor(sf::Color(255, 255, 255, 100));
            }
            else
            {
                tiles[y * size + x]->setSpriteColor(sf::Color::White);
            }
        }
    }
}

void Layer::swapTiles(std::shared_ptr<Tile>& tile1, std::shared_ptr<Tile>& tile2)
{
    tile1->tileSwap(tile2);
    std::swap(tile1, tile2);
}

void Layer::move(Direction direction)
{
    int move_index = -1;
    int col = current_index % size;
    int row = current_index / size;

    if (direction == Direction::Right && col < (size - 1)) move_index = current_index + 1;
    if (direction == Direction::Left && col > 0) move_index = current_index - 1;
    if (direction == Direction::Down && row < (size - 1)) move_index = current_index + size;
    if (direction == Direction::Up && row > 0) move_index = current_index - size;

    if (move_index >= 0)
    {
        if (!matchesAvailable())
        {
            game_over = true;
        }

        int new_col = move_index % size;
        int new_row = move_index / size;
        swapTiles(tiles[row * size + col], tiles[new_row * size + new_col]);
        delay(0.3f);
        if (!tilesMatch(col, row) && !tilesMatch(new_col, new_row))
        {
            tiles[current_index]->setSpriteColor(sf::Color::White);
            swapTiles(tiles[row * size + col], tiles[new_row * size + new_col]);
        }

        current_index = move_index;
    }
}

void Layer::burnTiles(std::vector<int>& indexes_to_delete)
{
    // shift tiles from above to down
    for (int i = 0; i < indexes_to_delete.size(); i++)
    {
        int tile_index = indexes_to_delete[i];
        int col = tile_index % size;
        int row = tile_index / size;
        tiles[tile_index]->burnTile(tiles, col, row, size);
        for (int alpha = 255; alpha >= 0; alpha -= 150)
        {
            delay(0.1f);
            tiles[tile_index]->setSpriteColor(sf::Color(255, 255, 255, alpha));
        }
    }

    for (int i = 0; i < indexes_to_delete.size(); i++)
    {
        int tile_index = indexes_to_delete[i];
        int col = tile_index % size;
        int row = tile_index / size;
        for (int j = row; j > 0; --j)
        {
            delay(0.2f);
            std::shared_ptr<Tile>& tile1 = tiles[j * size + col];
            std::shared_ptr<Tile>& tile2 = tiles[(j - 1) * size + col];
            swapTiles(tile1, tile2);
        }
        tiles[col]->setSpriteColor(sf::Color::White);
    }

    indexes_to_delete.clear();
}

bool Layer::tilesMatch(int y, int x)
{
    // Check match >=3 gorizontal
    std::vector<int> indexes_to_delete = checkMatch(x, y, true);
    if (indexes_to_delete.size() >= 3)
    {
        burnTiles(indexes_to_delete);
        return true;
    }

    // Check match >= 3 vertical
    indexes_to_delete = checkMatch(y, x, false);
    if (indexes_to_delete.size() >= 3)
    {
        burnTiles(indexes_to_delete);
        return true;
    }
    return false;
}

std::vector<int> Layer::checkMatch(int col, int row, bool horizontal_match)
{
    std::vector<int> indexes_to_delete;
    const int current_tile_index = getIndex(col, row, horizontal_match);
    const TextureType current_tile = tiles[current_tile_index]->get_texture_id();

    indexes_to_delete.push_back(current_tile_index);

    auto collect_matches_in_direction = [&](int start, int end, int step)
    {
        for (int index = start; index != end; index += step)
        {
            int tile_index = getIndex(col, index, horizontal_match);
            if (tiles[tile_index]->get_texture_id() == current_tile)
            {
                indexes_to_delete.push_back(tile_index);
            }
            else
            {
                break;
            }
        }
    };

    collect_matches_in_direction(row + 1, size, 1);
    collect_matches_in_direction(row - 1, -1, -1);

    return indexes_to_delete;
}

bool Layer::matchesAvailable()
{
    for (int col = 0; col < size; col++)
    {
        for (int row = 0; row < size; row++)
        {
            // Check tile with each of neighbour 
            std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            for (auto& dir : directions)
            {
                int new_col = col + dir.first;
                int new_row = row + dir.second;

                // swap tiles and check matching
                if (new_col >= 0 && new_col < size && new_row >= 0 && new_row < size)
                {
                    swapTiles(tiles[col * size + row], tiles[new_col * size + new_row]);

                    if ((checkMatch(col, row, true).size() >= 3) || checkMatch(row, col, false).size() >= 3)
                    {
                        //swap back after changing
                        swapTiles(tiles[col * size + row], tiles[new_col * size + new_row]);
                        return true;
                    }

                    // swap back after checking
                    swapTiles(tiles[col * size + row], tiles[new_col * size + new_row]);
                }
            }
        }
    }
    return false;
}

void Layer::delay(const float duration_)
{
    const float duration = duration_;
    float elapsed = 0.0f;
    while (elapsed < duration)
    {
        window.clear();
        window.draw(*this);
        window.display();

        elapsed += deltaTime;
    }
}

void Layer::draw(sf::RenderWindow& window)
{
    float time = clock.getElapsedTime().asSeconds();
    float intensity = 0.3f + 0.2f * std::sin(time * 10.0f);

    //checking matches >=3 of tiles in loop
    for (int y = 0; y < size; ++y)
    {
        for (int x = 0; x < size; ++x)
        {
            tilesMatch(y, x);
        }
    }
}
