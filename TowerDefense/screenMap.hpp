#include "cScreen.hpp"
#include "globals.hpp"
#include "Model.h"

#include <iostream>
#include <SFML/Graphics.hpp>

class screenMap : public cScreen
{
private:

public:
	screenMap(void);
	virtual int Run(sf::RenderWindow &App);

	void generateMenuItems(std::map<std::string, std::string> &menuItems, std::vector<std::map<std::string, std::string>*> results);

};
