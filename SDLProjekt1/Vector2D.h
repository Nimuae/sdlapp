#include <math.h>
#include <SDL.h>

#pragma once
class Vector2D {
public:
	Vector2D();
	Vector2D(double x, double y);
	Vector2D(SDL_Point point);
	~Vector2D();

	SDL_Point toPoint() {
		return { (int) x, (int) y };
	}

	double distance(Vector2D x);
	double x, y;
};