#include <iostream>
#include "cScreen.hpp"
#include "screen_1.hpp"
#include "globals.hpp"
#include <SFML/Graphics.hpp>


screen_1::screen_1(void)
{

}

int screen_1::Run(sf::RenderWindow &App)
{
	sf::RectangleShape* button;
	sf::Event Event;
	sf::Text headline;
	sf::Font font;
	sf::Texture bgTexture;
	sf::Texture image;

	std::map<std::string, std::string> menuItems;
	std::vector<sf::RectangleShape*> menuListButton;
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
	headline.setString("Waehle dein Volk!");
	setTextCenter(headline, 80.f);


	bgTexture.loadFromFile("menuMain.jpg");
	mainBg.setTexture(bgTexture);

	menuItems.insert(std::make_pair("Menschen", "human.png"));
	menuItems.insert(std::make_pair("Aliens", "alien.png"));
	menuItems.insert(std::make_pair("Robots", "robot.png"));

	//image.loadFromFile("logo.png");


	float buttonSpace = 30.f;
	int imageWidth = 210;
	float leftStart = (1024 - ((imageWidth)* menuItems.size()) - (buttonSpace * (menuItems.size() - 1))) / 2 + imageWidth / 2;
	float imagePosition = leftStart;
	int count = 0;
	sf::Texture *img;
	for (std::map<std::string, std::string>::iterator curr = menuItems.begin(); curr != menuItems.end(); ++curr){

		menuListButtonTextures.push_back(new sf::Texture());
		menuListButtonTextures[count]->loadFromFile(curr->second);

		sf::RectangleShape* button = new sf::RectangleShape(sf::Vector2f(imageWidth, 280));
		//button.setFillColor(sf::Color::Transparent);
		button->setOutlineThickness(2);
		button->setOutlineColor(sf::Color(1, 217, 232));
		button->setTexture(menuListButtonTextures[count], true);

		sf::FloatRect textRect = button->getLocalBounds();
		button->setOrigin(textRect.width / 2, textRect.height / 2);

		button->setPosition(sf::Vector2f(imagePosition, (756 / 2.0f)));

		menuListButton.push_back(button);

		imagePosition = imagePosition + imageWidth + buttonSpace;
		count++;
	}

	int item = -1;
	int itemPrev = -1;

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
				itemPrev = onButtonHover(Event, menuListButton, "move");
				if (itemPrev != item){
					playButtonSound();
				}
				item = itemPrev;
			}

			if (Event.type == sf::Event::MouseButtonPressed)
			{
				if (Event.mouseButton.button == sf::Mouse::Left)
				{
					item = onButtonHover(Event, menuListButton, "press");
					return 3;
				}
			}

		}

		//Clearing screen
		App.clear(sf::Color(0, 0, 0, 0));

		App.draw(mainBg);

		//App.draw(buttonText);


		int menuItemCount = 0;
		for (int i = 0; i < menuListButton.size(); i++){
		//for (std::vector<sf::RectangleShape>::iterator i = menuListButton.begin(); i != menuListButton.end(); ++i) {
			if (menuItemCount == item){
				menuListButton[menuItemCount]->setOutlineColor(sf::Color(255, 0, 0, 255));
			}
			else {
				menuListButton[menuItemCount]->setOutlineColor(sf::Color(255, 255, 255, 255));
			}

			App.draw(*menuListButton[menuItemCount]);

			menuItemCount++;
		}

		App.draw(headline);

		//Drawing

		//App.draw(Rectangle);
		App.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	return -1;
}