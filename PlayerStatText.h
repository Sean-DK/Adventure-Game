#pragma once
#include "PlayerCharacter.h"

class PlayerStatText {
public:
//Constructor
	PlayerStatText(PlayerCharacter character, sf::Vector2f position);

//Accessors
	std::vector<sf::Text> getStatusText() { return statusText; }

//Mutators
	void setStatusText(PlayerCharacter character);

private:
	sf::Font font;
	sf::Vector2f position;
	std::vector<sf::Text> statusText;
};