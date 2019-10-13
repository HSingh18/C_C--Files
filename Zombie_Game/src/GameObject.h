/*
 * GameObject.h
 *
 *  Created on: Apr 26, 2018
 *      Author: eliro
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Game.h"
#include <SDL2/SDL.h>

class GameObject {
public:
	GameObject(const char* textureSheet, int x, int y);
	virtual ~GameObject();

	void Update();
	void Render();

private:

	int xPos;
	int yPos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;


};

#endif /* GAMEOBJECT_H_ */
