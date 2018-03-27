#include "stdafx.h"
#include "Title.h"

Title::Title(Engine* engine)
	: engine(engine) {
	titleFont.loadFromFile("Fonts\\Lady Radical 2.ttf");
	title.setString("Adventure Game");
	title.setFont(titleFont);
	title.setCharacterSize(56);
	title.setFillColor(sf::Color::Black);
	title.setPosition(sf::Vector2f(25, 25));
	startFont.loadFromFile("Fonts\\PixelFJVerdana12pt.ttf");
	start.setString("Press Space to begin");
	start.setFont(startFont);
	start.setCharacterSize(18);
	start.setPosition(sf::Vector2f(250, 500));
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile("titleBackground.png");
	background.setTexture(*texture);
	background.setPosition(sf::Vector2f(0, 0));
	engine->newAnimation(TitleFade);
}

void Title::draw() {
	sf::RenderWindow* window = engine->getWindow();
	window->draw(background);
	window->draw(title);
	window->draw(start);
}

bool Title::handleInput(sf::Event event) {
	switch (event.key.code) {
	case sf::Keyboard::Space:
		return true;
		break;
	}
	return false;
}
