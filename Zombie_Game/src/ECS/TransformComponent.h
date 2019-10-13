

#ifndef TRANSFROMCOMPONENT_H_
#define TRANSFROMCOMPONENT_H_

#include "Components.h"
#include "../Vector2D.h"
#include "../Game.h"
//#include "../leaker.h"

#include <iostream>

class TransformComponent : public Component
{

public:
  Vector2D position;

  Vector2D velocity;

  int height;
  int width;
  int scale =1;


  int speed =7;
  int rev =1;
  TransformComponent()
  {
    position.x =0.0f;
    position.y=0.0f;
  }

  TransformComponent(float x, float y, int direc =1 , int Width=256,int Height=256)
  {
    position.x = x;
    position.y =y;
    width = Width;
    height = Height;


    rev = direc;
  }

  virtual ~TransformComponent(){
    std::cerr<<"TransformComponent destroy"<<this<<std::endl;
  }

  void init() override
  {
    velocity.x =0;
    velocity.y =0;
  }
  void update() override
  {
    position.x+= velocity.x * speed;
    if(position.x>0 && entity->hasGroup(groupMap))
      position.x=0;
    if(position.x<-2360)
      position.x=-2360;
    if(entity->hasGroup(groupZombies) || entity->hasGroup(groupBullets))
      position.x+=rev;
  }

};

#endif //TRANSFORMCOMPONENT_H_
