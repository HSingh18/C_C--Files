

#ifndef COLLIDERCOMPONENT_H_
#define COLLIDERCOMPONENT_H_

//#include "../leaker.h"

#include "../Game.h"
#include "Components.h"
#include "../Vector2D.h"
#include <string>
#include <SDL2/SDL.h>

class ColliderComponent : public Component
{
public:
  SDL_Rect collider;
  std::string tag;
  bool active;

  TransformComponent* transform;

  ColliderComponent(std::string t)
  {
    tag = t;
    active=true;
  }
  virtual ~ColliderComponent()
  {
    transform = NULL;
    delete transform;
    std::cerr<<"Collider destroy"<<std::endl;
  }

  void init() override
  {
    if(!entity->hasComponent<TransformComponent>())
      entity->addComponent<TransformComponent>();
    transform = &entity->getComponent<TransformComponent>();
    Game::colliders.push_back(this);

  }
  void update() override
  {
    refreshA();
    collider.x = (int)transform->position.x;
    collider.y = (int)transform->position.y;
    collider.w = transform->width * transform->scale -180;
    collider.h = transform->height * transform->scale;

  //  Game::colliders.push_back(this);
  }
  void refreshA()
  {
    Game::colliders.erase(std::remove_if(std::begin(Game::colliders),std::end(Game::colliders),
      [](ColliderComponent* mEntity)
    {
      return !mEntity ->active;
    }),
      std::end(Game::colliders));
  }

};

#endif //COLLIDERCOMPONENT_H_
