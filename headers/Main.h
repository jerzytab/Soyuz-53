#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;
using namespace sf;

#define MAX_NUMBER_OF_ITEMS 4

class MainMenu
{
public:
	MainMenu(float width, float height);

	void draw(RenderWindow &window);
	void MoveUp();
	void MoveDown();

	int GetPressedItem() {
	    return selectedItemIndex;
    }

    ~MainMenu();

private:
	int selectedItemIndex;
	Font font;
	Text mainMenu[MAX_NUMBER_OF_ITEMS];

};
