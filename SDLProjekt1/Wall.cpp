#include "Wall.h"

Wall::Wall(int x, int y, int w, int h) : Wall(x, y, w, h, { 0, 0, 0, 0xFF }) {}

Wall::Wall(int x, int y, int w, int h, SDL_Color color) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

	this->color = color;
}

Wall::~Wall() {}

void Wall::setColor(SDL_Color color) {
	this->color = color;
}
void Wall::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	this->color.r = r;
	this->color.g = g;
	this->color.b = b;
	this->color.a = a;
}

void Wall::render(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, this->color.r, this->color.g, this->color.b, this->color.a);
	SDL_RenderFillRect(renderer, this);
}

void Wall::update(double delta) {
}
 
void Wall::onNotify(char* message, GameObject *sender, NotifyFunction func) {
	if (message == "Collision?") {
		//check ball collision
		Ball *ball = (Ball*) sender;

		if (this->ellipseIntersect(ball)) {
			sender->notify("Collision.", this);
		}
	}
}

std::vector<Vector2D> Wall::getVectors() {
	std::vector<Vector2D> vectors = std::vector<Vector2D>();

	Vector2D pointA = Vector2D(this->x, this->y);
	Vector2D pointB = Vector2D(this->x + this->w, this->y);
	Vector2D pointC = Vector2D(this->x, this->y + this->h);
	Vector2D pointD = Vector2D(this->x + this->w, this->y + this->h);

	vectors.push_back(pointB - pointA);
	vectors.push_back(pointC - pointA);
	vectors.push_back(pointC - pointD);
	vectors.push_back(pointB - pointD);

	return vectors;
}

bool Wall::ellipseIntersect(Ball *ball) {
	SDL_Point pos = ball->getPosition();
	Vector2D ballPos = Vector2D(ball->getPosition());
	std::vector<Vector2D> vectors = this->getVectors();

	SDL_bool includedInRect = SDL_PointInRect(&pos, this);

	return includedInRect == SDL_TRUE;
}