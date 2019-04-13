#include "stdafx.h"

int main(int argc, char args[]) {
	newTimer.reset();
	SDL_Rect screen = { 0, 0, 1920 / 3, 1080 / 3 };//x and y are the location of the camera
	SDL_Rect level = { 0, 0, 1920 / 3, 1080 / 3 };
	SDL_Texture* texture = nullptr;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen.w, screen.h, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);// | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_Event e;

	bool quit = false;//if the program has been quit
	bool inGame = true;//if the player is in game
	bool paused = false;//if the game is paused
	double timeScale = 1;//how fast the game plays

	std::vector<Node> nodes;
	for (int i = 0; i < 3; i++) {
		Node newNode;
		Point newPoint;
		newPoint.setX(100 + ((i * 50) % 100));
		newPoint.setY(100 + i * 50);
		newNode.setPos(newPoint);
		nodes.push_back(newNode);
	}
	SoftBody softBody(nodes);
	softBody.fill();

	while (!quit) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

		event.update(e, quit, inGame, screen);

		menu.draw(0);

		SDL_RenderPresent(renderer);
		while (inGame) {
			if (paused) {
				menu.draw(1);
				timeScale = .01;
			} else {
				timeScale = 1;
			}

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

			event.update(e, quit, inGame, screen);
			if (event.m1) {
				softBody.drag(event.mPos);
			}
			softBody.update(newTimer.deltaTime, level);
			softBody.draw(renderer, screen);

			SDL_RenderPresent(renderer);

			newTimer.fps++;
			newTimer.checkDeltaTime();
			if (newTimer.checkTime() > newTimer.lastSecond + 1) {
				system("cls");//clears the console
				printf("Frames per second: %d\n", newTimer.fps);
				printf("Delta time: %f\n", newTimer.deltaTime);
				newTimer.lastSecond++;
				newTimer.fps = 0;
			}
		}
	}
}