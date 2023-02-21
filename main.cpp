#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "MainMenu.h"

using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(960, 720), "Menu", Style::Default);
	MainMenu menu(window.getSize().x, window.getSize().y);
    window.setMouseCursorVisible(false);

    RectangleShape background;
    background.setSize(Vector2f(960, 720));
    Texture Maintexture;
    Maintexture.loadFromFile("img/backgroundMainMenu.jpg");
    background.setTexture(&Maintexture);

    Music music;
    if (!music.openFromFile("music/music0.ogg"))
	{
		cout << "No music is here";
	}
	music.play();

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::KeyReleased:
				switch (event.key.code)
				{
				case Keyboard::Up:
					menu.MoveUp();
					break;

				case Keyboard::Down:
					menu.MoveDown();
					break;

				case Keyboard::Return:
                    RenderWindow Play(VideoMode(960, 720), "Sputnik 53");
                    RenderWindow OPTIONS(VideoMode(960, 720), "OPTIONS");
                    RenderWindow ABOUT(VideoMode(960, 720), "LEADERBOARD");

					switch (menu.GetPressedItem())
					{
					case 0:
						std::cout << "Play button has been pressed" << std::endl;
						break;
					case 1:
                        while (OPTIONS.isOpen()) {
                            Event aevent;
                            while (OPTIONS.pollEvent(aevent)) {
                                if (aevent.type == Event::Closed) {
                                    OPTIONS.close();
                                }
                                if (aevent.type == Event::KeyPressed) {
                                    if (aevent.key.code == Keyboard::Escape) {
                                        OPTIONS.close();
                                    }
                                }
                            }
                            Play.close();
                            OPTIONS.clear();
                            ABOUT.close();
                            OPTIONS.display();
                        }
                        break;
					case 2:
                        while (ABOUT.isOpen()) {
                            Event aevent;
                            while (ABOUT.pollEvent(aevent)) {
                                if (aevent.type == Event::Closed) {
                                    ABOUT.close();
                                }
                                if (aevent.type == Event::KeyPressed) {
                                    if (aevent.key.code == Keyboard::Escape) {
                                        ABOUT.close();
                                    }
                                }
                            }
                            Play.close();
                            OPTIONS.clear();
                            ABOUT.clear();
                            ABOUT.display();
                        }
                        break;
                    case 3:
                        window.close();
						break;
					}

					break;
				}

				break;
			case Event::Closed:
				window.close();

				break;

			}
		}

		window.clear();
		window.draw(background);
		menu.draw(window);
		window.display();
	}
}
