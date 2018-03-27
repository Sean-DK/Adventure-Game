#include "stdafx.h"
#include "Engine.h"
#include "Dirent.h"

Engine::Engine() {
	createRenderWindow();
	createMenu();
	loadMaps();
	loadCreatures();
	//loadQuestFlags();
	title = new Title(this);
}

void Engine::pollEvent() {
	sf::Event event;
	window->pollEvent(event);
	if (event.type == sf::Event::Closed) window->close();
	switch (activeState) {
	case _Title:
		if (title->handleInput(event)) {
			if (!animations.empty()) {
				animations.clear();
			}
			changeState(_Overworld);
		}
	case _Overworld: {
		GameState returnState = maps[currentMap]->handleInput(event);
		switch (returnState) {
		case _Overworld:
			break;
		case _Combat:
			initializeCombat();
			break;
		case _Menu:
			setActiveState(_Menu);
			break;
		}
		break;
	}
	case _Menu:
		if (menu->handleInput(event, window)) setActiveState(_Overworld);
		break;
	case _Combat:
		combat->handleInput(event, window);
		CombatPhase returnPhase = combat->getPhase();
		switch (returnPhase) {
		case victory:
			animations.clear();
			setActiveState(_Overworld);
			break;
		case defeat:
			animations.clear();
			window->close();
			break;
		case flee:
			animations.clear();
			setActiveState(_Overworld);
			break;
		}
		break;
	}
}

void Engine::draw() {
	window->clear();
	switch (activeState) {
	case _Title:
		window->setView(sf::View(sf::Vector2f(400, 300), sf::Vector2f(800, 600)));
		title->draw();
		break;
	case _Overworld: {
		Map* map = maps[currentMap];
		window->setView(sf::View(map->getPlayerSpritePosition(), sf::Vector2f(800, 600)));
		maps[currentMap]->draw(window);
		break;
	}
	case _Menu:
		window->setView(sf::View(sf::Vector2f(400, 300), sf::Vector2f(800, 600)));
		menu->update(characters);
		menu->draw(window);
		break;
	case _Combat:
		window->setView(sf::View(sf::Vector2f(400, 300), sf::Vector2f(800, 600)));
		combat->draw(window);
		break;
	case _ExpGain:
		break;
	}
	updateAnimations();
	window->display();
}

void Engine::changeMap(unsigned mapID) {
	if (mapID < maps.size()) {
		currentMap = mapID;
	}
}

void Engine::changeState(GameState state) {
	activeState = state;
}

void Engine::newAnimation(Animation animation) {
	animations.push_back(animation);
}

void Engine::wait() {
	while (animations.size() > 0) {
		draw();
	}
}

void Engine::createRenderWindow() {
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Temp Window Name");
	window->setFramerateLimit(30);
}

void Engine::createMenu() {
	menu = new Menu();
	characters.push_back(new PlayerCharacter("Breadward", 0));
	characters.push_back(new PlayerCharacter("Penjamin", 1));
	characters.push_back(new PlayerCharacter("Catthew", 2));
	characters.push_back(new PlayerCharacter("Bichael", 3));
}

void Engine::loadMaps() {
	std::vector<std::string> mapNames;
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir("Maps")) != NULL) {
		int i = -2;
		while ((ent = readdir(dir)) != NULL) {
			if (i > -1) {
				mapNames.push_back(ent->d_name);
				i++;
			}
			else {
				i++;
			}
		}
		closedir(dir);
	}
	for (unsigned i = 0; i < mapNames.size(); i++) {
		std::string path = "Maps\\" + mapNames[i];
		maps.push_back(new Map(path, this));
	}
}

void Engine::loadCreatures() {
	std::vector<std::string> creatureNames;
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir("Creatures")) != NULL) {
		int i = -2;
		while ((ent = readdir(dir)) != NULL) {
			if (i > -1) {
				creatureNames.push_back(ent->d_name);
				i++;
			}
			else {
				i++;
			}
		}
		closedir(dir);
	}
	for (unsigned i = 0; i < creatureNames.size(); i++) {
		std::string path = "Creatures\\" + creatureNames[i];

		creatures.push_back(new Creature(path));
	}
}

void Engine::setActiveState(GameState state) {
	switch (state) {
	case _Title:
		activeState = _Title;
		break;
	case _Overworld:
		activeState = _Overworld;
		break;
	case _Menu:
		activeState = _Menu;
		break;
	case _Combat:
		activeState = _Combat;
		break;
	case _ExpGain:
		activeState = _ExpGain;
		break;
	}
}

void Engine::initializeCombat(){
	std::vector<Creature> creatures;
	double numCreaturesChance = double(rand()) / RAND_MAX;
	unsigned numCreatures;
	if (numCreaturesChance <= 0.2) numCreatures = 1;
	if (numCreaturesChance > 0.2 && numCreaturesChance <= 0.45) numCreatures = 2;
	if (numCreaturesChance > 0.45 && numCreaturesChance <= 0.75) numCreatures = 3;
	if (numCreaturesChance > 0.75 && numCreaturesChance <= 0.85) numCreatures = 4;
	if (numCreaturesChance > 0.85 && numCreaturesChance <= 0.95) numCreatures = 5;
	if (numCreaturesChance > 0.95) numCreatures = 6;
	//TODO: pick based on level/tile type
	for (int i = 0; i < numCreatures; i++) {
		creatures.push_back(*this->creatures[rand() % this->creatures.size()]);
		if (i < 3) {
			creatures[i].getSprite()->setPosition(sf::Vector2f(250, 40 + (110 * i)));
		}
		if (i >= 3) {
			creatures[i].getSprite()->setPosition(sf::Vector2f(100, 40 + (110 * (i % 3))));
		}
	}
	combat = new Combat(characters, creatures, this);
	newAnimation(Animation(CombatStart, this));
	wait();
	setActiveState(_Combat);
}

void Engine::updateAnimations() {
	elapsed = clock.restart().asMilliseconds();
	if (animations.size() > 0) {
		switch (animations[0].getType()) {
		case PlayerAttack:
		case CreatureAttack:
			window->draw(*animations[0].getText());
			break;
		case ChangeMap:
		case TitleFade:
		case CombatStart:
			window->draw(*animations[0].getShape());
			break;
		}
		if (animations[0].play(elapsed)) animations.erase(animations.begin());
	}
}
