#include "Map.hpp"




Map::Map()
{
	grid = std::vector<std::vector<int>>(GRID_HEIGHT, std::vector<int>(GRID_WIDTH, 0));

	for (int i = 0; i < GRID_WIDTH; i++)
	{
		grid[0][i] = 1;
		grid[GRID_HEIGHT - 1][i] = 1;
	}
	for (int i = 0; i < GRID_HEIGHT; i++)
	{
		grid[i][0] = 1;
		grid[i][GRID_WIDTH - 1] = 1;   
	}
}


void Map::draw(sf::RenderWindow& window)
{
	sf::RectangleShape shape_grid;
	
	shape_grid.setSize(sf::Vector2f(32.f, 32.f));

	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			if (grid[y][x] == 1)
				shape_grid.setFillColor(sf::Color::Green);
			else
				shape_grid.setFillColor(sf::Color::Red);

			shape_grid.setPosition(sf::Vector2f(x * 32.f, y * 32.f));
			window.draw(shape_grid);
		}
	}
}

bool Map::isWall(int x, int y)
{
	return grid[y][x] == 1;
}
