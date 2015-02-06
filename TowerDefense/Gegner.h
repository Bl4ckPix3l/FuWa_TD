#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include<fstream>
#include <cctype>
#include <vector>
#include "Einheit.h";

class Gegner:public Einheit
{private:
	int beute;

public:
	Gegner();
	~Gegner();
};

