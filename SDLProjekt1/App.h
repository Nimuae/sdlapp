#include <SDL.h>
#include <SDL_timer.h>
#include <iostream>
#include <vector>

#include "GameObject.h"

#pragma once
class App
{
public:
	App();
	App(std::string title, unsigned int width, unsigned int height);
	~App();

	int init(std::string title, unsigned int width, unsigned int height);
	void addObject(GameObject *obj);

	void(*ErrorFunc)() = NULL;

private:
	SDL_Window *window = NULL;
	SDL_Surface *screen = NULL;
	SDL_Renderer *renderer = NULL;

	std::vector<GameObject*> gameObjects = std::vector<GameObject*>();

	Uint32 width, height;

	int eventLoop();
	void render();
};