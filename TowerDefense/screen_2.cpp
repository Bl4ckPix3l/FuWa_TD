#include <iostream>
#include "cScreen.hpp"
#include "globals.hpp"
#include "screen_2.hpp"
#include <SFML/Graphics.hpp>

screen_2::screen_2(void)
{

}

int screen_2::Run(sf::RenderWindow &App)
{
	sf::RectangleShape button;
	sf::Event Event;
	sf::Text headline;
	sf::Font font;
	sf::Texture bgTexture;
	sf::Texture image;

	std::map<std::string, std::string> menuItems;
	std::vector<sf::RectangleShape> menuListButton;
	std::vector<sf::Texture*> menuListButtonTextures;

	bool Running = true;
	float menuMarginleft = 220.f;
	float menuSpace = 60.f;

	if (!font.loadFromFile("verdanab.ttf")){
		std::cerr << "Error loading verdanab.ttf" << std::endl;
		return (-1);
	}

	headline.setColor(sf::Color(208, 181, 126));
	headline.setFont(font);
	headline.setCharacterSize(32);
	headline.setPosition({ 0, 0 });
	headline.setString("Einstellungen");
	setTextCenter(headline, 80.f);

	bgTexture.loadFromFile("menuMain.jpg");
	mainBg.setTexture(bgTexture);


	while (Running)
	{
		//Verifying events
		while (App.pollEvent(Event))
		{
			// Window closed
			if (Event.type == sf::Event::Closed)
			{
				return (-1);
			}
			//Key pressed
			if (Event.type == sf::Event::KeyPressed)
			{
				if (Event.key.code == sf::Keyboard::BackSpace){
					return 0;
				}
			}

			if (Event.type == sf::Event::MouseMoved){

			}

			if (Event.type == sf::Event::MouseButtonPressed)
			{

			}

		}

		//Clearing screen
		App.clear(sf::Color(0, 0, 0, 0));

		App.draw(mainBg);

		//App.draw(buttonText);

		App.draw(headline);

		//Drawing

		//App.draw(Rectangle);
		App.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	return -1;
}