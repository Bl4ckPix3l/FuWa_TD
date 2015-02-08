#include "globals.hpp"
#include "cScreen.hpp"

#include "Model.h"

#include <iostream>
#include <SFML/Graphics.hpp>

class screenRace : public cScreen
{
private:


public:
	screenRace(void);
	virtual int Run(sf::RenderWindow &App);

	void generateMenuItems(std::map<std::string, std::string> &menuItems, std::vector<std::map<std::string, std::string>*> results);

};
