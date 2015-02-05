#pragma once
#include "Gegner.h"
#include "Map.h"
#include <vector>
#include <cmath>

class BodenGegner:public Gegner
{
private:
	std::vector<Position*> queue;
	void berechneWeg(Position *zielPos);
	void initWegfindung(Map *karte);
	double berechneAbstand(Position *startPos, Position *zielPos);
public:
	BodenGegner();
	~BodenGegner();
	void move(Position *zielPosition);
};

