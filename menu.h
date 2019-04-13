#pragma once
#include "stdafx.h"

class Menu {
	SDL_Texture* mainMenu;//main menu image
	SDL_Texture* pauseMenu;//pause menu image
public:
	void draw(int type);//type 0 is main menu, 1 is pause menu
	void update();
};