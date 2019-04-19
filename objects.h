#pragma once
#include "stdafx.h"

class Point {
	double x, y;//x and y coordinates
public:
	double getX();
	double getY();
	void setX(double newX);
	void setY(double neyY);

	void draw(SDL_Renderer* renderer, SDL_Rect screen);

	Point();
};

class Camera {
public:
	Point pos;//location
	int w, h;//width and height of screen
	SDL_Rect screen;
};

class Node {
	Point pos;//location
	double velX, velY;//velocities
	double mass;//its mass
	int radius;//size
public:
	Point getPos();
	void setPos(Point newPos);
	double getVelX();
	double getVelY();

	void applyForceX(double forceX);
	void applyForceY(double forceY);
	void update(double deltaTime);
	void levelCollision(SDL_Rect level);//keeps the node inside the level boundaries
	void lineCollision(double x1, double y1, double x2, double y2);

	void draw(SDL_Renderer* renderer, SDL_Rect screen);

	Node();
};

class Line {
	Point p1, p2;
public:
	Point getp1();
	Point getp2();
	void setp1(Point newP1);
	void setp2(Point newP2);

	void draw(SDL_Renderer* renderer, SDL_Rect screen);

	Line();
	Line(double x1, double y1, double x2, double y2);
};

class Spring {
	Node *n1, *n2;
	double restitution;
	double flexibility;
	double optimalLength;
	double currentLength;
	double maxLength;
public:
	Node getn1();
	Node getn2();
	void setn1(Node *newN1);
	void setn2(Node *newN2);
	void setOptimalLength(double newOptimalLength);
	void setRestitution(double newRestitution);
	void setFlexibility(double newFlexibility);
	void setMaxLength(double newMaxLength);

	void update();
	void draw(SDL_Renderer* renderer, SDL_Rect screen);

	Spring();
};

class RigidBody {

};

class SoftBody {
	double density;//how many point there are in a given area; wont affect anything after the object is made
	double flexibility;
public:
	std::vector<Node> nodes;
	std::vector<Spring> springs;

	void fill();//fill it with random points based on the density, then create springs
	void drag(Point mPos);//drag it around with the mouse
	void update(double deltaTime, SDL_Rect level);
	void draw(SDL_Renderer* renderer, SDL_Rect screen);

	SoftBody(std::vector<Node> newNodes);
	SoftBody();
};