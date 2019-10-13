

#ifndef COLLISION_H_
#define COLLISION_H_

#include <SDL2/SDL.h>
#include "ECS/Components.h"
//#include "leaker.h"



class Collision
{
public:
  static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB)
  {
    if(
      recA.x + recA.w>=recB.x &&
      recB.x + recB.w>=recA.x &&
      recA.y + recA.h>=recB.y &&
      recB.y + recB.h>=recA.y
    )
      return true;
    return false;
  }
  static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB)
  {
    if(AABB(colA.collider, colB.collider))
    {
      return true;
    }
    return false;
  }

};


#endif //COLLISION_H_
