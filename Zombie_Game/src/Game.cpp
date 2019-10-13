/*
 * Game.cpp
 *
 *  Created on: Apr 24, 2018
 *      Author: eliro
 */

#include "Game.h"
#include "textureManager.h"
#include "ECS/Components.h"
#include "ZombieManager.h"
#include "Collision.h"
//#include "leaker.h"

#include "Vector2D.h"
#include <iostream>


SDL_Event Game::e;
SDL_Renderer* Game::renderer =NULL;
Manager Game::manager;
std::vector<ColliderComponent*>Game::colliders;
Entity* Game::Map(Game::manager.addEntity());

ZombieManager* zombieManager;
auto Player(Game::manager.addEntity());




Game::Game() {
	// TODO Auto-generated constructor stub
	window = NULL;
	renderer = NULL;
	backgroundTex = NULL;
	running = false;
	cnt =0;

}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

void Game::init(const char* title, int xpos, int ypos,int width, int height, bool fullscreen)
{
	int flag =0;
	if(fullscreen)
		flag =SDL_WINDOW_FULLSCREEN;
	if(SDL_Init(SDL_INIT_EVERYTHING)==0)
	{
		std::cout<<"Subsystem initialize"<<std::endl;
		window =SDL_CreateWindow(title, xpos, ypos, width, height,flag);
		if(window)
		{
			std::cout<<"Window initialized"<<std::endl;
		}
		renderer = SDL_CreateRenderer(window,-1,0);
		if(renderer)
		{
			SDL_SetRenderDrawColor(renderer,255,255,255,255);
			std::cout<<"Renderer created"<<std::endl;
		}
		running = true;
	}

	Game::Map->addComponent<TransformComponent>(0.0f,0.0f,1, 3000,480);
	Game::Map->addComponent<SpriteComponent>("images/BGZombieCC-2.png", SDL_FLIP_NONE);
	Game::Map->addComponent<KeyBoardController>();
	Game::Map->addGroup(groupMap);

	Player->addComponent<TransformComponent>(180.0f,200.0f);
	Player->addComponent<SpriteComponent>("images/Main-Character-x256-3.png",4,200);
	Player->addComponent<ColliderComponent>("Player");
	Player->addComponent<MagazineComponent>();
	Player->addComponent<PlayerKeyComponent>();
	Player->addComponent<HealthBarComponent>();
	Player->addGroup(groupPlayers);

	Player->setPlayer(true);

	zombieManager = new ZombieManager();
	Game::manager.m_game=this;

}

void Game::handleEvents()
{

	SDL_PollEvent(&e);
	switch(e.type)
	{
		case SDL_QUIT:
			running=false;
			break;
		default:
			break;
	}

}

void Game::update()
{
	Game::manager.refresh();
	Game::manager.update();
	zombieManager->refresh();
	zombieManager->update();


	for(auto& cc : colliders){
		if(Collision::AABB(Player->getComponent<ColliderComponent>(), *cc))
		{
			if(cc->tag=="zombie"){
				if((cc->entity->getComponent<SpriteComponent>().flipType==SDL_FLIP_NONE))
					cc->entity->getComponent<TransformComponent>().position.x-=1;
				else
					cc->entity->getComponent<TransformComponent>().position.x+=1;
				Player->getComponent<HealthBarComponent>().Hit(*this);
			}
		}
	}
	for(auto& bb : Player->getComponent<MagazineComponent>().Magazine)
	{
		for(auto cc : colliders)
		{
			if(cc->tag!="zombie")
				continue;
			if(Collision::AABB(bb->getComponent<ColliderComponent>().collider,cc->collider))
			{
					cc->active=false;
					cc->entity->destroy();
					bb->destroy();
					break;

			}
		}
	}



}

std::vector<Entity*>& back(Game::manager.getGroup(groupMap));
std::vector<Entity*>& players(Game::manager.getGroup(groupPlayers));
std::vector<Entity*>& zombies(Game::manager.getGroup(groupZombies));
std::vector<Entity*>& magazine(Game::manager.getGroup(groupBullets));

void Game::render()
{
	SDL_RenderClear(renderer);

	for(auto& t : back)
		t->draw();
	for(auto& p : players)
		p->draw();
	for(auto& z : zombies)
		z->draw();
	for(auto& b : magazine)
		b->draw();


	SDL_RenderPresent(renderer);

}

void Game::clean()
{
	SDL_DestroyWindow(window);

	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout<<"Game clean"<<std::endl;
}
