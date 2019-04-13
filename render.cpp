#include "stdafx.h"

SDL_Texture* Render::loadTexture(std::string path, SDL_Renderer* renderer) {
	SDL_Texture* newTexture = nullptr;//new texture
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());//Load image at specified path
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);//Create texture from surface pixels
	SDL_FreeSurface(loadedSurface);//Get rid of old loaded surface
	return newTexture;
}

void Render::render(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h) {
	rect.x = x;//setting the destination rect
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void Render::renderEx(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h, int angle) {
	rect.x = x;//setting the destination rect
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_RenderCopyEx(renderer, texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
}