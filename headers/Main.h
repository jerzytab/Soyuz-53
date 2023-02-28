#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <time.h>
#include <list>
#include <math.h>

using namespace std;
using namespace sf;

const int W = 1200;
const int H = 800;

float DEGTORAD = 0.017453f;

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

