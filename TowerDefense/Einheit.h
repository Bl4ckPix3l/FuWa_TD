#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Position.h"


class Einheit
{
protected:
	Position* position;
	double leben;
	double maxLeben;
	double speed;
	sf::Texture unitTexture;
	sf::Sprite unit;
	std::vector<Position*> inRange;
	bool tot = false;
	sf::Clock attackClock;

	
public:
	Einheit();
	~Einheit();
	Position *getPosition();
	double getLeben();
	double getMaxLeben();
	double getSpeed();
	bool getTot();
	void spawn(Position *spawnPos);
	bool setLeben(double pLeben);
	void setMaxLeben(double pLeben);
	void setTot(bool pTot);
	void setSpeed(double pSpeed);
};

