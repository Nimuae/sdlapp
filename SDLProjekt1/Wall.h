#include <iostream>

#include "GameObject.h"
#include "Vector2D.h"
#include "Ball.h"

#pragma once
class Wall : public GameObject, SDL_Rect {
public:
	Wall(int x, int y, int w, int h);
	Wall(int x, int y, int w, int h, SDL_Color color);
	~Wall();

	SDL_Color color;
	void setColor(SDL_Color color);
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);

	void render(SDL_Renderer *renderer);
	void update(double delta);

	void onNotify(char* message, GameObject *sender, NotifyFunction func = NULL);
	std::vector<Vector2D> getVectors();

private:
	SDL_Rect rect;

	Vector2D direction;

	bool ellipseIntersect(Ball *ball);
};

