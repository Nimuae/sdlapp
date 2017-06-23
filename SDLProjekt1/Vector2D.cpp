#include "Vector2D.h"

Vector2D::Vector2D() {
	this->x = 0;
	this->y = 0;
}
Vector2D::Vector2D(Vector2D a, Vector2D b) {
	this->x = b.x - a.x;
	this->y = b.y - a.y;
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
	return sqrt(SQR(a) + SQR(b));
}

Vector2D Vector2D::getOrtho() {
	return Vector2D(this->y * -1, this->x);
}

Vector2D Vector2D::operator+ (Vector2D v) {
	return Vector2D(this->x + v.x, this->y + v.y);
}

Vector2D Vector2D::operator- (Vector2D v) {
	return Vector2D(this->x - v.x, this->y - v.y);
}

Vector2D Vector2D::operator* (double s) {
	return Vector2D(this->x * s, this->y * s);
}

Vector2D Vector2D::operator*(Vector2D v) {
	return Vector2D(this->x * v.x, this->y * v.y);
}

Vector2D Vector2D::operator*=(double s) {
	return Vector2D((*this) * s);
}

bool Vector2D::operator==(Vector2D v) {
	return this->x == v.x && this->y == v.y;
}

bool Vector2D::operator!=(Vector2D v) {
	return this->x != v.x || this->y != v.y;
}

double Vector2D::dot(Vector2D v) {
	return this->x * v.x + this->y * v.y;
}

double Vector2D::length() {
	return sqrt(SQR(this->x) + SQR(this->y));
}

Line2D::Line2D() : Line2D(Vector2D(0, 0), Vector2D(1, 1)) {}

Line2D::Line2D(Vector2D startPoint, Vector2D direction) {
	this->startPoint = startPoint;
	this->direction = direction;
}

double Line2D::distanceToPoint(Vector2D point) {
	Line2D orthoLine = this->getOrthoLine(point);
	Vector2D intersectPoint = this->getIntersectPoint(orthoLine);

	return intersectPoint.distance(point);
}

Line2D Line2D::getOrthoLine(Vector2D point) {
	return Line2D(point, this->direction.getOrtho());
}

Vector2D Line2D::getIntersectPoint(Line2D line) {
	if (line.direction.x == this->direction.x) {
		return Vector2D();
	}

	double factorX = (this->startPoint.x - line.startPoint.x) / (line.direction.x - this->direction.x);
	double factorY = (this->startPoint.y - line.startPoint.y) / (line.direction.y - this->direction.y);

	if (factorX == 0) {
		return this->getPointFromFactor(factorY);
	}
	return this->getPointFromFactor(factorX);
}

double Line2D::getPointFactor(Vector2D point) {
	double factor = 0;

	if (this->direction.x != 0) {
		factor = (point.x - this->startPoint.x) / this->direction.x;
	} else {
		factor = (point.y - this->startPoint.y) / this->direction.y;
	}

	return factor;
}

Vector2D Line2D::getPointFromFactor(double factor) {
	return this->startPoint + this->direction * factor;
}