#pragma once
#include <SFML/Graphics.hpp>
#include "Position.h"
class Einheit
{
protected:
	Position position;
	int speed;
	sf::Texture unitTexture;
	sf::Sprite unit;

public:
	Einheit();
	~Einheit();
	Position getPosition()
	{
		return position;
	}
	void spawn(Position spawnPos);
};

