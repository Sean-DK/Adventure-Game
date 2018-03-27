#include "stdafx.h"
#include "Animation.h"


//ChangeMap
Animation::Animation(AnimationType type, int mapID, Engine* engine)
	: type(type), color(sf::Color::Black), mapID(mapID), engine(engine) {
	if (type == ChangeMap) {
		duration = initialDuration = 500;
		shape = new sf::RectangleShape(sf::Vector2f(50000, 50000));
		shape->setPosition(sf::Vector2f(-2500, -2500));
		alphaPerMillisecond = 255.0 / duration;
		r = color.r;
		g = color.g;
		b = color.b;
		a = 0;
		shape->setFillColor(sf::Color(r, g, b, a));
	}
	else {
		throw std::runtime_error("Improper animation type. Expected 'ChangeMap'");
	}
}

//Combat start
Animation::Animation(AnimationType type, Engine * engine) 
	: type(type), engine(engine), color(sf::Color::White) {
	if (type == CombatStart) {
		duration = initialDuration = 200;
		shape = new sf::RectangleShape(sf::Vector2f(50000, 50000));
		shape->setPosition(sf::Vector2f(-2500, -2500));
		alphaPerMillisecond = 255.0 / duration;
		r = color.r;
		g = color.g;
		b = color.b;
		a = 0;
		shape->setFillColor(sf::Color(r, g, b, a));
	}
	else {
		throw std::runtime_error("Improper animation type. Expected 'CombatStart'");
	}
}

//Title fade
Animation::Animation(AnimationType type) 
	: type(TitleFade), color(sf::Color::Black) {
	if (type == TitleFade) {
		shape = new sf::RectangleShape(sf::Vector2f(800, 600));
		shape->setPosition(sf::Vector2f(0, 0));
		initialDuration = 2000;
		duration = 5000;
		alphaPerMillisecond = 255.0 / duration;
		r = color.r;
		g = color.g;
		b = color.b;
		a = 255;
		shape->setFillColor(sf::Color(r, g, b, a));
	}
	else {
		throw std::runtime_error("Improper animation type. Expected 'TitleFade'");
	}
}

//Attack
Animation::Animation(AnimationType type, sf::Sprite* attackingSprite, sf::Sprite* targetSprite, std::string str)
	: type(type), attackingSprite(attackingSprite), targetSprite(targetSprite) {
	if (type == PlayerAttack || type == CreatureAttack) {
		switch (type) {
		case PlayerAttack:
			duration = initialDuration = 200;
			x = attackingSprite->getPosition().x;
			y = attackingSprite->getPosition().y;
			pixelsPerMillisecond.x = -0.25;
			pixelsPerMillisecond.y = 0;
			font = new sf::Font();
			font->loadFromFile("Fonts/ARCADECLASSIC.ttf");
			text = new sf::Text(str, *font, 22);
			text->setFillColor(sf::Color::White);
			text->setOutlineColor(sf::Color::Black);
			text->setOutlineThickness(1);
			text->setPosition(sf::Vector2f(targetSprite->getPosition().x + 54, targetSprite->getPosition().y + 5));
			break;
		case CreatureAttack:
			duration = initialDuration = 200;
			x = attackingSprite->getPosition().x;
			y = attackingSprite->getPosition().y;
			pixelsPerMillisecond.x = 0.25;
			pixelsPerMillisecond.y = 0;
			font = new sf::Font();
			font->loadFromFile("Fonts/ARCADECLASSIC.ttf");
			text = new sf::Text(str, *font, 22);
			text->setFillColor(sf::Color::White);
			text->setOutlineColor(sf::Color::Black);
			text->setOutlineThickness(1);
			text->setPosition(sf::Vector2f(targetSprite->getPosition().x + 54, targetSprite->getPosition().y + 5));
			break;
		}
	}
	else {
		throw std::runtime_error("Improper animation type. Expected 'PlayerAttack' or 'CreatureAttack'");
	}
}

//Move
Animation::Animation(sf::Sprite* characterSprite, AnimationType direction) 
	: characterSprite(characterSprite) {
	if (direction == MoveUp ||
		direction == MoveDown ||
		direction == MoveLeft ||
		direction == MoveRight) {
		duration = 300;
		x = characterSprite->getPosition().x;
		y = characterSprite->getPosition().y;
		switch (direction) {
		case MoveUp:
			type = MoveUp;
			pixelsPerMillisecond.x = 0;
			pixelsPerMillisecond.y = -(double(32) / duration);
			break;
		case MoveDown:
			type = MoveDown;
			pixelsPerMillisecond.x = 0;
			pixelsPerMillisecond.y = double(32) / duration;
			break;
		case MoveLeft:
			type = MoveLeft;
			pixelsPerMillisecond.x = -(double(32) / duration);
			pixelsPerMillisecond.y = 0;
			break;
		case MoveRight:
			type = MoveRight;
			pixelsPerMillisecond.x = double(32) / duration;
			pixelsPerMillisecond.y = 0;
			break;
		default:
			type = Wait;
			duration = 0;
		}
	}
	else {
		throw std::runtime_error("Improper animation type. Expected 'MoveUp', 'MoveDown', 'MoveLeft', or 'MoveRight'");
	}
}

