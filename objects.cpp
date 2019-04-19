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
	if (getPos().getX() + radius > level.w) { 
		pos.setX(level.w - radius); 
		velX = 0;
		velY *= .95;
	} else if (getPos().getX() - radius < 0) {
		pos.setX(0 + radius);
		velX = 0;
		velY *= .95;
	} if (getPos().getY() + radius > level.h) {
		pos.setY(level.h - radius);
		velY = 0;
		velX *= .95;
	} else if (getPos().getY() - radius < 0) {
		pos.setY(0 + radius);
		velY = 0;
		velX *= .95;
	}
}
void Node::lineCollision(double x1, double y1, double x2, double y2) {
	if (collision.circleVsLine(pos, radius, x1, y1, x2, y2)) {
		float distX = x1 - x2;
		float distY = y1 - y2;
		float len = sqrt((distX*distX) + (distY*distY));

		float dot = (((pos.getX() - x1)*(x2 - x1)) + ((pos.getY() - y1)*(y2 - y1))) / pow(len, 2);

		float closestX = x1 + (dot * (x2 - x1));
		float closestY = y1 + (dot * (y2 - y1));

		float angle = abs(atan2(y2 - y1, x2 - x1));

		pos.setX(closestX - (sin(angle) * radius));
		pos.setY(closestY - (cos(angle) * radius));

		velX *= .9999 * cos(angle);
		velY *= .9999 * sin(angle);
	}
}

void Node::draw(SDL_Renderer* renderer, SDL_Rect screen) {
	int x = radius;
	int y = 0;
	int err = 0;

	while (x >= y) {
		SDL_RenderDrawPoint(renderer, pos.getX() + x - screen.x, pos.getY() + y - screen.y);
		SDL_RenderDrawPoint(renderer, pos.getX() + y - screen.x, pos.getY() + x - screen.y);
		SDL_RenderDrawPoint(renderer, pos.getX() - y - screen.x, pos.getY() + x - screen.y);
		SDL_RenderDrawPoint(renderer, pos.getX() - x - screen.x, pos.getY() + y - screen.y);
		SDL_RenderDrawPoint(renderer, pos.getX() - x - screen.x, pos.getY() - y - screen.y);
		SDL_RenderDrawPoint(renderer, pos.getX() - y - screen.x, pos.getY() - x - screen.y);
		SDL_RenderDrawPoint(renderer, pos.getX() + y - screen.x, pos.getY() - x - screen.y);
		SDL_RenderDrawPoint(renderer, pos.getX() + x - screen.x, pos.getY() - y - screen.y);

		if (err <=0) {
			y++;
			err += 2 * y + 1;
		} else if (err > 0) {
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}

Node::Node() {
	velX = 0;
	velY = 0;
	mass = 5;
	radius = 5;
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
	restitution = .002;
	flexibility = .75;
	optimalLength = 0;
	currentLength = 0;
	maxLength = 0;
}

//SoftBody class
void SoftBody::fill() {
	int farLeft = nodes[0].getPos().getX(), farRight = nodes[0].getPos().getX(), farTop = nodes[0].getPos().getY(), farBottom = nodes[0].getPos().getY();
	for (auto i : nodes) {
		if (i.getPos().getX() > farRight) farRight = i.getPos().getX();
		else if (i.getPos().getX() < farLeft) farLeft = i.getPos().getX();
		if (i.getPos().getY() < farTop) farTop = i.getPos().getY();
		else if (i.getPos().getY() > farBottom) farBottom = i.getPos().getY();
	}

	int linesCollided = 0;
	while (std::size(nodes) < 20) {
		Node newNode;
		Point pos;
		newTimer.seedRand();
		pos.setX((rand() % (farRight - farLeft)) + farLeft + 1);
		pos.setY((rand() % (farBottom - farTop)) + farTop + 1);
		for (unsigned int i = 0; i < std::size(nodes); i++) {
			if (collision.lineVsLine(pos.getX(), pos.getY(), pos.getX(), farBottom + 1, nodes[i].getPos().getX(), nodes[i].getPos().getY(), nodes[(i + 1) % std::size(nodes)].getPos().getX(), nodes[(i + 1) % std::size(nodes)].getPos().getY())) linesCollided++;
		}
		if (linesCollided % 2 == 1) {
			newNode.setPos(pos);
			nodes.push_back(newNode);
			linesCollided = 0;
		}
	}

	for (unsigned int i = 0; i < std::size(nodes); i++) {
		for (unsigned int j = 0; j < std::size(nodes); j++) {
			if (collision.pointVsCircle(nodes[i].getPos(), nodes[j].getPos(), 70)) {
				Spring newSpring;
				newSpring.setn1(&nodes[i]);
				newSpring.setn2(&nodes[j]);
				springs.push_back(newSpring);
			}
		}
	}
}
void SoftBody::drag(Point mPos) {
	Node mouse;
	mouse.setPos(mPos);
	for (unsigned int i = 0; i < std::size(nodes); i++) {
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
		i.lineCollision(200,400,600,200);
	}
	for (auto &i : springs) {
		i.update();
	}
}
void SoftBody::draw(SDL_Renderer* renderer, SDL_Rect screen) {
	for (auto &i : springs) {
		i.draw(renderer, screen);
	}
	for (auto &i : nodes) {
		i.draw(renderer, screen);
	}
}

SoftBody::SoftBody(std::vector<Node> newNodes) {
	density = 0.05;
	flexibility = 0.05;
	nodes = newNodes;
}
SoftBody::SoftBody() {
	density = 0.05;
	flexibility = 0.05;
}