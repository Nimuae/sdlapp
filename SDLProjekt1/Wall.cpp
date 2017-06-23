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
		
		Vector2D ballPos = Vector2D(ball->getPosition());

		sender->notify("Collision.", this);
	}
}