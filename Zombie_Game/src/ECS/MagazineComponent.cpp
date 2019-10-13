#include "MagazineComponent.h"
//#include "../leaker.h"


bool MagazineComponent::checkState()
{
  return (entity->getComponent<PlayerKeyComponent>().selfState==false);
}

void MagazineComponent::Shots()
{
  if(currentIndex>29)
  {
    std::cout<<"No ammo"<<std::endl;
    return;
  }
  int posX = entity->getComponent<TransformComponent>().position.x;

  //if(timePassed<shootDelay)
  //  return;
  if(checkState()){
    Magazine[currentIndex]->getComponent<TransformComponent>().position.x=posX;
    Magazine[currentIndex]->getComponent<TransformComponent>().rev=-5;
    Magazine[currentIndex]->addComponent<SpriteComponent>("images/Bullet.png");
    Magazine[currentIndex]->addComponent<KeyBoardController>();
  }
  else{
    Magazine[currentIndex]->getComponent<TransformComponent>().position.x=posX;
    Magazine[currentIndex]->getComponent<TransformComponent>().rev=5;
    Magazine[currentIndex]->addComponent<SpriteComponent>("images/Bullet.png",SDL_FLIP_HORIZONTAL);
    Magazine[currentIndex]->addComponent<KeyBoardController>();
  }
  currentIndex++;
  timePassed=0.0f;
}
