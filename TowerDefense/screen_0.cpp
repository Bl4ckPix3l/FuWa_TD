#include "screen_0.hpp"

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
		if (cScreen::isPlaying){
			route = 3;
		}
		else {
			route = 1;
		}
		break;
	}
	return route;
}

int screen_0::Run(sf::RenderWindow &App)
{
	bool Running = true;
	int alpha = 0;
	int menu = 0;

	
	sf::Texture Texture;
	sf::Texture logo;
	sf::Sprite spriteLogo;

	sf::Text menuItemPlay;
	sf::Text menuItemSettings;
	sf::RectangleShape* button;

	std::vector<std::string> menuItems;
	std::vector<sf::Text*> menuListText;
	std::vector<sf::RectangleShape*> menuListButton;

	if (cScreen::isPlaying){
		menuItems.push_back("Fortfahren");
	}
	else {
		menuItems.push_back("Spielen");
	}
	
	menuItems.push_back("Beenden");


	playMainMusic();

	float menuMarginTop = 300.f;
	float menuSpace = 70.f;

	for (int i = 0; i < menuItems.size(); i++){
		sf::Text* MenuTest = new sf::Text();
		MenuTest->setFont(*getMainFont());
		MenuTest->setCharacterSize(26);
		MenuTest->setString(menuItems[i]);
		MenuTest->setColor(getColor("default"));
		menuListText.push_back(MenuTest);

		sf::RectangleShape * button = new sf::RectangleShape(sf::Vector2f(250, 40));
		button->setFillColor(sf::Color::Transparent);
		button->setOutlineThickness(3);
		button->setOutlineColor(getColor("default"));
		setButtonCenter(*button, menuMarginTop + 12);
		menuListButton.push_back(button);

		menuMarginTop = menuMarginTop + menuSpace;
	}

	// texturen laden
	if (!Texture.loadFromFile("media/img/main.png")){
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

	int menuPrev = 1;

	sf::Event Event;

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
					playSound("button");
					menu++;
					if (menu == menuListText.size()){
						menu = 0;
					}
					break;
				case sf::Keyboard::Down:
					playSound("button");
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
					playSound("button");
				}
				menu = menuPrev;
			}

			if (Event.type == sf::Event::MouseButtonPressed)
			{
				if (Event.mouseButton.button == sf::Mouse::Left)
				{
					menu = onButtonHover(Event, menuListButton, "press");
					if (menu >= 0){
						return getMenuRouting(menu);
					}
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

		float menuMarginTop = 300.f;
		float menuSpace = 70.f;

		// menu items zeichen
		
		for (int i = 0; i < menuListText.size(); i++){
		//for (std::vector<sf::Text*>::iterator i = menuListText.begin(); i != menuListText.end(); ++i) {
			setTextCenter(*menuListText[i], menuMarginTop);
			if (i == menu){
				menuListText[i]->setColor(getColor("hover2"));
			}
			else {
				menuListText[i]->setColor(sf::Color(255, 255, 255, 255));
			}

			App.draw(*menuListText[i]);
			App.draw(*menuListButton[i]);

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