//Wait
Animation::Animation(double duration) 
	: type(Wait), duration(duration) {}

bool Animation::play(double elapsed) {
	switch (type) {
	case TitleFade: {
		if (!reverse) {
			if (initialDuration - elapsed < 0) {
				elapsed = initialDuration;
			}
			initialDuration -= elapsed;
			if (initialDuration <= 0) {
				reverse = true;
			}
		}
		if (reverse) {
			if (duration - elapsed < 0) {
				elapsed = duration;
			}
			double deltaA = alphaPerMillisecond * elapsed;
			a -= deltaA;
			color = sf::Color(r, g, b, a);
			shape->setFillColor(color);
			duration -= elapsed;
			if (duration <= 0) {
				return true;
			}
		}
		break;
	}
	case ChangeMap: {
		if (!reverse) {
			if (duration - elapsed < 0) {
				elapsed = duration;
			}
			double deltaA = alphaPerMillisecond * elapsed;
			a += deltaA;
			color = sf::Color(r, g, b, a);
			shape->setFillColor(color);
			duration -= elapsed;
			if (duration <= 0) {
				duration = 0;
				reverse = true;
				engine->changeMap(mapID);
			}
		}
		if (reverse) {
			if (duration + elapsed > initialDuration) {
				elapsed = initialDuration - duration;
			}
			double deltaA = alphaPerMillisecond * elapsed;
			a -= deltaA;
			color = sf::Color(r, g, b, a);
			shape->setFillColor(color);
			duration += elapsed;
			if (duration >= initialDuration) {
				return true;
			}
		}
		break;
	}
	case CombatStart: {
		if (iteration == -1) {
			if (duration - elapsed < 0) {
				elapsed = duration;
			}
			double deltaA = alphaPerMillisecond * elapsed;
			a -= deltaA;
			color = sf::Color(r, g, b, a);
			shape->setFillColor(color);
			duration -= elapsed;
			if (duration <= 0) {
				return true;
			}
		}
		else {
			if (!reverse) {
				if (duration - elapsed < 0) {
					elapsed = duration;
				}
				double deltaA = alphaPerMillisecond * elapsed;
				a += deltaA;
				color = sf::Color(r, g, b, a);
				shape->setFillColor(color);
				duration -= elapsed;
				if (duration <= 0) {
					if (iteration > 2) {
						iteration = -1;
						duration = 500;
						alphaPerMillisecond = a / duration;
						engine->changeState(_Combat);
					}
					else {
						duration = 0;
						reverse = true;
						iteration++;
					}
				}
			}
			if (reverse) {
				if (duration + elapsed > initialDuration) {
					elapsed = initialDuration - duration;
				}
				double deltaA = alphaPerMillisecond * elapsed;
				a -= deltaA;
				color = sf::Color(r, g, b, a);
				shape->setFillColor(color);
				duration += elapsed;
				if (duration >= initialDuration) {
						duration = initialDuration;
						reverse = false;
				}
			}
		}
		break;
	}
	case PlayerAttack:
	case CreatureAttack: {
		if (!reverse) {
			if (duration - elapsed < 0) {
				elapsed = duration;
			}
			double deltaX = pixelsPerMillisecond.x * elapsed;
			double deltaY = pixelsPerMillisecond.y * elapsed;
			x += deltaX;
			y += deltaY;
			attackingSprite->setPosition(sf::Vector2f(x, y));
			int textY = text->getPosition().y - 2;
			text->setPosition(sf::Vector2f(text->getPosition().x, textY));
			duration -= elapsed;
			if (duration <= 0) {
				duration = 0;
				reverse = true;
			}
		}
		if (reverse) {
			if (duration + elapsed > initialDuration) {
				elapsed = initialDuration - duration;
			}
			double deltaX = pixelsPerMillisecond.x * elapsed;
			double deltaY = pixelsPerMillisecond.y * elapsed;
			x -= deltaX;
			y -= deltaY;
			attackingSprite->setPosition(sf::Vector2f(x, y));
			int textY = text->getPosition().y - 2;
			text->setPosition(sf::Vector2f(text->getPosition().x, textY));
			duration += elapsed;
			if (duration >= initialDuration) {
				return true;
			}
		}
		break;
	}
	case MoveUp: 
	case MoveDown:
	case MoveLeft:
	case MoveRight: {
		if (duration - elapsed < 0) {
			elapsed = duration;
		}
		double deltaX = pixelsPerMillisecond.x * elapsed;
		double deltaY = pixelsPerMillisecond.y * elapsed;
		x += deltaX;
		y += deltaY;
		characterSprite->setPosition(sf::Vector2f(x, y));
		duration -= elapsed;
		if (duration <= 0) {
			return true;
		}
		break;
	}
	case Wait: {
		if (duration > 0) {
			duration -= elapsed;
			return false;
		}
		return true;
		break;
	}
	}
	return false;
}
