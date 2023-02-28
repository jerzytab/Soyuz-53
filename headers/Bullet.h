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

class bullet: public Entity
{
   public:
   bullet()
   {
     name="bullet";
   }

   void  update()
   {
     dx=cos(angle*DEGTORAD)*6;
     dy=sin(angle*DEGTORAD)*6;
     // angle+=rand()%7-3;
     x+=dx;
     y+=dy;

     if (x>W || x<0 || y>H || y<0) life=0;
   }

};
