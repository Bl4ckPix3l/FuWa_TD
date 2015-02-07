#include "cScreen.hpp"
#include "Database.h"
#include "Model.h"
#include "globals.hpp"

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

class screen_0 : public cScreen
{
private:
    int alpha_max;
    int alpha_div;
    bool playing;

public:
    screen_0(void);
    virtual int Run(sf::RenderWindow &App);
	int getMenuRouting(int item);

};