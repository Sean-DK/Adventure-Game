#include "stdafx.h"
#include "Combat.h"
#include "Animation.h"
#include <algorithm>

Combat::Combat(std::vector<PlayerCharacter*> characters, std::vector<Creature> creatures, Engine* engine) 
	: engine(engine) {
	font.loadFromFile("Fonts\\JMH Arkham.ttf");
	options.push_back(sf::Text("Attack", font, 22));
	options.push_back(sf::Text("Magic", font, 22));
	options.push_back(sf::Text("Item", font, 22));
	options.push_back(sf::Text("Flee", font, 22));
	for (unsigned i = 0; i < options.size(); i++) {
		options[i].setPosition(sf::Vector2f(340, 410 + (28 * i)));
		if (i == 1 || i == 2) {
			options[i].setFillColor(sf::Color(75, 75, 75, 255));
		}
	}

	for (unsigned i = 0; i < characters.size(); i++) {
		characterTextName.push_back(sf::Text("PlayerName", font, 22));
		characterTextName[i].setPosition(sf::Vector2f(430, 410 + (28 * i)));
		characterTextHP.push_back(sf::Text("HP ---/---", font, 22));
		characterTextHP[i].setPosition(sf::Vector2f(545, 410 + (28 * i)));
		characterTextMP.push_back(sf::Text("MP ---/---", font, 22));
		characterTextMP[i].setPosition(sf::Vector2f(670, 410 + (28 * i)));
	}

	for (unsigned i = 0; i < creatures.size(); i++) {
		creatureText.push_back(sf::Text("Creature", font, 22));
		creatureText[i].setPosition(sf::Vector2f(75, 410 + (28 * i)));
	}

	backgrounds.push_back(sf::RectangleShape(sf::Vector2f(800, 200)));
	backgrounds[0].setPosition(sf::Vector2f(0, 400));
	backgrounds[0].setFillColor(sf::Color::Blue);
	backgrounds[0].setOutlineColor(sf::Color::White);
	backgrounds[0].setOutlineThickness(-2);
	backgrounds.push_back(sf::RectangleShape(sf::Vector2f(125, 200)));
	backgrounds[1].setPosition(sf::Vector2f(300, 400));
	backgrounds[1].setFillColor(sf::Color::Blue);
	backgrounds[1].setOutlineColor(sf::Color::White);
	backgrounds[1].setOutlineThickness(-2);

	for (unsigned i = 0; i < characters.size(); i++) {
		this->characters.push_back(characters[i]);
	}
	for (unsigned i = 0; i < creatures.size(); i++) {
		this->creatures.push_back(creatures[i]);
		totalExpReward += creatures[i].getExpReward();
	}
}

void Combat::draw(sf::RenderWindow* window) {
	update();
	//Check to see if combat is over
	bool alive = false;
	for (unsigned i = 0; i < characters.size(); i++) {
		if (!characters[i]->isDead()) alive = true;
	}
	if (!alive) {
		resolve(false);
	}
	alive = false;
	for (unsigned i = 0; i < creatures.size(); i++) {
		if (!creatures[i].isDead()) alive = true;
	}
	if (!alive) {
		resolve(true);
	}
	//Draw stuff
	for (unsigned i = 0; i < backgrounds.size(); i++) {
		window->draw(backgrounds[i]);
	}
	for (unsigned i = 0; i < options.size(); i++) {
		window->draw(options[i]);
	}
	sf::Text hoverArrow("-", font, 22);
	hoverArrow.setPosition(sf::Vector2f(325, 408 + (28 * (hoveredOption))));
	window->draw(hoverArrow);
	for (unsigned i = 0; i < characters.size(); i++) {
		if (i == hoveredCharacter && phase == chooseAction) {
			characterTextName[i].setFillColor(sf::Color::Yellow);
			characterTextHP[i].setFillColor(sf::Color::Yellow);
			characterTextMP[i].setFillColor(sf::Color::Yellow);
		}
		else {
			characterTextName[i].setFillColor(sf::Color::White);
			characterTextHP[i].setFillColor(sf::Color::White);
			characterTextMP[i].setFillColor(sf::Color::White);
		}
		window->draw(characterTextName[i]);
		window->draw(characterTextHP[i]);
		window->draw(characterTextMP[i]);
	}
	for (unsigned i = 0; i < creatureText.size(); i++) {
		if (!creatures[i].isDead()) {
			if (i == hoveredCreature && phase == chooseTarget) {
				creatureText[i].setFillColor(sf::Color::Yellow);
			}
			else {
				creatureText[i].setFillColor(sf::Color::White);
			}
			window->draw(creatureText[i]);
		}
	}
	for (unsigned i = 0; i < characters.size(); i++) {
		window->draw(*characters[i]->getSprite());
	}
	for (unsigned i = 0; i < creatures.size(); i++) {
		if (!creatures[i].isDead()) {
			window->draw(*creatures[i].getSprite());
		}
	}
}

