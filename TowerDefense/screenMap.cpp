#include "screenMap.hpp"

screenMap::screenMap(void){}

int screenMap::Run(sf::RenderWindow &App)
{
	sf::RectangleShape* button;
	sf::Event Event;
	sf::Text headline;
	sf::Text* title;
	sf::Font font;
	sf::Texture bgTexture;
	sf::Texture image;

	std::map<std::string, std::string> menuItems;
	std::vector<sf::Text*> menuListTitles;
	std::vector<sf::RectangleShape*> menuListButton;
	std::vector<sf::Texture*> menuListButtonTextures;

	bool Running = true;
	float menuMarginleft = 220.f;
	float menuSpace = 60.f;

	headline.setColor(getColor("default"));
	headline.setFont(*getMainFont());
	headline.setCharacterSize(48);
	headline.setPosition({ 0, 0 });
	headline.setString("Wo möchtest du spielen?");
	setTextCenter(headline, 80.f);

	bgTexture.loadFromFile("media/img/main.png");
	mainBg.setTexture(bgTexture);

	std::vector<std::map<std::string, std::string>*> results;
	Model *model = new Model();
	results = model->getMaps();

	generateMenuItems(menuItems, results);

	float buttonSpace = 30.f;
	int imageWidth = 210;
	int imageHeight = 280;
	float leftStart = (1024 - ((imageWidth)* menuItems.size()) - (buttonSpace * (menuItems.size() - 1))) / 2 + imageWidth / 2;
	float imagePosition = leftStart;
	int count = 0;
	sf::Texture *img;
	for (std::map<std::string, std::string>::iterator curr = menuItems.begin(); curr != menuItems.end(); ++curr){

		menuListButtonTextures.push_back(new sf::Texture());
		menuListButtonTextures[count]->loadFromFile(curr->second);

		sf::RectangleShape* button = new sf::RectangleShape(sf::Vector2f(imageWidth, imageHeight));
		button->setOutlineThickness(2);
		button->setOutlineColor(sf::Color(1, 217, 232));
		button->setTexture(menuListButtonTextures[count], true);

		sf::FloatRect textRect = button->getLocalBounds();
		button->setOrigin(textRect.width / 2, textRect.height / 2);

		button->setPosition(sf::Vector2f(imagePosition, (SCREENHEIGHT / 2.0f)));
		menuListButton.push_back(button);

		title = new sf::Text();
		title->setColor(getColor("default"));
		title->setFont(*getMainFont());
		title->setCharacterSize(18);
		title->setPosition(sf::Vector2f(imagePosition, (SCREENHEIGHT / 2.0f) + (imageHeight / 2) + 30.f));
		title->setString(curr->first);

		textRect = title->getLocalBounds();
		title->setOrigin(textRect.width / 2, textRect.height / 2);

		menuListTitles.push_back(title);

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
					return 1;
				}
			}

			if (Event.type == sf::Event::MouseMoved){
				itemPrev = onButtonHover(Event, menuListButton, "move");
				if (itemPrev != item){
					playSound("button");
				}
				item = itemPrev;
			}

			if (Event.type == sf::Event::MouseButtonPressed)
			{
				if (Event.mouseButton.button == sf::Mouse::Left)
				{
					item = onButtonHover(Event, menuListButton, "press");
					cScreen::selectedMap = results[item];
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
				menuListButton[menuItemCount]->setOutlineColor(getColor("hover2"));
			}
			else {
				menuListButton[menuItemCount]->setOutlineColor(sf::Color(255, 255, 255, 255));
			}
			
			App.draw(*menuListButton[menuItemCount]);
			App.draw(*menuListTitles[menuItemCount]);

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

void screenMap::generateMenuItems(std::map<std::string, std::string> &menuItems, std::vector<std::map<std::string, std::string>*> results){
	for (int i = 0; i < results.size(); i++){
		std::map<std::string, std::string>* entry = results[i];
		std::string name;
		std::string path;
		for (std::map<std::string, std::string>::iterator it = entry->begin(); it != entry->end(); ++it) {
			if (it->first == "name"){
				name = it->second;
			}
			else if (it->first == "image"){
				path = it->second;
			}
		}

		menuItems.insert(std::make_pair(name, path));
	}
}