#pragma once
#include "Engine.h"

class Engine;

class Title {
public:
	Title() {}
	Title(Engine* engine);

	void draw();
	bool handleInput(sf::Event event);

private:
	Engine* engine;

	sf::Font titleFont;
	sf::Text title;
	sf::Font startFont;
	sf::Text start;
	sf::Sprite background;
};