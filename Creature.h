#pragma once
#include "Tile.h"
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"

class Creature {
public:
	//Constructor
	Creature(std::string filePath);

	//Queries

	bool isDead() { return dead; }

	//Accessor
	std::string getName() { return name; }

	unsigned getLevel() { return level; }

	unsigned getMaxHitpoints() { return maxHitpoints; }

	unsigned getCurrentHitpoints() { return currentHitpoints; }

	unsigned getStrength() { return strength; }

	unsigned getExpReward() { return expReward; }

	TerrainType getHabitat() { return habitat; }
	
	sf::Sprite* getSprite() { return &sprite; }

	//Mutator
	void setCurrentHitpoints(unsigned n);

	void setSprite(sf::Sprite sprite);

	void setDead(bool b);

private:
	std::string name;

	sf::Sprite sprite;

	bool dead = false;

	unsigned level;

	unsigned maxHitpoints;

	unsigned currentHitpoints;

	unsigned strength;

	unsigned expReward;

	TerrainType habitat;
};