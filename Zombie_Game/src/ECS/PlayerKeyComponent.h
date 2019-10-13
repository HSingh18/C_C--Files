

#ifndef PLAYERKEYCOMPONENT_H_
#define PLAYERKEYCOMPONENT_H_

#include "Components.h"
//#include "../leaker.h"


class PlayerKeyComponent : public Component
{
public:
  bool selfState = true;

  void init() override
  {
    selfState = true;
  }
  virtual ~PlayerKeyComponent()
  {
    std::cout<<"PlayerKeyComponent destroyed"<<std::endl;
  }
  void ShotBullets();
  void Flip(SDL_RendererFlip asd);

  void update() override
  {
    if(Game::e.type ==SDL_KEYDOWN)
    {
      switch(Game::e.key.keysym.sym)
      {
        case SDLK_LEFT:
          Flip(SDL_FLIP_HORIZONTAL);
          selfState = false;
          break;
        case SDLK_RIGHT:
          Flip(SDL_FLIP_NONE);
          selfState = true;
          break;
        case SDLK_SPACE:
          ShotBullets();
          break;
        default:
          break;
      }
    }
  }
};

#endif //PLAYERKEYCOMPONENT_H_
