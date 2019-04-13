#include "stdafx.h"

//Point class
double Point::getX() {
	return x;
}
double Point::getY() {
	return y;
}
void Point::setX(double newX) {
	x = newX;
}
void Point::setY(double newY) {
	y = newY;
}
Point::Point() {
	x = 0;
	y = 0;
}

//Node class
Point Node::getPos() {
	return pos;
}
void Node::setPos(Point newPos) {
	pos = newPos;
}
double Node::getVelX() {
	return velX;
}
double Node::getVelY() {
	return velY;
}

void Node::applyForceX(double forceX) {
	velX += forceX / mass;
}
void Node::applyForceY(double forceY) {
	velY += forceY / mass;
}
void Node::update(double deltaTime) {
	velY += .5;//gravity
	pos.setX(pos.getX() + velX * deltaTime);
	pos.setY(pos.getY() + velY * deltaTime);
}
void Node::levelCollision(SDL_Rect level) {
	if (!collision.pointVsRect(getPos(), level)) {
		if (getPos().getX() > level.w) { 
			pos.setX(level.w); 
			velX = 0;
			velY *= .99;
		} else if (getPos().getX() < 0) {
			pos.setX(0);
			velX = 0;
			velY *= .99;
		} if (getPos().getY() > level.h) {
			pos.setY(level.h);
			velY = 0;
			velX *= .99;
		} else if (getPos().getY() < 0) {
			pos.setY(0);
			velY = 0;
			velX *= .99;
		}
	}
}

Node::Node() {
	velX = 0;
	velY = 0;
	mass = 5;
}

//Line class


//Spring class
Node Spring::getn1() {
	return *n1;
}
Node Spring::getn2() {
	return *n2;
}
void Spring::setn1(Node *newN1) {
	n1 = newN1;
	if (n2 != nullptr) optimalLength = sqrt(pow(n1->getPos().getX() - n2->getPos().getX(), 2) + pow(n1->getPos().getY() - n2->getPos().getY(), 2));
}
void Spring::setn2(Node *newN2) {
	n2 = newN2;
	if (n1 != nullptr) optimalLength = sqrt(pow(n1->getPos().getX() - n2->getPos().getX(), 2) + pow(n1->getPos().getY() - n2->getPos().getY(), 2));
}
void Spring::setOptimalLength(double newOptimalLength) {
	optimalLength = newOptimalLength;
}
void Spring::setRestitution(double newRestitution) {
	restitution = newRestitution;
}
void Spring::setFlexibility(double newFlexibility) {
	flexibility = newFlexibility;
}
void Spring::setMaxLength(double newMaxLength) {
	maxLength = newMaxLength;
}
void Spring::update() {
	currentLength = sqrt(pow(n1->getPos().getX() - n2->getPos().getX(), 2) + pow(n1->getPos().getY() - n2->getPos().getY(), 2));
	if (optimalLength != currentLength) {
		//spring forces
		n1->applyForceX(-((n1->getPos().getX() - n2->getPos().getX()) / currentLength) * (currentLength - optimalLength) * flexibility);
		n1->applyForceY(-((n1->getPos().getY() - n2->getPos().getY()) / currentLength) * (currentLength - optimalLength) * flexibility);
		n2->applyForceX(-((n2->getPos().getX() - n1->getPos().getX()) / currentLength) * (currentLength - optimalLength) * flexibility);
		n2->applyForceY(-((n2->getPos().getY() - n1->getPos().getY()) / currentLength) * (currentLength - optimalLength) * flexibility);
		//spring damping
		n1->applyForceX(-(n1->getVelX() - n2->getVelX()) * restitution);
		n1->applyForceY(-(n1->getVelY() - n2->getVelY()) * restitution);
		n2->applyForceX(-(n2->getVelX() - n1->getVelX()) * restitution);
		n2->applyForceY(-(n2->getVelY() - n1->getVelY()) * restitution);
	}
}
void Spring::draw(SDL_Renderer* renderer, SDL_Rect screen) {
	SDL_RenderDrawLine(renderer, n1->getPos().getX() - screen.x, n1->getPos().getY() - screen.y, n2->getPos().getX() - screen.x, n2->getPos().getY() - screen.y);
}

Spring::Spring() {
	n1 = nullptr;
	n2 = nullptr;
	restitution = .0005;
	flexibility = 1;
	optimalLength = 0;
	currentLength = 0;
	maxLength = 0;
}

//SoftBody class
void SoftBody::fill() {
	for (int i = 0; i < std::size(nodes); i++) {
		Spring newSpring;
		newSpring.setn1(&nodes[i]);
		newSpring.setn2(&nodes[(i+1) % std::size(nodes)]);
		springs.push_back(newSpring);
	}
}
void SoftBody::drag(Point mPos) {
	Node mouse;
	mouse.setPos(mPos);
	for (int i = 0; i < std::size(nodes); i++) {
		Spring newSpring;
		newSpring.setn1(&nodes[i]);
		newSpring.setn2(&mouse);
		newSpring.setOptimalLength(0);
		newSpring.setFlexibility(.05);
		newSpring.update();
	}
}
void SoftBody::update(double deltaTime, SDL_Rect level) {
	for (auto &i : nodes) {
		i.update(deltaTime);
		i.levelCollision(level);
	}
	for (auto &i : springs) {
		i.update();
	}
}
void SoftBody::draw(SDL_Renderer* renderer, SDL_Rect screen) {
	for (auto &i : springs) {
		i.draw(renderer, screen);
	}
}

SoftBody::SoftBody(std::vector<Node> newNodes) {
	density = 0.05;
	flexibility = 0.05;
	nodes = newNodes;
}