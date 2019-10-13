#ifndef MAGAZINE_H
#define MAGAZINE_H

#include<vector>
#include<SDL2/SDL.h>
#include"Components.h"
//#include "../leaker.h"


class MagazineComponent: public Component
{
public:

  MagazineComponent()
  {
    shootDelay = 1.0;
    timePassed = 0.0;
    currentIndex = 0;
    Clip();
  }
  virtual ~MagazineComponent()
  {
    Magazine.clear();
    std::cout<<"Magazine destroyed"<<std::endl;
  }

  void Clip(){
    currentIndex=0;
    Magazine.clear();
    for(int i = 0; i <30; i++)
    {
    int posX = entity->getComponent<TransformComponent>().position.x;
    Entity* Bullet(Game::manager.addEntity());
    Magazine.push_back(Bullet);
    Magazine[i]->addComponent<TransformComponent>(-5000.0f,200.0f);
    Magazine[i]->addComponent<ColliderComponent>("bullet");
    Magazine[i]->addGroup(groupBullets);
    }

  }
  bool checkState();
  void Shots();
  void update() override{
    timePassed += 0.01;
    for(auto* bullet : Magazine)
    {
      bullet->update();
    }
  }
  std::vector<Entity*> Magazine;

private:
  double shootDelay;
  double timePassed;
  unsigned int currentIndex;









};




#endif //MAGAZINE_H
