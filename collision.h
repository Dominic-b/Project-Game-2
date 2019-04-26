#pragma once
#include "stdafx.h"

class Collision {
public:
	bool pointVsRect(Point point, SDL_Rect rect);
	bool pointVsCircle(Point point1, Point point2, double radius);
	bool lineVsLine(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
	bool pointVsLine(Point point, double x1, double y1, double x2, double y2);
	bool circleVsLine(Point point, double radius, double x1, double y1, double x2, double y2);
};