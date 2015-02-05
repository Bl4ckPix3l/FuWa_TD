#include <iostream>
#include "cScreen.hpp"

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>


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