#include "ECS.h"
//#include "../leaker.h"


void Entity::addGroup(Group mGroup){
  groupBitSet[mGroup]=true;
  manager->addToGroup(this,mGroup);
}
