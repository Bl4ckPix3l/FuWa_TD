#include <iostream>
#include "cScreen.hpp"

#include <SFML/Graphics.hpp>

class screen_1 : public cScreen
{
private:


public:
	screen_1(void);
	virtual int Run(sf::RenderWindow &App);
};
