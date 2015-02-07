#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include<fstream>
#include <cctype>
#include <vector>
#include "Einheit.h"
#include "Turm.h"

class Gegner:public Einheit
{private:
	int beute;
	int smoothX;
	int smoothY;
	int smoothNegativ;
	bool nextX;

public:
	Gegner();
	~Gegner();
	int getSmoothNegativ();
	int getSmoothX();
	int getSmoothY();
	bool getNextX();
	void setSmoothNegativ(int pSmoothNegativ);
	void setSmoothX(int pSmoothX);
	void setSmoothY(int pSmoothY);
	void setNextX(bool nextX);

	std::vector<Turm*> isInRange(std::vector<Turm*> *pEinheiten);
};

