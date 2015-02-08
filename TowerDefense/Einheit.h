#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Position.h"


class Einheit
{
protected:
	double maxLeben;
	Position *position;
	double leben;
	double angriffsWert;
	double speed;
	int range;
	int shape;
	std::string color;
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
	int getRange();
	double getAngriff();
	int getShape();
	std::string getColor();
	void setRange(int pRange);
	void setAngriff(int pAngriff);
	bool setLeben(int pLeben);
	void setShape(int pShape);
	void setColor(std::string pColor);
	void setTot(bool pTot);
	void setSpeed(double pSpeed);
};

