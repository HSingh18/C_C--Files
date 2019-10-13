#include "Components.h"
#include "TransformComponent.h"
#include "../Game.h"

#ifndef CAMERACOMPONENT_H_
#define CAMERACOMPONENT_H_

class CameraComponent : public Component
{
public:
  TransformComponent *transform;

  void init() override
  {
    transform = &entity->getComponent<TransformComponent>();
    camera = {0,0,SCREEN_WITDH,SCREEN_HEIGHT};
  }
  void setCamera()
  {
    camera.x = (transform.x +32)-Game::SCREEN_WITDH/2;
    camera.y = (transform.y+32)-Game::SCREEN_HEIGHT/2;

    if(camera.x<0)
      camera.x =0;
    if(camera.x> 3000 - camera.w)
      camera.x = 3000-camera.w;
  }
  void update() override
  {
    setCamera();
  }

private:
  SDL_Rect camera;

};


#endif //CAMERACOMPONENT_H_
