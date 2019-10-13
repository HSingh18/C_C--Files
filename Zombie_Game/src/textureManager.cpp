#include "textureManager.h"

SDL_Texture* textureManager::loadTexture(const char* path)
{

	SDL_Surface* tmpSurface = IMG_Load(path);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return tex;
}

void textureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flipType)
{
  SDL_RenderCopyEx(Game::renderer, tex, &src, &dest,0,NULL,flipType);
}
