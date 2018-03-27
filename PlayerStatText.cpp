#include "stdafx.h"
#include "PlayerStatText.h"

PlayerStatText::PlayerStatText(PlayerCharacter character, sf::Vector2f position) {
	font.loadFromFile("Fonts\\JMH Arkham.ttf");
	statusText.push_back(sf::Text(character.getName() + "  Lv. " + std::to_string(character.getLevel()), font, 16));
	statusText.push_back(sf::Text("HP: " + std::to_string(character.getCurrentHitpoints()) + " / " + std::to_string(character.getMaxHitpoints()), font, 16));
	statusText.push_back(sf::Text("MP: " + std::to_string(character.getCurrentMana()) + " / " + std::to_string(character.getMaxMana()), font, 16));
	statusText.push_back(sf::Text("XP: " + std::to_string(character.getCurrentExperience()) + " / " + std::to_string(character.getMaxExperience()), font, 16));
	statusText.push_back(sf::Text("STR  " + std::to_string(character.getStrength()), font, 16));
	statusText.push_back(sf::Text("DEX  " + std::to_string(character.getDexterity()), font, 16));
	statusText.push_back(sf::Text("WIS  " + std::to_string(character.getWisdom()), font, 16));
	statusText[0].setPosition(position);
	statusText[1].setPosition(sf::Vector2f(position.x, position.y + 20));
	statusText[2].setPosition(sf::Vector2f(position.x, position.y + 40));
	statusText[3].setPosition(sf::Vector2f(position.x, position.y + 60));
	statusText[4].setPosition(sf::Vector2f(position.x + 150, position.y + 20));
	statusText[5].setPosition(sf::Vector2f(position.x + 150, position.y + 40));
	statusText[6].setPosition(sf::Vector2f(position.x + 150, position.y + 60));
}

void PlayerStatText::setStatusText(PlayerCharacter character) {
	statusText[0].setString(character.getName() + "  Lv. " + std::to_string(character.getLevel()));
	statusText[1].setString("HP: " + std::to_string(character.getCurrentHitpoints()) + " / " + std::to_string(character.getMaxHitpoints()));
	statusText[2].setString("MP: " + std::to_string(character.getCurrentMana()) + " / " + std::to_string(character.getMaxMana()));
	statusText[3].setString("XP: " + std::to_string(character.getCurrentExperience()) + " / " + std::to_string(character.getMaxExperience()));
	statusText[4].setString("STR  " + std::to_string(character.getStrength()));
	statusText[5].setString("DEX  " + std::to_string(character.getDexterity()));
	statusText[6].setString("WIS  " + std::to_string(character.getWisdom()));
}
