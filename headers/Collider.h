#pragma once

#include "SFML/Graphics.hpp"
#include "Main.h"
#include "Asteroid.h"
#include <iostream>
#include <time.h>
#include <list>
#include <math.h>

using namespace std;
using namespace sf;

bool isCollide(Entity *a,Entity *b)
{
  return (b->x - a->x)*(b->x - a->x)+
         (b->y - a->y)*(b->y - a->y)<
         (a->R + b->R)*(a->R + b->R);
}
