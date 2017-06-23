#include "App.h"

App::App() {}

App::App(std::string title, unsigned int width, unsigned int height) {
	this->init(title, width, height);
}


App::~App() {
	for (std::vector<GameObject*>::iterator i = this->gameObjects.begin(); i != this->gameObjects.end(); i++) {
		delete (*i);
	}

	if (this->screen != NULL) {
		SDL_FreeSurface(this->screen);
		this->screen = NULL;
	}

	if (this->renderer != NULL) {
		SDL_DestroyRenderer(this->renderer);
		this->renderer = NULL;
	}
	
	if (this->window != NULL) {
		SDL_DestroyWindow(this->window);
		this->window = NULL;
	}

	//Quit SDL subsystems
	SDL_Quit();
}

int App::init(std::string title, unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;

	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

		if (this->window == NULL && this->ErrorFunc != NULL) {
			this->ErrorFunc();
			return 1;
		}

		this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
		SDL_SetRenderDrawBlendMode(this->renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);
		this->screen = SDL_GetWindowSurface(this->window);

		return this->eventLoop();
	}
	return 1;
}

int App::eventLoop() {
	bool quit = false;

	SDL_Event e;
	Uint32 oldTime = SDL_GetTicks();
	Uint32 currentTime = 0;
	double delta = 0;

	while (!quit) {
		currentTime = SDL_GetTicks();
		delta = (currentTime - oldTime) / 1000.f;
		oldTime = currentTime;

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (e.type == SDL_MOUSEMOTION) {
			}
		}

		std::vector<GameObject*>::iterator i;
		for (i = this->gameObjects.begin(); i != this->gameObjects.end(); i++) {
			(*i)->update(delta);
		}

		for (i = this->gameObjects.begin(); i != this->gameObjects.end(); i++) {
			(*i)->onBeforeRendering();
		}

		this->render();
	}
	return 0;
}

void App::render() {
	std::vector<GameObject*>::iterator i;
	
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
	SDL_RenderClear(this->renderer);

	for (i = this->gameObjects.begin(); i != this->gameObjects.end(); i++) {
		SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
		(*i)->render(this->renderer);
	}

	SDL_RenderPresent(this->renderer);

	for (i = this->gameObjects.begin(); i != this->gameObjects.end(); i++) {
		(*i)->onAfterRendering();
	}
}

void App::addObject(GameObject *obj) {
	if (obj != NULL) {
		this->gameObjects.push_back(obj);
		obj->setApp(this);
	}
}