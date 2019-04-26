#pragma once
#include "stdafx.h"

class Level {
public:
	std::vector<Point> points;
	std::vector<Line> lines;
	SDL_Rect level;
	void addPoint(Point newPoint);
	void addLine(Line newLine);
	void nodeCollision(Node &node);
	void springCollision(Spring &spring);
	void drawPoints(SDL_Rect screen, SDL_Renderer* renderer);
	void drawLines(SDL_Rect screen, SDL_Renderer* renderer);

	Level();
};