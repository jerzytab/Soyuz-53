#pragma once

#include "SFML/Graphics.hpp"
#include "Main.h"
#include <iostream>
#include <time.h>
#include <list>
#include <math.h>
#include "Animation.h"

using namespace std;
using namespace sf;

class Entity
{
   public:
   float x,y,dx,dy,R,angle;
   bool life;
   std::string name;
   Animation anim;

   Entity()
   {
     life=1;
   }

    void settings(Animation &a,int X,int Y,float Angle=0,int radius=1)
   {
     anim = a;
     x=X; y=Y;
     angle = Angle;
     R = radius;
   }

   virtual void update(){};

   void draw(RenderWindow &app)
   {
     anim.sprite.setPosition(x,y);
     anim.sprite.setRotation(angle+90);
     app.draw(anim.sprite);

     CircleShape circle(R);
     circle.setFillColor(Color(255,0,0,170));
     circle.setPosition(x,y);
     circle.setOrigin(R,R);
     //app.draw(circle);
   }

   virtual ~Entity(){};
};


class asteroid: public Entity
{
   public:
   asteroid()
   {
     dx=rand()%8-4;
     dy=rand()%8-4;
     name="asteroid";
   }

   void update()
   {
     x+=dx;
     y+=dy;

     if (x>W) x=0;  if (x<0) x=W;
     if (y>H) y=0;  if (y<0) y=H;
   }

};
