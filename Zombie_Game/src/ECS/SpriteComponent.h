
#include <SDL2/SDL.h>

#ifndef SPRITECOMPONENT_H_
#define SPRITECOMPONENT_H_
#include "Components.h"
//#include "../leaker.h"

#include "TransformComponent.h"


class SpriteComponent : public Component
{

private:
  TransformComponent* transform;
  SDL_Rect srcRect, destRect;
  SDL_Texture* texture;

  bool animated = false;
  int frames = 0;
  int speed = 100;

public:
  SDL_RendererFlip flipType;
  SpriteComponent() = default;
  SpriteComponent(const char* path, SDL_RendererFlip flipT= SDL_FLIP_NONE){
    setTex(path);
    flipType=flipT;
  }
  SpriteComponent(const char* path,int nFrames, int mSpeed, SDL_RendererFlip flipT= SDL_FLIP_NONE){
	  animated = true;
	  frames = nFrames;
	  speed = mSpeed;
      setTex(path);


      flipType=flipT;
    }


  virtual ~SpriteComponent(){
    SDL_DestroyTexture(texture);
    transform = NULL;
    delete transform;
    std::cout<<"SpriteComponent destroyed"<<std::endl;
  }

  void setTex(const char* path)
  {
    texture =textureManager::loadTexture(path);
  }

  void init() override
  {
    transform = &entity->getComponent<TransformComponent>();
    srcRect.x = srcRect.y =0;

    srcRect.w = transform->width;
    srcRect.h =transform->height;
  }
  void update() override
  {
	if (animated)
	{
		srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
	}

    destRect.x = (int)transform->position.x;
    destRect.y = (int)transform->position.y;
    destRect.w = transform->width*transform->scale;
    destRect.h = transform->height*transform->scale;
  }

  void draw() override
  {
    textureManager::Draw(texture,srcRect,destRect,flipType);
  }

};



#endif //SPRITECOMPONENT_H_
