#include "stdafx.h"

bool Collision::pointVsRect(Point point, SDL_Rect rect) {
	return ((point.getX() > rect.x) && (point.getY() > rect.y) && (point.getX() < rect.x + rect.w) && (point.getY() < rect.y + rect.h));
}
