
#ifndef ZOMBIEMANAGER_H_
#define ZOMBIEMANAGER_H_

#include <vector>
#include <stdio.h>
#include "Game.h"
#include "ECS/ECS.h"
#include <iostream>


class ZombieManager
{
public:

  ZombieManager()
  {
    zombiesNumber=0;
    round=0;
    roundOver=true;
    timePassed =0.0;
    zombieDelay = 1.0;
    currentIndex =0;
    maxRound=3;
  }
  void startNewRound()
  {
    round++;
    currentIndex=0;
    std::cout<<"Round: "<<round<<std::endl;
    zombiesNumber +=round;
    zombies.clear();
    for(int i=0;i<zombiesNumber;i++)
    {
      Entity* tempZombie(Game::manager.addEntity());
      zombies.push_back(tempZombie);
      zombies[i]->addComponent<TransformComponent>(5000.0f,5000.0f);
      zombies[i]->addComponent<ColliderComponent>("zombie");
      zombies[i]->addGroup(groupZombies);
    }
    roundOver=false;
  }
  void spawnZombie()
  {
    if(timePassed<zombieDelay)
      return;
    int posX = Game::Map->getComponent<TransformComponent>().position.x;
    std::cout<<"Zombie Spawned"<<std::endl;
    if(currentIndex%2==0){
      zombies[currentIndex]->getComponent<TransformComponent>().rev=1;
      zombies[currentIndex]->getComponent<TransformComponent>().position.x=posX;
      zombies[currentIndex]->getComponent<TransformComponent>().position.y=200;

      zombies[currentIndex]->addComponent<SpriteComponent>("images/Zombie-x256-3.png",4,200);
      zombies[currentIndex]->addComponent<KeyBoardController>();
    }
    else{
      zombies[currentIndex]->getComponent<TransformComponent>().rev=1;
      zombies[currentIndex]->getComponent<TransformComponent>().position.x=posX+1500;
      zombies[currentIndex]->getComponent<TransformComponent>().position.y=200;
      zombies[currentIndex]->addComponent<SpriteComponent>("images/Zombie-x256-3.png", 4,200, SDL_FLIP_HORIZONTAL);
      zombies[currentIndex]->addComponent<KeyBoardController>();
    }
    currentIndex++;
    timePassed=0.0f;
  }
  void endGame()
  {
    std::cout<<"Game Over!\nYou Win!"<<std::endl;
    Game::manager.m_game->setRun(false);
  }
  void update()
  {
    if(round>maxRound)
        endGame();
    checkForZombies();
    if(roundOver)
      startNewRound();
    if(currentIndex<zombiesNumber){
      timePassed+=0.01;
      spawnZombie();
    }
  }
  void refresh()
  {
    zombies.erase(std::remove_if(std::begin(zombies),std::end(zombies),
      [](Entity* mEntity)
    {
      return !mEntity ->isActive();
    }),
      std::end(zombies));
  }
  void checkForZombies()
  {
    if(zombies.size()==0)
    {
      roundOver=true;
      std::cerr<<"Round Over"<<std::endl;
    }
  }

private:
  std::vector<Entity*> zombies;
  unsigned int zombiesNumber;
  unsigned int round;
  double timePassed;
  double zombieDelay;
  unsigned int currentIndex;
  bool roundOver;
  unsigned int maxRound;

};


#endif //ZOMBIEMANAGER_H_