void Combat::update() {
	for (unsigned i = 0; i < characterTextName.size(); i++) {	
		characterTextName[i].setString(characters[i]->getName());
	}
	for (unsigned i = 0; i < characterTextHP.size(); i++) {
		characterTextHP[i].setString("HP " + std::to_string(characters[i]->getCurrentHitpoints())
			+ "/" + std::to_string(characters[i]->getMaxHitpoints()));
	}
	for (unsigned i = 0; i < characterTextMP.size(); i++) {
		characterTextMP[i].setString("MP " + std::to_string(characters[i]->getCurrentMana())
			+ "/" + std::to_string(characters[i]->getMaxMana()));
	}
	for (unsigned i = 0; i < creatureText.size(); i++) {
		creatureText[i].setString(creatures[i].getName());
	}
}

void Combat::handleInput(sf::Event event, sf::RenderWindow* window) {
	switch (event.type) {
	case sf::Event::KeyPressed:
		switch (event.key.code) {
		case sf::Keyboard::Up:
			if (phase == chooseAction) {
				hoveredOption--;
				if (hoveredOption > options.size()) hoveredOption = options.size() - 1;
				if (hoveredOption == 1) hoveredOption--;
				if (hoveredOption == 2) hoveredOption -= 2;
			}
			else if (phase == chooseTarget) {
				if (--hoveredCreature > creatures.size()) {
					hoveredCreature = creatures.size() - 1;
				}
				while (creatures[hoveredCreature].isDead()) {
					if (--hoveredCreature > creatures.size()) {
						hoveredCreature = creatures.size() - 1;
					}
				}
			}
			break;
		case sf::Keyboard::Down:
			if (phase == chooseAction) {
				hoveredOption++;
				if (hoveredOption + 1 > options.size()) hoveredOption = 0;
				if (hoveredOption == 1) hoveredOption++;
				if (hoveredOption == 2) hoveredOption++;
			}
			else if (phase == chooseTarget) {
				if (++hoveredCreature > creatures.size() - 1) {
					hoveredCreature = 0;
				}
				while (creatures[hoveredCreature].isDead()) {
					if (++hoveredCreature > creatures.size() - 1) {
						hoveredCreature = 0;
					}
				}
			}
			break;
		case sf::Keyboard::Return:
			switch (phase) {
			case chooseAction:
				switch (hoveredOption) {
				case 0:
					phase = chooseTarget;
					characters[hoveredCharacter]->setFlee(false);
					break;
				case 1:
					//TODO: magic
					break;
				case 2:
					//TODO: items
					break;
				case 3:
					characters[hoveredCharacter]->setFlee(true);
					while (1) {
						if (++hoveredCharacter < characters.size()) {
							if (characters[hoveredCharacter]->isDead()) {}
							else {
								phase = chooseAction;
								break;
							}
						}
						else {
							phase = evaluateDamage;
							break;
						}
					}
					break;
				}
				break;
			case chooseTarget:
				characters[hoveredCharacter]->setTarget(&creatures[hoveredCreature]);
				while (1) {
					if (++hoveredCharacter < characters.size()) {
						if (characters[hoveredCharacter]->isDead()) {}
						else {
							phase = chooseAction;
							break;
						}
					}
					else {
						phase = evaluateDamage;
						break;
					}
				}
				break;
			}
		}
	}
	//Check combat state
	if (phase == evaluateDamage) {
		damageEvaluation();
	}
}

