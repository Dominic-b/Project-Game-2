#include "stdafx.h"

void Level::addPoint(Point newPoint) {
	points.push_back(newPoint);
}
void Level::addLine(Line newLine) {
	lines.push_back(newLine);
}
void Level::nodeCollision(Node& node) {
	for (auto i : lines) {
		node.lineCollision(i);
	}
	if (node.getPos().getY() + node.radius > level.h) {
		node.setPos({ node.getPos().getX(), (double)(level.h - node.radius - .1) });
		node.velX *= .9;
		node.velY = 0;
	} else if (node.getPos().getY() - node.radius < 0) {
		node.setPos({ node.getPos().getX(), (double)(node.radius + .1) });
		node.velX *= .9;
		node.velY = 0;
	}
	if (node.getPos().getX() + node.radius > level.w) {
		node.setPos({ (double)(level.w - node.radius - .1), node.getPos().getY() });
		node.velY *= .9;
		node.velX = 0;
	} else if (node.getPos().getX() - node.radius < 0) {
		node.setPos({ (double)(node.radius + .1), node.getPos().getY() });
		node.velY *= .9;
		node.velX = 0;
	}
	
}
void Level::springCollision(Spring& spring) {
	for (auto i : points) {
		spring.pointCollision(i);
	}
}
void Level::drawPoints(SDL_Rect screen, SDL_Renderer* renderer) {
	for (auto i : points) {
		int x = 5;
		int y = 0;
		int err = 0;

		while (x >= y) {
			SDL_RenderDrawPoint(renderer, i.getX() + x - screen.x, i.getY() + y - screen.y);
			SDL_RenderDrawPoint(renderer, i.getX() + y - screen.x, i.getY() + x - screen.y);
			SDL_RenderDrawPoint(renderer, i.getX() - y - screen.x, i.getY() + x - screen.y);
			SDL_RenderDrawPoint(renderer, i.getX() - x - screen.x, i.getY() + y - screen.y);
			SDL_RenderDrawPoint(renderer, i.getX() - x - screen.x, i.getY() - y - screen.y);
			SDL_RenderDrawPoint(renderer, i.getX() - y - screen.x, i.getY() - x - screen.y);
			SDL_RenderDrawPoint(renderer, i.getX() + y - screen.x, i.getY() - x - screen.y);
			SDL_RenderDrawPoint(renderer, i.getX() + x - screen.x, i.getY() - y - screen.y);

			if (err <= 0) {
				y++;
				err += 2 * y + 1;
			}
			else if (err > 0) {
				x -= 1;
				err -= 2 * x + 1;
			}
		}
	}
}
void Level::drawLines(SDL_Rect screen, SDL_Renderer* renderer) {
	for (auto i : lines) {
		SDL_RenderDrawLine(renderer, i.getp1().getX() - screen.x, i.getp1().getY() - screen.y, i.getp2().getX() - screen.x, i.getp2().getY() - screen.y);
	}
	SDL_RenderDrawLine(renderer, level.x - screen.x, level.y - screen.y, level.x + level.w - screen.x, level.y - screen.y);
	SDL_RenderDrawLine(renderer, level.x + level.w - screen.x, level.y - screen.y, level.x + level.w - screen.x, level.y + level.h - screen.y);
	SDL_RenderDrawLine(renderer, level.x + level.w - screen.x, level.y + level.h - screen.y, level.x - screen.x, level.y + level.h - screen.y);
	SDL_RenderDrawLine(renderer, level.x - screen.x, level.y + level.h - screen.y, level.x - screen.x, level.y - screen.y);
}

Level::Level() {
	level = { 0, 0, 1920, 1080 / 3 };
}