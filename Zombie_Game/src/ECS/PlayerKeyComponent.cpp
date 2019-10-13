#include "PlayerKeyComponent.h"
//#include "../leaker.h"


void PlayerKeyComponent::ShotBullets()
{
  entity->getComponent<MagazineComponent>().Shots();
}

void PlayerKeyComponent::Flip(SDL_RendererFlip asd)
{
  entity->getComponent<SpriteComponent>().flipType=asd;
}
