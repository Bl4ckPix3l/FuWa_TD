#pragma once
#include <SFML/Graphics.hpp>
#include "Position.h"
#include <vector>
class Einheit
{
protected:
	Position *position;
	int leben;
	int angriffsWert;
	int speed;
	int range;
	sf::Texture unitTexture;
	sf::Sprite unit;
	std::vector<Position*> inRange;
	bool tot = false;
	sf::Clock attackClock;
	
public:
	Einheit();
	~Einheit();
	Position *getPosition();
	int getRange();
	int getLeben();
	int getAngriff();
	int getSpeed();
	bool getTot();
	void spawn(Position *spawnPos);
	void setRange(int pRange);
	void setAngriff(int pAngriff);
	bool setLeben(int pLeben);
	void setTot(bool pTot);
	void setSpeed(int pSpeed);
	void berechneRangeFelder(std::vector<std::vector<Position*>> positionen);
	std::vector<Einheit*> isInRange(std::vector<Einheit*> *pEinheiten);
	std::vector<Position*> getInRange();
	bool angriff(Einheit *angriffsZiel);
	sf::Clock getAttackClock();
};

