#include "stdafx.h"
#include "Tile.h"

Tile::Tile(TerrainType type, MapLink mapLink, sf::Texture* texture)
	: type(type), mapLink(mapLink) {
	sprite.setTexture(*texture);
	switch (type) {
	case Plains:
		solid = false;
		sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
		break;
	case Forest:
		solid = false;
		sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
		break;
	case Mountain:
		solid = true;
		sprite.setTextureRect(sf::IntRect(96, 0, 32, 32));
		break;
	case Lake:
		solid = true;
		sprite.setTextureRect(sf::IntRect(128, 0, 32, 32));
		break;
	case Ocean:
		solid = true;
		sprite.setTextureRect(sf::IntRect(160, 0, 32, 32));
		break;
	case CityFloor:
		solid = false;
		sprite.setTextureRect(sf::IntRect(192, 0, 32, 32));
		break;
	case CityFloorCracked:
		solid = false;
		sprite.setTextureRect(sf::IntRect(224, 0, 32, 32));
		break;
	case CityWall:
		solid = true;
		sprite.setTextureRect(sf::IntRect(0, 32, 32, 32));
		break;
	case CityWallCracked:
		solid = true;
		sprite.setTextureRect(sf::IntRect(32, 32, 32, 32));
		break;
	case CityWallWindow:
		solid = true;
		sprite.setTextureRect(sf::IntRect(64, 32, 32, 32));
		break;
	case DungeonFloor:
		solid = false;
		sprite.setTextureRect(sf::IntRect(96, 32, 32, 32));
		break;
	case DungeonFloorCracked:
		solid = false;
		sprite.setTextureRect(sf::IntRect(128, 32, 32, 32));
		break;
	case DungeonWall:
		solid = true;
		sprite.setTextureRect(sf::IntRect(160, 32, 32, 32));
		break;
	case DungeonWallCracked:
		solid = true;
		sprite.setTextureRect(sf::IntRect(192, 32, 32, 32));
		break;
	case CaveFloor:
		solid = false;
		sprite.setTextureRect(sf::IntRect(224, 32, 32, 32));
		break;
	case CaveFloorCracked:
		solid = false;
		sprite.setTextureRect(sf::IntRect(0, 64, 32, 32));
		break;
	case CaveFloorStalagmite:
		solid = true;
		sprite.setTextureRect(sf::IntRect(32, 64, 32, 32));
		break;
	case CaveWall:
		solid = true;
		sprite.setTextureRect(sf::IntRect(64, 64, 32, 32));
		break;
	case CaveWallCracked:
		solid = true;
		sprite.setTextureRect(sf::IntRect(96, 64, 32, 32));
		break;
	case CityDoor:
		solid = false;
		sprite.setTextureRect(sf::IntRect(128, 64, 32, 32));
		break;
	case DungeonDoor:
		solid = false;
		sprite.setTextureRect(sf::IntRect(160, 64, 32, 32));
		break;
	case CaveDoor:
		solid = false;
		sprite.setTextureRect(sf::IntRect(192, 64, 32, 32));
		break;
	default:
		solid = true;
		sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
		break;
	}
}

TerrainType s2tt(std::string s)
{
	if (s == "Plains") return Plains;
	if (s == "Forest") return Forest;
	if (s == "Mountain") return Mountain;
	if (s == "Lake") return Lake;
	if (s == "Ocean") return Ocean;
	if (s == "CityFloor") return CityFloor;
	if (s == "CityFloorCracked") return CityFloorCracked;
	if (s == "CityWall") return CityWall;
	if (s == "CityWallCracked") return CityWallCracked;
	if (s == "CityWallWindow") return CityWallWindow;
	if (s == "DungeonFloor") return DungeonFloor;
	if (s == "DungeonFloorCracked") return DungeonFloorCracked;
	if (s == "DungeonWall") return DungeonWall;
	if (s == "DungeonWallCracked") return DungeonWallCracked;
	if (s == "CaveFloor") return CaveFloor;
	if (s == "CaveFloorCracked") return CaveFloorCracked;
	if (s == "CaveFloorStalagmite") return CaveFloorStalagmite;
	if (s == "CaveWall") return CaveWall;
	if (s == "CaveWallCracked") return CaveWallCracked;
	if (s == "CityDoor") return CityDoor;
	if (s == "DungeonDoor") return DungeonDoor;
	if (s == "CaveDoor") return CaveDoor;
	return None;
}
