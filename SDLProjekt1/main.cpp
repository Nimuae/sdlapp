#include <SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "App.h"
#include "Wall.h"
#include "Ball.h"

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* args[]) {
	App a = App();
	
	//top
	a.addObject(new Wall(0, 0, SCREEN_WIDTH, 5));
	//bottom
	a.addObject(new Wall(0, SCREEN_HEIGHT - 5, SCREEN_WIDTH, 5, { 0xDD, 0x77, 0x88 }));
	//left
	a.addObject(new Wall(0, 0, 5, SCREEN_HEIGHT));
	//right
	a.addObject(new Wall(SCREEN_WIDTH - 5, 0, 5, SCREEN_HEIGHT));

	a.addObject(new Ball());

	return a.init("Test", SCREEN_WIDTH, SCREEN_HEIGHT);
}