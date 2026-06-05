#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


class Map
{
public:
    static constexpr int GRID_WIDTH = 25;
    static constexpr int GRID_HEIGHT = 19;
    Map();
    void draw(sf::RenderWindow& window);
    bool isWall(int x, int y);

private:
    std::vector<std::vector<int>> grid;
};

