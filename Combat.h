#pragma once
#include "PlayerCharacter.h"
#include "Creature.h"
#include "Engine.h"

class Engine;

enum CombatPhase {
	chooseAction,
	chooseTarget,
	evaluateDamage,
	victory,
	defeat,
	flee
};

class Combat {
public:
	Combat(std::vector<PlayerCharacter*> characters, std::vector<Creature> creatures, Engine* engine);

	void draw(sf::RenderWindow* window);
	void handleInput(sf::Event event, sf::RenderWindow* window);

	CombatPhase getPhase() { return phase; }

private:
	void update();
	void damageEvaluation();
	void resolve(bool victory);

	std::vector<PlayerCharacter*> characters;
	std::vector<Creature> creatures;
	sf::Font font;
	std::vector<sf::Text> options;
	std::vector<sf::Text> enemyNames;
	std::vector<sf::Text> characterTextName;
	std::vector<sf::Text> characterTextHP;
	std::vector<sf::Text> characterTextMP;
	std::vector<sf::Text> creatureText;
	std::vector<sf::RectangleShape> backgrounds;

	unsigned hoveredOption = 0;
	unsigned hoveredCharacter = 0;
	unsigned hoveredCreature = 0;

	unsigned totalExpReward = 0;

	CombatPhase phase = chooseAction;
	
	Engine* engine;
};