#include "stdafx.h"
#include "Menu.h"

Menu::Menu() {
	font.loadFromFile("Fonts\\JMH Arkham.ttf");
	options.push_back(sf::Text("Resume", font, 16));
	options.push_back(sf::Text("Quit", font, 16));
	for (unsigned i = 0; i < options.size(); i++) {
		options[i].setPosition(sf::Vector2f(40, 20 + (20 * i)));
	}
	//TODO: dynamically change "objective" with QuestFlag object
	objective.setString("Current Objective:\n\n");
	objective.setPosition(sf::Vector2f(20, 80));
	objective.setFont(font);
	objective.setCharacterSize(16);

	playerStats.push_back(new PlayerStatText(PlayerCharacter(), sf::Vector2f(300, 50)));
	playerStats.push_back(new PlayerStatText(PlayerCharacter(), sf::Vector2f(300, 180)));
	playerStats.push_back(new PlayerStatText(PlayerCharacter(), sf::Vector2f(300, 310)));
	playerStats.push_back(new PlayerStatText(PlayerCharacter(), sf::Vector2f(300, 440)));

	backgrounds.push_back(sf::RectangleShape(sf::Vector2f(150, 50)));
	backgrounds[0].setPosition(sf::Vector2f(15, 15));
	backgrounds[0].setFillColor(sf::Color::Blue);
	backgrounds[0].setOutlineColor(sf::Color::White);
	backgrounds[0].setOutlineThickness(-2);
	backgrounds.push_back(sf::RectangleShape(sf::Vector2f(150, 510)));
	backgrounds[1].setPosition(sf::Vector2f(15, 75));
	backgrounds[1].setFillColor(sf::Color::Blue);
	backgrounds[1].setOutlineColor(sf::Color::White);
	backgrounds[1].setOutlineThickness(-2);
	backgrounds.push_back(sf::RectangleShape(sf::Vector2f(610, 570)));
	backgrounds[2].setPosition(sf::Vector2f(175, 15));
	backgrounds[2].setFillColor(sf::Color::Blue);
	backgrounds[2].setOutlineColor(sf::Color::White);
	backgrounds[2].setOutlineThickness(-2);
}

void Menu::draw(sf::RenderWindow* window) {
	for (unsigned i = 0; i < backgrounds.size(); i++) {
		window->draw(backgrounds[i]);
	}
	for (unsigned i = 0; i < options.size(); i++) {
		window->draw(options[i]);
	}
	sf::Text hoverArrow("-", font, 16);
	hoverArrow.setPosition(sf::Vector2f(25, 20 + (20 * (hoveredOption))));
	window->draw(hoverArrow);
	window->draw(objective);
	for (unsigned i = 0; i < playerStats.size(); i++) {
		for (unsigned j = 0; j < playerStats[i]->getStatusText().size(); j++) {
			window->draw(playerStats[i]->getStatusText()[j]);
		}
	}
}

void Menu::update(std::vector<PlayerCharacter*> characters) {
	for (unsigned i = 0; i < characters.size() && i < playerStats.size(); i++) {
		playerStats[i]->setStatusText(*characters[i]);
	}
	//TODO: dynamically change "objective" with QuestFlag object
	objective.setString("Current Objective:\n\n" /*+ QuestFlag.getObjectiveText()*/);
}

bool Menu::handleInput(sf::Event event, sf::RenderWindow* window) {
	switch (event.type) {
	case sf::Event::KeyPressed:
		switch (event.key.code) {
		case sf::Keyboard::Up:
			hoveredOption--;
			if (hoveredOption > options.size()) hoveredOption = options.size() - 1;
			break;
		case sf::Keyboard::Down:
			hoveredOption++;
			if (hoveredOption + 1 > options.size()) hoveredOption = 0;
			break;
		case sf::Keyboard::Return:
			switch (hoveredOption) {
			case 0:
				return true;
				break;
			case 1:
				window->close();
				break;
			}
		}
	}
	return false;
}