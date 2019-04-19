#include "stdafx.h"

bool Collision::pointVsRect(Point point, SDL_Rect rect) {
	return ((point.getX() > rect.x) && (point.getY() > rect.y) && (point.getX() < rect.x + rect.w) && (point.getY() < rect.y + rect.h));
}
bool Collision::pointVsCircle(Point point1, Point point2, double radius) {
	return (pow(point1.getX() - point2.getX(), 2) + pow(point1.getY() - point2.getY(), 2)) < pow(radius, 2);
}
bool Collision::lineVsLine(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
	double uA = ((x4 - x3)*(y1 - y3) - (y4 - y3)*(x1 - x3)) / ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));
	double uB = ((x2 - x1)*(y1 - y3) - (y2 - y1)*(x1 - x3)) / ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));
	return (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1);
}
bool Collision::circleVsLine(Point point, double radius, double x1, double y1, double x2, double y2) {
	float distX = x1 - x2;
	float distY = y1 - y2;
	float len = sqrt((distX*distX) + (distY*distY));

	float dot = (((point.getX() - x1)*(x2 - x1)) + ((point.getY() - y1)*(y2 - y1))) / pow(len, 2);

	float closestX = x1 + (dot * (x2 - x1));
	float closestY = y1 + (dot * (y2 - y1));

	Point pos;
	pos.setX(closestX);
	pos.setY(closestY);

	SDL_Rect rect = {x1, y1 - distY, abs(distX), abs(distY)};

	if (pointVsRect(pos, rect)) {

		distX = closestX - point.getX();
		distY = closestY - point.getY();
		float distance = sqrt((distX*distX) + (distY*distY));

		return (distance <= radius);
	}
}