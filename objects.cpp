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
Point::Point(double newX, double newY) {
	x = newX;
	y = newY;
}

//Line class
Point Line::getp1() {
	return p1;
}
Point Line::getp2() {
	return p2;
}
void Line::setp1(Point newPoint) {
	p1 = newPoint;
}
void Line::setp2(Point newPoint) {
	p2 = newPoint;
}
Line::Line() {
	p1.setX(0);
	p1.setY(0);
	p2.setX(0);
	p2.setY(0);
}
Line::Line(int x1, int y1, int x2, int y2) {
	p1.setX(x1);
	p1.setY(y1);
	p2.setX(x2);
	p2.setY(y2);
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
void Node::lineCollision(Line line) {
	if (collision.circleVsLine(pos, radius, line.getp1().getX(), line.getp1().getY(), line.getp2().getX(), line.getp2().getY())) {
		float distX = line.getp1().getX() - line.getp2().getX();
		float distY = line.getp1().getY() - line.getp2().getY();

		float dot = (((pos.getX() - line.getp1().getX())*(line.getp2().getX() - line.getp1().getX())) + ((pos.getY() - line.getp1().getY())*(line.getp2().getY() - line.getp1().getY()))) / pow(sqrt((distX*distX) + (distY*distY)), 2);

		float closestX = line.getp1().getX() + (dot * (line.getp2().getX() - line.getp1().getX()));
		float closestY = line.getp1().getY() + (dot * (line.getp2().getY() - line.getp1().getY()));

		double angle = -atan2(line.getp2().getY() - line.getp1().getY(), line.getp2().getX() - line.getp1().getX());

		pos.setX(closestX - (sin(angle) * radius));
		pos.setY(closestY - (cos(angle) * radius));
		
		velX *= .9 * cos(angle);
		velY *= .9 * sin(angle);
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
	radius = .5;
}

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
void Spring::pointCollision(Point point) {
	if (collision.circleVsLine({point.getX(), point.getY()}, 5, n1->getPos().getX(), n1->getPos().getY(), n2->getPos().getX(), n2->getPos().getY())) {
		n1->lineCollision({ (int)n1->getPos().getX(), (int)n1->getPos().getY(), (int)n2->getPos().getX(), (int)n2->getPos().getY() });
		n2->lineCollision({ (int)n1->getPos().getX(), (int)n1->getPos().getY(), (int)n2->getPos().getX(), (int)n2->getPos().getY() });
	}
}
void Spring::draw(SDL_Renderer* renderer, SDL_Rect screen) {
	SDL_RenderDrawLine(renderer, n1->getPos().getX() - screen.x, n1->getPos().getY() - screen.y, n2->getPos().getX() - screen.x, n2->getPos().getY() - screen.y);
}

Spring::Spring() {
	n1 = nullptr;
	n2 = nullptr;
	restitution = .002;
	flexibility = 2;
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
	int dist = 20;
	std::vector<Node> newNodes;
	Node newNode;
	Point pos;
	for (int i = 0; i <= ceil((farRight - farLeft) / dist); i++) {
		for (int j = 0; j <= ceil((farBottom - farTop) / dist); j++) {
			pos.setX(farLeft + dist * i);
			pos.setY(farTop + dist * j);
			newNode.setPos(pos);
			newNodes.push_back(newNode);
		}
	}

	int linesCollided = 0;
	for (auto& j : newNodes) {
		for (int i = 0; i < std::size(nodes); i++) {
			if (collision.lineVsLine(j.getPos().getX(), j.getPos().getY(), j.getPos().getX(), farBottom + 1, nodes[i].getPos().getX(), nodes[i].getPos().getY(), nodes[(i + 1) % std::size(nodes)].getPos().getX(), nodes[(i + 1) % std::size(nodes)].getPos().getY())) linesCollided++;
		}
		if (linesCollided % 2 == 1) {
			nodes.push_back(j);
			linesCollided = 0;
		}
	}

	for (unsigned int i = 0; i < std::size(nodes); i++) {
		for (unsigned int j = 0; j < std::size(nodes); j++) {
			if (collision.pointVsCircle(nodes[i].getPos(), nodes[j].getPos(), 40)) {
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
void SoftBody::update(double deltaTime) {
	for (auto &i : nodes) {
		i.update(deltaTime);
		//i.lineCollision({ 200,400,600,200 });
	}
	for (auto &i : springs) {
		i.update();
		//i.pointCollision({ 600,200 });
	}
}
void SoftBody::draw(SDL_Renderer* renderer, SDL_Rect screen) {
	for (auto &i : springs) {
		i.draw(renderer, screen);
	}
	for (auto &i : nodes) {
		//i.draw(renderer, screen);
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