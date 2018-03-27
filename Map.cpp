#include "stdafx.h"
#include "Map.h"
#include "StringSplit.h"
#include <fstream>
#include <algorithm>

Map::Map(std::string filePath, Engine* engine) 
	: engine(engine) {
	sf::Texture* spriteTextureSheet = new sf::Texture;
	spriteTextureSheet->loadFromFile("spriteTextureSheet.png");
	std::ifstream inFile(filePath);
	std::string str((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
	std::vector<std::string> strVec;
	strVec = stringsplit(str, "\n");
	for (unsigned i = 0; i < strVec.size(); i++) {
		if (strVec[i] == "}") continue;
		else if (strVec[i] == "]") continue;
		else if (strVec[i] == "{") {
			grid.push_back(new Tile(s2tt(strVec[i+1]), MapLink(s2b(strVec[i+2]), std::stoi(strVec[i+3])), spriteTextureSheet));
			i = i + 3;
		}
		else {
			std::vector<std::string> tempVec = stringsplit(strVec[i], " ");
			if (tempVec[0] == "Width:") {
				gridWidth = std::stoi(tempVec[1]);
			}
			if (tempVec[0] == "Tiles:") {
				grid.reserve(std::stoi(tempVec[1]));
			}
			if (tempVec[0] == "Spawn:") {
				playerPosition = std::stoi(tempVec[1]);
				playerDisplay = playerPosition;
			}
		}
	}
	character = new PlayerCharacter();
	character->getSprite()->setPosition(sf::Vector2f((playerDisplay % gridWidth) * 32, (playerDisplay / gridWidth) * 32));
}

GameState Map::handleInput(sf::Event event)
{
	switch (event.type) {
	case sf::Event::KeyPressed:
		switch (event.key.code) {
		case sf::Keyboard::Up:
			if (moveUp()) return _Combat;
			break;
		case sf::Keyboard::Down:
			if (moveDown()) return _Combat;
			break;
		case sf::Keyboard::Left:
			if (moveLeft()) return _Combat;
			break;
		case sf::Keyboard::Right:
			if (moveRight()) return _Combat;
			break;
		case sf::Keyboard::Return:
			return _Menu;
			break;
		}
	}
	return _Overworld;
}

void Map::draw(sf::RenderWindow* window) {
	for (unsigned i = 0; i < grid.size(); i++) {
		grid[i]->getSprite()->setPosition(sf::Vector2f((i % gridWidth) * 32, (i / gridWidth) * 32));
		window->draw(*grid[i]->getSprite());
	}
	window->draw(*character->getSprite());
}

bool Map::moveUp() {
	if (!engine->characterIsMoving()) {
		unsigned newPos = playerDisplay - gridWidth;
		if (newPos < grid.size() && !grid[newPos]->isSolid()) {
			if (!grid[newPos]->getMapLink().isOpen()) {
				playerPosition = playerDisplay;
				playerDisplay -= gridWidth;
				engine->newAnimation(Animation(character->getSprite(), MoveUp));
				if (!randomBattle()) {
					movesSinceLastBattle++;
				}
				else {
					movesSinceLastBattle = 0;
					return true;
				}
			}
			else {
				engine->newAnimation(Animation(ChangeMap, grid[newPos]->getMapLink().getMapID(), engine));
				engine->wait();
			}
		}
	}
	return false;
}

bool Map::moveDown() {
	if (!engine->characterIsMoving()) {
		unsigned newPos = playerDisplay + gridWidth;
		if (newPos < grid.size() && !grid[newPos]->isSolid()) {
			if (!grid[newPos]->getMapLink().isOpen()) {
				playerPosition = playerDisplay;
				playerDisplay += gridWidth;
				engine->newAnimation(Animation(character->getSprite(), MoveDown));
				if (!randomBattle()) {
					movesSinceLastBattle++;
				}
				else {
					movesSinceLastBattle = 0;
					return true;
				}
			}
			else {
				engine->newAnimation(Animation(ChangeMap, grid[newPos]->getMapLink().getMapID(), engine));
				engine->wait();
			}
		}
	}
	return false;
}

bool Map::moveLeft() {
	if (!engine->characterIsMoving()) {
		unsigned newPos = playerDisplay - 1;
		if (newPos % gridWidth == gridWidth - 1) {}
		else if (newPos < grid.size() && !grid[newPos]->isSolid()) {
			if (!grid[newPos]->getMapLink().isOpen()) {
				playerPosition = playerDisplay;
				playerDisplay -= 1;
				engine->newAnimation(Animation(character->getSprite(), MoveLeft));
				if (!randomBattle()) {
					movesSinceLastBattle++;
				}
				else {
					movesSinceLastBattle = 0;
					return true;
				}
			}
			else {
				engine->newAnimation(Animation(ChangeMap, grid[newPos]->getMapLink().getMapID(), engine));
				engine->wait();
			}
		}
	}
	return false;
}

bool Map::moveRight() {
	if (!engine->characterIsMoving()) {
		unsigned newPos = playerDisplay + 1;
		if (newPos % gridWidth == 0) {}
		else if (newPos < grid.size() && !grid[newPos]->isSolid()) {
			if (!grid[newPos]->getMapLink().isOpen()) {
				playerPosition = playerDisplay;
				playerDisplay += 1;
				engine->newAnimation(Animation(character->getSprite(), MoveRight));
				if (!randomBattle()) {
					movesSinceLastBattle++;
				}
				else {
					movesSinceLastBattle = 0;
					return true;
				}
			}
			else {
				engine->newAnimation(Animation(ChangeMap, grid[newPos]->getMapLink().getMapID(), engine));
				engine->wait();
			}
		}
	}
	return false;
}

bool Map::randomBattle()
{
	unsigned baseChance = 20;
	unsigned actualChance = baseChance - movesSinceLastBattle;
	if (rand() % actualChance == 0) {
		return true;
	}
	return false;
}