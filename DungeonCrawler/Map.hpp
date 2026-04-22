#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

const int GRID_WIDTH = 25;
const int GRID_HEIGHT = 19;


class Map
{
public:
    Map();
    void draw(sf::RenderWindow& window);
    bool isWall(int x, int y);

private:
    std::vector<std::vector<int>> grid;
};

