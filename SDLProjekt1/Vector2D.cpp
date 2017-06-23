#include "Vector2D.h"

Vector2D::Vector2D() {
	this->x = 0;
	this->y = 0;
}
Vector2D::Vector2D(double x, double y) {
	this->x = x;
	this->y = y;
}
Vector2D::Vector2D(SDL_Point point) {
	this->x = point.x;
	this->y = point.y;
}

Vector2D::~Vector2D() {}

double Vector2D::distance(Vector2D v) {
	double a = v.x - this->x;
	double b = v.y - this->y;
	return sqrt(a*a + b*b);
}