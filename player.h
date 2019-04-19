#pragma once
#include "stdafx.h"

class Player {
	SoftBody softBody;
	Node centerNode;
	double radius;
public:
	void centerCamera(Camera &camera, double deltaTime);
	void move(SDL_Event &e, const Uint8 *keyboard_state_array);
	void update(double deltaTime, SDL_Rect level);
	void draw(SDL_Renderer* renderer, SDL_Rect screen);

	Player();
};