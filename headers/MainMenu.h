#include "Main.h"

using namespace std;
using namespace sf;

MainMenu::MainMenu(float width, float height)
{
	if (!font.loadFromFile("fonts/FounderPersonal-Bold.ttf"))
	{
		cout << "No font is here";
	}

	mainMenu[0].setFont(font);
	mainMenu[0].setColor(Color::Red);
	mainMenu[0].setString("Play");
    mainMenu[0].setCharacterSize(70);
	mainMenu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	mainMenu[1].setFont(font);
	mainMenu[1].setColor(sf::Color::White);
	mainMenu[1].setString("Options");
    mainMenu[1].setCharacterSize(70);
	mainMenu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(Color::White);
    mainMenu[2].setString("Leaderboard");
    mainMenu[2].setCharacterSize(70);
    mainMenu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	mainMenu[3].setFont(font);
	mainMenu[3].setColor(sf::Color::White);
	mainMenu[3].setString("Exit");
    mainMenu[3].setCharacterSize(70);
	mainMenu[3].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 4));

	selectedItemIndex = 0;
}


MainMenu::~MainMenu()
{
}

void MainMenu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(mainMenu[i]);
	}
}

void MainMenu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		mainMenu[selectedItemIndex].setColor(Color::White);
		selectedItemIndex--;
		mainMenu[selectedItemIndex].setColor(Color::Red);
	}
}

void MainMenu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		mainMenu[selectedItemIndex].setColor(Color::White);
		selectedItemIndex++;
		mainMenu[selectedItemIndex].setColor(Color::Red);
	}
}
