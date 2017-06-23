#include "GameObject.h"

std::vector<GameObject *> GameObject::OBJECTS = std::vector<GameObject *>();
Uint32 GameObject::COUNTER = 0;

GameObject::GameObject() {
	this->id = ++GameObject::COUNTER;

	GameObject::OBJECTS.push_back(this);
}

GameObject::~GameObject() {}

void GameObject::render(SDL_Renderer *renderer) {}

void GameObject::update(double delta) {}

void GameObject::onBeforeRendering() {}

void GameObject::onAfterRendering() {}

void GameObject::onNotify(char* message, GameObject *sender, NotifyFunction func) {}

void GameObject::notify(char* message, GameObject *sender) {
	this->onNotify(message, sender);
}

void GameObject::notifyAll(char* message, GameObject *sender, NotifyFunction func) {
	for (std::vector<GameObject*>::iterator it = GameObject::OBJECTS.begin(); it != GameObject::OBJECTS.end();) {
		(*it)->onNotify(message, sender, func);
	}
}

void GameObject::setApp(App *app) {
	this->app = app;
}

void GameObject::addDelegate(GameObject *object) {
	if (object != NULL) {
		this->delegates.push_back(object);
	}
}

bool GameObject::hasDelegate(GameObject *object) {
	if (object != NULL) {
		for (std::vector<GameObject*>::iterator it = GameObject::OBJECTS.begin(); it != GameObject::OBJECTS.end();) {
			if ((*it)->id == object->id) {
				return true;
			}
		}
	}
	return false;
}