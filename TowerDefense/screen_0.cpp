#include <iostream>
#include "globals.hpp"
#include "cScreen.hpp"
#include "screen_0.hpp"
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>


screen_0::screen_0(void)
{
	alpha_max = 3 * 255;
	alpha_div = 3;
	playing = false;
}

int screen_0::getMenuRouting(int item){
	int route = -1; // Exit
	switch (item){
	case 0: // Spielen
		route = 4;
		break;
	case 1: // Einstellungen
		route = 2;
		break;
	}
	return route;
}

int screen_0::Run(sf::RenderWindow &App)
{
	bool Running = true;
	int alpha = 0;
	int menu = 0;

	sf::Event Event;
	sf::Texture Texture;
	sf::Texture logo;
	sf::Sprite spriteLogo;

	sf::Font Font;
	sf::Text menuItemPlay;
	sf::Text menuItemSettings;
	sf::RectangleShape button;

	std::vector<std::string> menuItems;
	std::vector<sf::Text*> menuListText;
	std::vector<sf::RectangleShape> menuListButton;

	if (!Font.loadFromFile("verdanab.ttf")){
		std::cerr << "Error loading verdanab.ttf" << std::endl;
		return (-1);
	}

	menuItems.push_back("Spielen");
	menuItems.push_back("Einstellungen");
	menuItems.push_back("Beenden");
	

	playMainMusic();

	float menuMarginTop = 220.f;
	float menuSpace = 60.f;

	//std::map<std::string, std::string>::iterator curr, end;
	for (int i = 0; i < menuItems.size(); i++){
		sf::Text* MenuTest = new sf::Text();
		MenuTest->setFont(Font);
		MenuTest->setCharacterSize(20);
		MenuTest->setString(menuItems[i]);
		MenuTest->setColor(sf::Color(208, 181, 126));
		//setTextCenter(MenuTest, menuMarginTop);
		menuListText.push_back(MenuTest);

		button = sf::RectangleShape(sf::Vector2f(250, 40));
		button.setFillColor(sf::Color::Transparent);
		button.setOutlineThickness(3);
		button.setOutlineColor(sf::Color(1, 217, 232));
		setButtonCenter(button, menuMarginTop + 8);
		menuListButton.push_back(button);

		menuMarginTop = menuMarginTop + menuSpace;
	}

	// texturen laden
	if (!Texture.loadFromFile("menuMain.jpg")){
		std::cerr << "Error loading menuMain.gif" << std::endl;
		return (-1);
	}
	mainBg.setTexture(Texture);
	mainBg.setColor(sf::Color(255, 255, 255, alpha));

	if (!logo.loadFromFile("logo.png")){
		std::cerr << "Error loading logo.png" << std::endl;
		return (-1);
	}
	spriteLogo.setTexture(logo);
	setSpriteCenter(spriteLogo, 80.f);



	if (playing)
	{
		alpha = alpha_max;
	}

	int menuPrev;

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
				switch (Event.key.code)
				{
				case sf::Keyboard::Up:
					playButtonSound();
					menu++;
					if (menu == menuListText.size()){
						menu = 0;
					}
					break;
				case sf::Keyboard::Down:
					playButtonSound();
					if (menu == 0){
						menu = menuListText.size() - 1;
					}
					else {
						menu--;
					}
					break;
				case sf::Keyboard::Return:
					return getMenuRouting(menu);
					break;
				default:
					break;
				}

			}
			if (Event.type == sf::Event::MouseMoved){
				menuPrev = onButtonHover(Event, menuListButton, "move");
				if (menuPrev != menu){
					playButtonSound();
				}
				menu = menuPrev;
			}

			if (Event.type == sf::Event::MouseButtonPressed)
			{
				if (Event.mouseButton.button == sf::Mouse::Left)
				{
					menu = onButtonHover(Event, menuListButton, "press");

					return getMenuRouting(menu);
				}
			}
		}
		//When getting at alpha_max, we stop modifying the mainBg
		if (alpha<alpha_max)
		{
			alpha++;
		}
		mainBg.setColor(sf::Color(255, 255, 255, alpha / alpha_div));

		//Clearing screen
		App.clear();
		//Drawing

		// hintergrund zeichnen
		App.draw(mainBg);
		// logo zeichnen
		App.draw(spriteLogo);

		float menuMarginTop = 220.f;
		float menuSpace = 60.f;

		// menu items zeichen
		
		for (int i = 0; i < menuListText.size(); i++){
		//for (std::vector<sf::Text*>::iterator i = menuListText.begin(); i != menuListText.end(); ++i) {
			setTextCenter(*menuListText[i], menuMarginTop);
			if (i == menu){
				menuListText[i]->setColor(sf::Color(255, 0, 0, 255));
			}
			else {
				menuListText[i]->setColor(sf::Color(255, 255, 255, 255));
			}

			App.draw(*menuListText[i]);
			App.draw(menuListButton[i]);

			menuMarginTop = menuMarginTop + menuSpace;
		}

		if (alpha == alpha_max)
		{
			if (playing)
			{
				//App.draw(Menu3);
			}
			else
			{
				//App.draw(menuItemPlay);
			}
			//App.draw(Menu2);
		}
		App.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	return (-1);
}