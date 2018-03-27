#pragma once
#include "Creature.h"

class PlayerCharacter {
public:
//Constructor
	PlayerCharacter();
	PlayerCharacter(std::string name, unsigned id);

//Accessor
	std::string getName() { return name; }
	unsigned getLevel() { return level; }

	unsigned getMaxHitpoints() { return maxHitpoints; }
	unsigned getMaxMana() { return maxMana; }
	unsigned getMaxExperience() { return maxExperience; }

	unsigned getCurrentHitpoints() { return currentHitpoints; }
	unsigned getCurrentMana() { return currentMana; }
	unsigned getCurrentExperience() { return currentExperience; }

	unsigned getStrength() { return strength; }
	unsigned getDexterity() { return dexterity; }
	unsigned getWisdom() { return wisdom; }

	Creature* getTarget() { return target; }

	sf::Sprite* getSprite() { return &sprite; }

//Mutator
	void setName(std::string name);
	void setCurrentHitpoints(unsigned n);
	void setCurrentMana(unsigned n);
	void setCurrentExperience(unsigned n);
	void setTarget(Creature* target);
	void setFlee(bool b);
	void setDead(bool b);

//Queries
	bool isFleeing() { return flee; }
	bool isDead() { return dead; }


private:
	std::string name;
	unsigned level;

	unsigned maxHitpoints;
	unsigned maxMana;
	unsigned maxExperience;
	
	unsigned currentHitpoints;
	unsigned currentMana;
	unsigned currentExperience;

	unsigned strength;
	unsigned dexterity;
	unsigned wisdom;

	Creature* target;
	bool flee = false;
	bool dead = false;

	sf::Sprite sprite;
};