#pragma once
#include "SFML\Graphics.hpp"
#include "MapLink.h"

enum TerrainType {
	//None
	None,

	//Outdoor
	Plains,
	Forest,
	Mountain,
	Lake,
	Ocean,

	//City
	CityFloor,
	CityFloorCracked,
	CityWall,
	CityWallCracked,
	CityWallWindow,

	//Dungeon
	DungeonFloor,
	DungeonFloorCracked,
	DungeonWall,
	DungeonWallCracked,

	//Cave
	CaveFloor,
	CaveFloorCracked,
	CaveFloorStalagmite,
	CaveWall,
	CaveWallCracked,

	//Doors
	CityDoor,
	DungeonDoor,
	CaveDoor,
};

TerrainType s2tt(std::string s);

class Tile {
public:
//Constructors
	Tile(TerrainType type, MapLink mapLink, sf::Texture* texture);

//Queries
	//\Tell whether the tile is solid or not
	bool isSolid() { return solid; }
//Accessors
	//\Get the map link of the tile
	MapLink getMapLink() { return mapLink; }
	//\Get the terrain type of the tile
	TerrainType getType() { return type; }
	//\Get the sprite of the tile
	//\Returns const reference of sf::Sprite
	sf::Sprite* getSprite() { return &sprite; }

private:
	/*The type of the terrain is used to determine the state of "solid" and the
	  display area of "sprite" (sf::Sprite::TextureRect). The Tile constructor
	  does a switch on "type" to automatically set these other values*/
	TerrainType type;
	/*Determines if the player is able to stand on this tile or not. If "solid"
	  is TRUE then the player CANNOT traverse this tile. If it is FALSE then the player
	  CAN traverse the tile. This value is checked every time the player attempts a movement*/
	bool solid;
	/*"The spritesheet texture will be loaded at the start of the program and passed into every 
	  tile's constructor. Based on the type of terrain a tile is, the display rectangle of the
	  sprite will change*/
	sf::Sprite sprite;
	/*Holds the info of whether a Tile should connect to a different map or not. If a
	  link is "closed" (determined by the MapLink::isOpen() method) then isOpen() will return
	  FALSE and no new map will be loaded if they player is on this tile. If the link is "open"
	  then a new map will need to be loaded if the player were to move to this tile*/
	MapLink mapLink;
};