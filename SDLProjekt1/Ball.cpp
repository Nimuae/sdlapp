#include "Ball.h"

Ball::Ball() {
	this->position = Vector2D(100.f, 100.f);
	this->direction = Vector2D(1, 1);
	this->color = { 0xFF, 0, 0, 0xFF };
}

Ball::~Ball() {}

void Ball::render(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0xFF, 0, 0xFF);

	SDL_Point pos = this->position.toPoint();
	this->drawFilledEllipse(renderer, pos.x, pos.y, 10, 10, this->color);
}

void Ball::update(double delta) {
	const float speed = 50.f; //px per second
	this->position.x += this->direction.x * speed * delta;
	this->position.y += this->direction.y * speed * delta;

	GameObject::notifyAll("Collision?", this);
}

void Ball::onNotify(char* message, GameObject *sender, NotifyFunction func) {
	if (message == "Collision.") {
		//TODO: implement deflection physics
	}
}

SDL_Point Ball::getSize() {
	return this->size;
}
SDL_Point Ball::getPosition() {
	return this->position.toPoint();
}

SDL_Texture* Ball::drawFilledEllipse(SDL_Renderer *renderer, int cx, int cy, int rx, int ry, SDL_Color fillColor) {
	const int width = rx * 2;
	const int height = ry * 2;

	float step = 1.f;
	SDL_Rect srcRect = { 0, 0, width, height };
	SDL_Rect dstRect = {
		cx - rx,
		cy - ry,
		width,
		height
	};

	SDL_Rect* rects = NULL;
	int count = 0;
	this->_fillHalfEllipse(step, rects, rx, ry, count);

	this->paintTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TextureAccess::SDL_TEXTUREACCESS_TARGET, width, height);
	SDL_SetTextureBlendMode(this->paintTexture, SDL_BlendMode::SDL_BLENDMODE_BLEND);

	SDL_SetRenderTarget(renderer, this->paintTexture);

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
	SDL_RenderFillRects(renderer, rects, count);

	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, this->paintTexture, &srcRect, &dstRect);
	SDL_RenderCopyEx(renderer, this->paintTexture, &srcRect, &dstRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_VERTICAL);

	//delete rects;
	return this->paintTexture;
}

void Ball::_fillHalfEllipse(float step, SDL_Rect* &rects, int rx, int ry, int &count) {
	count = (int) floor(90 / step);
	
	if (rects == NULL) {
		rects = new SDL_Rect[count * 2];
	}

	double x1 = 0, x2 = 0;
	double y = 0;
	double gamma = 0;
	int i = 0;

	SDL_Rect *_rectangle = NULL;
	for (double alpha = 0.f; alpha <= 90; alpha += step) {
		if (i >= count) {
			break;
		}
		gamma = M_PI * (alpha / 180);
		x1 = rx * SDL_cos(gamma) * -1.f;
		y = ry * SDL_sin(gamma);

		rects[++i] = {
			(int) round(x1) + rx,
			(int) round(y) + ry - 1,
			(int) round(abs(x1)) * 2,
			1
		};
	}
}

void Ball::onAfterRendering() {
	if (this->paintTexture != NULL) {
		SDL_DestroyTexture(this->paintTexture);
		this->paintTexture = NULL;
	}
}