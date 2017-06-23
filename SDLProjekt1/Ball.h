#include <SDL.h>
#include <iostream>
#include <math.h>

#include "Vector2D.h"
#include "GameObject.h"

#pragma once
class Ball : public GameObject {
public:
	Ball();
	~Ball();

	void render(SDL_Renderer *renderer);
	void update(double delta);
	void onAfterRendering();
	void onNotify(char* message, GameObject *sender, NotifyFunction func = NULL);

	SDL_Point getSize();
	SDL_Point getPosition();

private:
	SDL_Texture* drawFilledEllipse(SDL_Renderer *renderer, int cx, int cy, int rx, int ry, SDL_Color fillColor);
	void _fillHalfEllipse(float step, SDL_Rect* &rects, int rx, int ry, int &count);

	SDL_Texture *paintTexture = NULL;
	Vector2D position;
	SDL_Color color;
	SDL_Point size;
};

