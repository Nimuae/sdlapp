#include <SDL.h>
#include <vector>
#include <iostream>

class App;
class GameObject

#pragma once
typedef (*NotifyFunction)(GameObject*);

#pragma once
class GameObject {
public:
	GameObject();
	~GameObject();

	virtual void render(SDL_Renderer *renderer);
	virtual void update(double delta);
	virtual void onBeforeRendering();
	virtual void onAfterRendering();
	void setApp(App *app);

	void addDelegate(GameObject *object);
	bool hasDelegate(GameObject *object);

	static void notifyAll(char* message, GameObject *sender, NotifyFunction func = NULL);
	virtual void onNotify(char* message, GameObject *sender, NotifyFunction func = NULL);
	void notify(char *message, GameObject *sender);

private:
	static std::vector<GameObject *> OBJECTS;
	static Uint32 COUNTER;
	Uint32 id = 0;
	App *app = NULL;
	std::vector<GameObject*> delegates = std::vector<GameObject*>();
};