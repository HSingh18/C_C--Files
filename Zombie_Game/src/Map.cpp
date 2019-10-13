//#include "leaker.h"
#include "Map.h"


Map::Map()
{
  background = textureManager::loadTexture("images/BGZombieCC.png");

  src.x = src.y =0;

  src.w = dest.w = 3000;
  src.h = dest.h = 480;

  dest.x = dest.y =0;
}

Map::~Map()
{

}

void Map::DrawMap()
{
  textureManager::Draw(background,src,dest);
}
