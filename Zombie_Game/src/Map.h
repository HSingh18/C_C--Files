


#ifndef MAP_H_
#define MAP_H_

#include <SDL2/SDL.h>
#include "textureManager.h"

class Map
{
public:
  Map();
  virtual ~Map();

  void DrawMap();

  SDL_Rect src, dest;

private:


  SDL_Texture* background;

};




#endif //MAP_H_
