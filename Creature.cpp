#include "stdafx.h"
#include "Creature.h"
#include "StringSplit.h"
#include <fstream>

Creature::Creature(std::string filePath) {
	sf::Texture* spriteTextureSheet = new sf::Texture;
	spriteTextureSheet->loadFromFile("spriteTextureSheet.png");
	sprite.setTexture(*spriteTextureSheet);
	sprite.setTextureRect(sf::IntRect(160, 192, 64, 64));
	std::ifstream inFile(filePath);
	std::string str((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
	std::vector<std::string> strVec;
	strVec = stringsplit(str, "\n");
	for (unsigned i = 0; i < strVec.size(); i++) {
		std::vector<std::string> tempVec = stringsplit(strVec[i], " ");
		if (tempVec[0] == "Name:") {
			name = tempVec[1];
		}
		else if (tempVec[0] == "Level:") {
			level = std::stoi(tempVec[1]);
		}
		else if (tempVec[0] == "Hitpoints:") {
			maxHitpoints = currentHitpoints = std::stoi(tempVec[1]);
		}
		else if (tempVec[0] == "Strength:") {
			strength = std::stoi(tempVec[1]);
		}
		else if (tempVec[0] == "EXP:") {
			expReward = std::stoi(tempVec[1]);
		}
		else if (tempVec[0] == "Habitat:") {
			//TODO: fix habitat stuff
		}
	}
}

void Creature::setCurrentHitpoints(unsigned n) {
	currentHitpoints = n;
}

void Creature::setSprite(sf::Sprite sprite) {
	this->sprite = sprite;
}

void Creature::setDead(bool b) {
	dead = b;
}
