/*
 * textureManager.h
 *
 *  Created on: Apr 26, 2018
 *      Author: eliro
 */


#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"

class textureManager {
public:

	static SDL_Texture* loadTexture(const char* path);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flipType);

};

#endif /* TEXTUREMANAGER_H_ */
