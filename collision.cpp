#include "stdafx.h"

bool Collision::pointVsRect(Point point, SDL_Rect rect) {
	return ((point.getX() >= rect.x) && (point.getY() >= rect.y) && (point.getX() <= rect.x + rect.w) && (point.getY() <= rect.y + rect.h));
}
bool Collision::pointVsCircle(Point point1, Point point2, double radius) {
	return (pow(point1.getX() - point2.getX(), 2) + pow(point1.getY() - point2.getY(), 2)) <= pow(radius, 2);
}
bool Collision::lineVsLine(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
	double uA = ((x4 - x3)*(y1 - y3) - (y4 - y3)*(x1 - x3)) / ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));
	double uB = ((x2 - x1)*(y1 - y3) - (y2 - y1)*(x1 - x3)) / ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));
	return (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1);
}

bool Collision::circleVsLine(Point point, double radius, double x1, double y1, double x2, double y2) {
	if (pointVsCircle(point, { x1, y1 }, 5) || pointVsCircle(point, { x2, y2 }, 5)) return true;
	double distX = x1 - x2;
	double distY = y1 - y2;
	double len = sqrt((distX*distX) + (distY*distY));

	double dot = (((point.getX() - x1)*(x2 - x1)) + ((point.getY() - y1)*(y2 - y1))) / pow(len, 2);

	double closestX = x1 + (dot * (x2 - x1));
	double closestY = y1 + (dot * (y2 - y1));

	Point pos;
	pos.setX(closestX);
	pos.setY(closestY);

	if (pointVsRect(pos, { (int)x1, (int)(y1 - distY), (int)abs(distX), (int)abs(distY) })) {

		distX = closestX - point.getX();
		distY = closestY - point.getY();
		float distance = sqrt((distX*distX) + (distY*distY));

		return (distance <= radius);
	}
	return false;
}