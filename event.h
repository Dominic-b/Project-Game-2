#pragma once
#include "stdafx.h"

class Event {
public:
	const Uint8 *keyboard_state_array;//holds keyboard presses
	bool m1, m2;//left and right click
	int mX, mY;//mouse x and y
	Point mPos;
	void update(SDL_Event &e, bool &quit, bool &inGame, SDL_Rect screen);
	bool testKey(char key);//tests if a key is pressed
};