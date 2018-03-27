#include "stdafx.h"
#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter() {
	sf::Texture* spriteTextureSheet = new sf::Texture;
	spriteTextureSheet->loadFromFile("spriteTextureSheet.png");
	sprite.setTexture(*spriteTextureSheet);
	sprite.setTextureRect(sf::IntRect(224, 224, 32, 32));
}

PlayerCharacter::PlayerCharacter(std::string name, unsigned id)
	: level(1), maxHitpoints(10), maxMana(10), maxExperience(5),
	currentHitpoints(10), currentMana(10), currentExperience(0),
	strength(1), dexterity(1), wisdom(1), name(name) {
	sf::Texture* spriteTextureSheet = new sf::Texture;
	spriteTextureSheet->loadFromFile("spriteTextureSheet.png");
	sprite.setTexture(*spriteTextureSheet);
	sprite.setTextureRect(sf::IntRect(160, 192, 64, 64));
	sprite.setPosition(sf::Vector2f(600, 40 + (90 * id)));
}

void PlayerCharacter::setName(std::string name) {
	this->name = name;
}

void PlayerCharacter::setCurrentHitpoints(unsigned n) {
	currentHitpoints = n;
}

void PlayerCharacter::setCurrentMana(unsigned n) {
	currentMana = n;
}

void PlayerCharacter::setCurrentExperience(unsigned n) {
	if (n < maxExperience) {
		currentExperience = n;
	}
	else {
		level++;
		unsigned remainingExperience = n - maxExperience;
		maxExperience *= 1.2;
		setCurrentExperience(remainingExperience);
		maxHitpoints += 5;
		currentHitpoints += 5;
		strength += 1;
		dexterity += 1;
		wisdom += 1;
	}
}

void PlayerCharacter::setTarget(Creature* target) {
	this->target = target;
}

void PlayerCharacter::setDead(bool b) {
	dead = b;
}

void PlayerCharacter::setFlee(bool b) {
	flee = b;
}
