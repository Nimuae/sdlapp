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

	Vector2D getOrtho();

	Vector2D operator+ (Vector2D v);
	Vector2D operator- (Vector2D v);
	Vector2D operator*(double s);
	bool operator==(Vector2D v);
	bool operator!=(Vector2D v);

	double dot(Vector2D v);
};

#pragma once
class Line2D {
public:
	Line2D();
	Line2D(Vector2D startPoint, Vector2D direction);
	friend class Vector2D;

	double distanceToPoint(Vector2D point);
	Line2D getOrthoLine(Vector2D point);
	Vector2D getIntersectPoint(Line2D line);

	double getPointFactor(Vector2D point);
	Vector2D getPointFromFactor(double factor);

private:
	Vector2D startPoint;
	Vector2D direction;
};