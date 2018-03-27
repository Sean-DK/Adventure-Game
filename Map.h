#pragma once
#include "Tile.h"
#include "Engine.h"
#include "PlayerCharacter.h"

class Engine;
enum GameState;

class Map {
public:
//Constructors
	//\Load map from a file
	Map(std::string fileName, Engine* engine);

//Accessors
	//\Get the tile grid of the map
	//\Returns a const reference of the Tile* vector
	const std::vector<Tile*>& getGrid() { return grid; }
	//\Get the player's display position
	//\This is the player's current position
	unsigned getPlayerDisplay() { return playerDisplay; }
	//\Get the player's position
	//\This is the player's last known position, not the current position
	unsigned getPlayerPosition() { return playerPosition; }
	//\Get the width of the grid
	//\This is the horizontal dimension of the grid
	unsigned getGridWidth() { return gridWidth; }

	sf::Vector2f getPlayerSpritePosition() { return character->getSprite()->getPosition(); }
	
	
	GameState handleInput(sf::Event event);
	void draw(sf::RenderWindow* window);

private:
	/*The "grid" vector contains all of the tiles that make up a map*/
	std::vector<Tile*> grid;
	//This denotes the players CURRENT position, and where the sprite will be displayed
	unsigned playerDisplay;
	/*Actually denotes the players PREVIOUS position. This is because
	  it is updated every time the player moves, but it is updated BEFORE the player's
	  coordinates change. This means if the player is on tile 42 and moves to til 43, then
	  "playerPosition" will be updated to be equal to 42 AND THEN the player will move to 43.
	  This is done so that when a player leaves a map and then attempts to re-enter it, the
	  player will be able to return to a traversable tile, if the position were updated AFTER
	  the coordinate change, then a player would likely be placed on a door when re-entering a
	  map, which would result in a never-ending loop of re-loading maps. Instead, the player will
	  be returned in front of the door.*/
	unsigned playerPosition;
	/*Denotes the width of the grid. Since the grid is a one dimensional vector that is going to be
	  represented as a 2D grid it is necessary to know the width. The formula to convert a 2D coordinate
	  to a 1D vector is:
			2D = (x, y)
			1D = y * width + x
	  For instance, the 2D point (10, 5) on a grid with width 20 is the 1D point 205.*/
	unsigned gridWidth;
	/*Denotes how many times the character has moved since the last time a random battle occured. This is
	  used to dynamically adjust the likelihood of an encounter occuring.*/
	unsigned movesSinceLastBattle = 0;
	Engine* engine;
	PlayerCharacter* character;

	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	bool randomBattle();
};