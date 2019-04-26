#include "stdafx.h"

int main(int argc, char args[]) {
	newTimer.reset();
	Camera camera;
	Point newPos;
	newPos.setX(0);
	newPos.setY(0);
	camera.pos = newPos;
	camera.w = 1920 / 3;
	camera.h = 1080 / 3;
	camera.screen = { 0, 0, 1920 / 3, 1080 / 3 };//x and y are the location of the camera
	SDL_Texture* texture = nullptr;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, camera.screen.w, camera.screen.h, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);// | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_Event e;

	bool quit = false;//if the program has been quit
	bool inGame = true;//if the player is in game
	bool paused = false;//if the game is paused
	double timeScale = 1;//how fast the game plays

	Level level;
	Player player;

	level.addLine({ 0, 300, 1000, 360 });

	while (!quit) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

		event.update(e, quit, inGame, camera.screen);

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

			event.update(e, quit, inGame, camera.screen);
			
			player.update(newTimer.deltaTime, level);
			player.move(e, event.keyboard_state_array);
			player.centerCamera(camera, newTimer.deltaTime);
			player.draw(renderer, camera.screen);
			level.drawLines(camera.screen, renderer);
			level.drawPoints(camera.screen, renderer);
			
			SDL_RenderPresent(renderer);

			newTimer.fps++;
			newTimer.checkDeltaTime();
			if (newTimer.checkTime() > newTimer.lastSecond + 1) {
				printf("Frames per second: %d\n", newTimer.fps);
				newTimer.lastSecond++;
				newTimer.fps = 0;
			}
		}
	}
}