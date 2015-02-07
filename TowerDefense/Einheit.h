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
	int shape;
	std::string color;
	sf::Texture unitTexture;
	sf::Sprite unit;
	std::vector<Position*> inRange;
	bool tot = false;
	
public:
	Einheit();
	~Einheit();
	Position *getPosition();
	int getRange();
	int getLeben();
	int getAngriff();
	int getShape();
	std::string getColor();
	bool getTot();
	void spawn(Position *spawnPos);
	void setRange(int pRange);
	void setAngriff(int pAngriff);
	void setLeben(int pLeben);
	void setShape(int pShape);
	void setColor(std::string pColor);
	void setTot(bool pTot);
	void berechneRangeFelder(std::vector<std::vector<Position*>> positionen);
	std::vector<Einheit*> isInRange(std::vector<Einheit*> *pEinheiten);
	std::vector<Position*> getInRange();
	void angriff(Einheit *angriffsZiel);
};

