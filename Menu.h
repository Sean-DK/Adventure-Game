#pragma once
#include "PlayerStatText.h"
#include <string>

class Menu {
public:
//Constructor
	Menu();

	void draw(sf::RenderWindow* window);
	void update(std::vector<PlayerCharacter*> characters);
	bool handleInput(sf::Event event, sf::RenderWindow* window);

private:
	sf::Font font;
	std::vector<sf::Text> options;
	sf::Text objective;
	std::vector<PlayerStatText*> playerStats;
	std::vector<sf::RectangleShape> backgrounds;
	unsigned hoveredOption = 0;
};