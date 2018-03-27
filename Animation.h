#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "Engine.h"

class Engine;

enum AnimationType {
	TitleFade,
	ChangeMap,
	CombatStart,
	PlayerAttack,
	CreatureAttack,
	MoveUp,
	MoveDown,
	MoveLeft,
	MoveRight,
	Wait
};

class Animation {
public:
	//Change map fade
	Animation(AnimationType type, int mapID, Engine* engine);
	
	//Combat start flash
	Animation(AnimationType type, Engine* engine);
	
	//Title fade
	Animation(AnimationType type);
	
	//Combat attack movement & text
	Animation(AnimationType type, sf::Sprite* characterSprite, sf::Sprite* creatureSprite, std::string str);
	
	//Player movement in overworld
	Animation(sf::Sprite* characterSprite, AnimationType direction);
	
	//Wait
	Animation(double duration);

	bool play(double elapsed);
	AnimationType getType() { return type; }
	sf::Text* getText() { return text; }
	sf::RectangleShape* getShape() { return shape; }

private:
	Engine* engine;

	sf::Sprite* characterSprite;
	sf::Sprite* attackingSprite;
	sf::Sprite* targetSprite;
	sf::RectangleShape* shape;
	AnimationType type;

	sf::Font* font;
	sf::Text* text;

	//Duration in milliseconds
	double duration;
	double initialDuration;

	sf::Color color;
	double r;
	double g;
	double b;
	double a;

	double x;
	double y;

	double alphaPerMillisecond;
	sf::Vector2f pixelsPerMillisecond;

	bool reverse = false;

	int mapID;
	int iteration = 0;
};