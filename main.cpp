#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <time.h>
#include <list>
#include <math.h>
#include <sstream>

#include "headers/MainMenu.h"
#include "headers/Main.h"
#include "headers/Player.h"
#include "headers/Collider.h"
#include "headers/Bullet.h"
#include "headers/Asteroid.h"

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(960, 720), "Menu", Style::Default); // Fullscreen, Default
    MainMenu menu(window.getSize().x, window.getSize().y);
    window.setMouseCursorVisible(false);

    Image icon;
    icon.loadFromFile("images/logo.png");
    window.setIcon(32, 32, icon.getPixelsPtr());

    RectangleShape background;
    background.setSize(Vector2f(960, 720));
    Texture Maintexture;
    Maintexture.loadFromFile("images/backgroundMainMenu.jpg");
    background.setTexture(&Maintexture);

    RectangleShape t1, t4, t6;
    Texture spacecraft, asteroid1, asteroid2, t5;

    spacecraft.loadFromFile("images/spaceship/space2.png");
    t1.setTexture(&spacecraft);

    asteroid1.loadFromFile("images/asteroids/asteroid3.png");
    t4.setTexture(&asteroid1);

    t5.loadFromFile("images/spaceship/fire_balls1.png");

    asteroid2.loadFromFile("images/asteroids/asteroid6.png");
    t6.setTexture(&asteroid2);

    spacecraft.setSmooth(true);

    Animation sRock(asteroid1, 0, 0, 64, 64, 16, 0.2);
    Animation sRock_small(asteroid2, 0, 0, 64, 64, 16, 0.2);
    Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);
    Animation sPlayer(spacecraft, 40, 0, 40, 40, 1, 0);
    Animation sPlayer_go(spacecraft, 40, 40, 40, 40, 1, 0);

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
                    RenderWindow Play(VideoMode(W, H), "Sputnik 53", Style::Fullscreen);
                    Play.setFramerateLimit(60);
                    RenderWindow OPTIONS(VideoMode(960, 720), "OPTIONS");
                    RenderWindow ABOUT(VideoMode(960, 720), "LEADERBOARD");

                    if (Play.isOpen())
                    {
                        music.pause();
                    }

                    srand(time(0));

                    std::list<Entity *> entities;

                    // Generowanie asteroid tj max size(15)
                    for (int i = 0; i < 5; i++)
                    {
                        asteroid *a = new asteroid();
                        a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
                        entities.push_back(a);
                    }

                    // Generowanie statku
                    player *p = new player();
                    p->settings(sPlayer, 200, 200, 0, 20);
                    entities.push_back(p);

                    int score = 0;

                    ostringstream score_screen;
                    score_screen << "Score: " << score;

                    Font score_font;
                    if (!score_font.loadFromFile("fonts/TrenchThin.ttf"))
                    {
                        cout << "No font is here";
                    }

                    Text text;
                    text.setFont(score_font);
                    text.setString(score_screen.str());
                    text.setCharacterSize(40);

                    switch (menu.GetPressedItem())
                    {
                    case 0:

                        while (Play.isOpen())
                        {
                            Event aevent;
                            while (Play.pollEvent(aevent))
                            {
                                if (aevent.type == Event::Closed)
                                {
                                    Play.close();
                                }
                                if (aevent.type == Event::KeyPressed)
                                {
                                    if (aevent.key.code == Keyboard::Escape)
                                    {
                                        Play.close();
                                    }
                                }
                            }
                            Music fire, bangLarge, bangSmall, thrust;
                            if (!fire.openFromFile("music/fire.wav"))
                            {
                                cout << "No music is here";
                            }
                            if (!bangLarge.openFromFile("music/bangLarge.wav"))
                            {
                                cout << "No music is here";
                            }
                            if (!bangSmall.openFromFile("music/bangSmall.wav"))
                            {
                                cout << "No music is here";
                            }
                            if (!thrust.openFromFile("music/thrust.wav"))
                            {
                                cout << "No music is here";
                            }

                            if (Mouse::isButtonPressed(Mouse::Left))
                            {
                                bullet *b = new bullet();
                                b->settings(sBullet, p->x, p->y, p->angle, 1);
                                entities.push_back(b);
                                fire.play();
                            }
                            if (Keyboard::isKeyPressed(Keyboard::D)) { p->angle += 3; }
                            if (Keyboard::isKeyPressed(Keyboard::A)) { p->angle -= 3; }
                            if (Keyboard::isKeyPressed(Keyboard::W)) { p->thrust = true; /*thrust.play();*/ }
                            else { p->thrust = false; }

                            for (auto a : entities)
                                for (auto b : entities)
                                {
                                    if (a->name == "asteroid" && b->name == "bullet")
                                        if (isCollide(a, b))
                                        {
                                            a->life = false;
                                            b->life = false;

                                            bangLarge.play();

                                            score += 10;
                                            score_screen.str("");
                                            score_screen << "Score: " << score;
                                            text.setString(score_screen.str());

                                            for (int i = 0; i < 2; i++)
                                            {
                                                if (a->R == 15)
                                                    continue;
                                                Entity *e = new asteroid();
                                                e->settings(sRock_small, a->x, a->y, rand() % 360, 15);
                                                entities.push_back(e);
                                            }
                                        }

                                    if (a->name == "player" && b->name == "asteroid")
                                        if (isCollide(a, b))
                                        {
                                            b->life = false;

                                            // Sprawdzanie kolizji
                                            p->settings(sPlayer, W / 2, H / 2, 0, 1);
                                            p->dx = 0;
                                            p->dy = 0;
                                        }
                                }

                            if (p->thrust)
                                p->anim = sPlayer_go;
                            else
                                p->anim = sPlayer;

                            // Elsplozja statku
                            for (auto e : entities)
                                if (e->name == "explosion")
                                    if (e->anim.isEnd())
                                        e->life = 0;

                            if (rand() % 150 == 0)
                            {
                                asteroid *a = new asteroid();
                                a->settings(sRock, 0, rand() % H, rand() % 360, 25);
                                entities.push_back(a);
                            }

                            for (auto i = entities.begin(); i != entities.end();)
                            {
                                Entity *e = *i;

                                e->update();

                                if (e->life == false)
                                {
                                    bangSmall.play();

                                    score += 5;
                                    score_screen.str("");
                                    score_screen << "Score: " << score;
                                    text.setString(score_screen.str());

                                    i = entities.erase(i);
                                    delete e;
                                }
                                else
                                    i++;
                            }

                            OPTIONS.close();
                            ABOUT.close();
                            Play.clear();
                            for (auto i : entities)
                                i->draw(Play);
                            Play.draw(text);
                            Play.display();
                            music.play();
                        }
                        break;
                    case 1:
                        while (OPTIONS.isOpen())
                        {
                            Event aevent;
                            while (OPTIONS.pollEvent(aevent))
                            {
                                if (aevent.type == Event::Closed)
                                {
                                    OPTIONS.close();
                                }
                                if (aevent.type == Event::KeyPressed)
                                {
                                    if (aevent.key.code == Keyboard::Escape)
                                    {
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
                        while (ABOUT.isOpen())
                        {
                            Event aevent;
                            while (ABOUT.pollEvent(aevent))
                            {
                                if (aevent.type == Event::Closed)
                                {
                                    ABOUT.close();
                                }
                                if (aevent.type == Event::KeyPressed)
                                {
                                    if (aevent.key.code == Keyboard::Escape)
                                    {
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