void Combat::damageEvaluation() {
	//Creature damage
	for (unsigned i = 0; i < creatures.size(); i++) {
		Creature* creature = &creatures[i];
		if (!creature->isDead()) {
			int target = rand() % 4;
			int attempts = 0;
			while (characters[target]->getCurrentHitpoints() == 0) {
				target = rand() % 4;
				attempts++;
				if (attempts > 1000) break;
			}
			if (attempts > 1000) {}
			else {
				//TODO: actual damage calculation
				if (rand() % 3 == 0) {
					engine->newAnimation(Animation(CreatureAttack, creature->getSprite(), characters[target]->getSprite(), "Miss!"));
				} //miss
				else {
					unsigned damage = creature->getStrength() + (rand() % ((creature->getStrength() / 4) + 1));
					characters[target]->setCurrentHitpoints(characters[target]->getCurrentHitpoints() - damage);
					engine->newAnimation(Animation(CreatureAttack, creature->getSprite(), characters[target]->getSprite(), std::to_string(damage)));
				}
			}
		}
	}
	//Check player death
	for (unsigned i = 0; i < characters.size(); i++) {
		PlayerCharacter* character = characters[i];
		if (character->getCurrentHitpoints() > character->getMaxHitpoints() || character->getCurrentHitpoints() == 0) {
			character->setCurrentHitpoints(0);
			character->setDead(true);
		}
	}
	//Player damage
	for (unsigned i = 0; i < characters.size(); i++) {
		PlayerCharacter* character = characters[i];
		if (character->isDead()) {}
		else if (character->isFleeing()) {
			//TODO: figure out how to flee
			phase = flee;
			return;
		}
		else {
			Creature* target = character->getTarget();
			if (target->isDead()) { //if the target is dead, switch
				for (unsigned j = 0; j < creatures.size(); j++) {
					if (!creatures[j].isDead()) {
						target = &creatures[j];
					}
				}
			}
			//TODO: actual damage calculation
			int levelDelta = target->getLevel() - character->getLevel();
			double hitChance = (levelDelta * -0.05) + 0.75;
			if ((double(rand()) / RAND_MAX) > hitChance) {
				engine->newAnimation(Animation(PlayerAttack, character->getSprite(), target->getSprite(), "Miss!"));
				engine->wait();
			}
			else {
				unsigned damage;
				damage = character->getStrength() + (rand() % ((character->getStrength() / 4) + 1));
				target->setCurrentHitpoints(target->getCurrentHitpoints() - damage);
				engine->newAnimation(Animation(PlayerAttack, character->getSprite(), target->getSprite(), std::to_string(damage)));
				engine->wait();
			}
		}
	}
	//Check creature death
	for (unsigned i = 0; i < creatures.size(); i++) {
		Creature* creature = &creatures[i];
		if (creature->getCurrentHitpoints() > creature->getMaxHitpoints() || creature->getCurrentHitpoints() == 0) {
			creatures[i].setDead(true);
		}
	}

	for (unsigned i = 0; i < characters.size(); i++) {
		if (!characters[i]->isDead()) {
			hoveredCharacter = i;
			break;
		}
	}
	for (unsigned i = 0; i < creatures.size(); i++) {
		if (!creatures[i].isDead()) {
			hoveredCreature = i;
			break;
		}
	}
	phase = chooseAction;
}

void Combat::resolve(bool v){
	if (v) {
		for (unsigned i = 0; i < characters.size(); i++) {
			if (characters[i]->isDead()) {}
			else {
				characters[i]->setCurrentExperience(characters[i]->getCurrentExperience() + totalExpReward);
			}
		}
		phase = victory;
	}
	else {
		phase = defeat;
	}
}