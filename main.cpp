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
	SDL_Rect level = { 0, 0, 1920, 1080 / 3 };
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

	Player player;

	/*std::vector<Node> nodes;
	for (int i = 0; i < 4; i++) {
		Node newNode;
		Point newPoint;
		newPoint.setX(100 + ((i * 100) % 200));
		newPoint.setY(100 + i * 100);
		newNode.setPos(newPoint);
		nodes.push_back(newNode);
	}
	SoftBody softBody(nodes);
	softBody.fill();*/

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
			/*if (event.m1) {
				softBody.drag(event.mPos);
			}
			softBody.update(newTimer.deltaTime, level);
			softBody.draw(renderer, screen);*/

			player.update(newTimer.deltaTime, level);
			player.move(e, event.keyboard_state_array);
			player.centerCamera(camera, newTimer.deltaTime);
			player.draw(renderer, camera.screen);
			SDL_RenderDrawLine(renderer, level.x - camera.screen.x, level.y - camera.screen.y, level.x + level.w - camera.screen.x, level.y - camera.screen.y);
			SDL_RenderDrawLine(renderer, level.x + level.w - camera.screen.x, level.y - camera.screen.y, level.x + level.w - camera.screen.x, level.y + level.h - camera.screen.y);
			SDL_RenderDrawLine(renderer, level.x + level.w - camera.screen.x, level.y + level.h - camera.screen.y, level.x - camera.screen.x, level.y + level.h - camera.screen.y);
			SDL_RenderDrawLine(renderer, level.x - camera.screen.x, level.y + level.h - camera.screen.y, level.x - camera.screen.x, level.y - camera.screen.y);

			SDL_RenderDrawLine(renderer, 200-camera.screen.x, 400 - camera.screen.y, 600 - camera.screen.x, 200 - camera.screen.y);

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