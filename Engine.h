#pragma once
#include "Map.h"
#include "Menu.h"
#include "Title.h"
#include "Combat.h"
#include "Animation.h"

class Map;
class Title;
class Combat;
class Animation;

enum GameState {
	_Title,
	_Overworld,
	_Menu,
	_Combat,
	_ExpGain
};

class Engine {
public:
//Constructors
	Engine();

//This is sloppy, remove it later
	sf::RenderWindow* getWindow() { return window; }

//sf::Window wrappers
	bool isRunning() { return window->isOpen(); }
	void pollEvent();
	void draw();
	
	
	void changeMap(unsigned mapID);
	void changeState(GameState state);
	void newAnimation(Animation animation);
	bool characterIsMoving() { return !animations.empty(); }
	void wait();

private:
	void createRenderWindow();
	void createMenu();
	void loadMaps();
	void loadCreatures();
	//void loadQuestFlags();

	sf::RenderWindow* window;
	Title* title;
	Menu* menu;
	Combat* combat;
	std::vector<PlayerCharacter*> characters;
	std::vector<Map*> maps;
	std::vector<Creature*> creatures;
	//std::vector<QuestFlag*> questFlags;
	std::vector<Animation> animations;

	GameState activeState = _Title;
	unsigned currentMap;

	sf::Clock clock;
	double elapsed;

	void setActiveState(GameState state);
	void initializeCombat();
	void updateAnimations();
};