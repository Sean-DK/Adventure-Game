#include "stdafx.h"
#include "Engine.h"

int main() {
	srand(time(NULL));
	Engine engine;
	while (engine.isRunning()) {
		engine.pollEvent();
		engine.draw();
	}
	return 0;
}