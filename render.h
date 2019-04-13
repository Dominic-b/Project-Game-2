#pragma once
#include "stdafx.h"

class Render {
	SDL_Rect source;//what is take from the png / image
	SDL_Rect rect;//where the image is rendered onto the screen
public:
	SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);

	void render(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h);
	void renderEx(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h, int angle);
	//void renderSheetEx(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int x2, int y2, int w, int h, int w2, int h2, double angle);
};