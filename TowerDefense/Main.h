#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include<fstream>
#include <cctype>
#include <vector>

class Spiel
{
private:
	std::vector<std::vector<int>> map;
	std::vector<int> tempMap;
	sf::Texture mauerTexture;
	sf::Texture bauplatzTexture;
	sf::Sprite feld;

	void LoadMap(const char*filename);
	int main();
public:
	Main();
	~Main();
};

