/*
 * GameObject.cpp
 *
 *  Created on: Apr 26, 2018
 *      Author: eliro
 */

#include <iostream>
#include "GameObject.h"
#include "textureManager.h"
//#include <SDL2/SDL.h>

GameObject::GameObject(const char* textureSheet, int x, int y) {
	// TODO Auto-generated constructor stub
	objTexture = textureManager::loadTexture(textureSheet);

	xPos =x;
	yPos =y;
}

GameObject::~GameObject() {
	// TODO Auto-generated destructor stub
}

void GameObject::Update()
{

	xPos++;
	yPos++;

	srcRect.w=32;
	srcRect.h =32;

	srcRect.x=0;
	srcRect.y=0;

	destRect.x=xPos;
	destRect.y=yPos;
	destRect.w=srcRect.w*2;
	destRect.h=srcRect.h*2;

}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
