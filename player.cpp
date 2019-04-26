#include "stdafx.h"

void Player::centerCamera(Camera &camera, double deltaTime) {
	camera.pos.setX(camera.pos.getX() + (centerNode.getPos().getX() - camera.w / 2 - camera.pos.getX()) * 4 * deltaTime);
	camera.pos.setY(camera.pos.getY() + (centerNode.getPos().getY() - camera.h / 2 - camera.pos.getY()) * 4 * deltaTime);
	camera.screen.x = (int)camera.pos.getX();
	camera.screen.y = (int)camera.pos.getY();
}
void Player::move(SDL_Event &e, const Uint8 *keyboard_state_array) {
	SDL_PollEvent(&e);
	keyboard_state_array = SDL_GetKeyboardState(NULL);
	if (keyboard_state_array[SDL_SCANCODE_D] || keyboard_state_array[SDL_SCANCODE_RIGHT]) {
		for (auto &i : softBody.nodes) {
			i.applyForceX(cos(atan2(i.getPos().getY() - centerNode.getPos().getY(), i.getPos().getX() - centerNode.getPos().getX()) + .5 * M_PI) * 5);
			i.applyForceY(sin(atan2(i.getPos().getY() - centerNode.getPos().getY(), i.getPos().getX() - centerNode.getPos().getX()) + .5 * M_PI) * 5);
		}
	} if (keyboard_state_array[SDL_SCANCODE_A] || keyboard_state_array[SDL_SCANCODE_LEFT]) {
		for (auto &i : softBody.nodes) {
			i.applyForceX(cos(atan2(i.getPos().getY() - centerNode.getPos().getY(), i.getPos().getX() - centerNode.getPos().getX()) - .5 * M_PI) * 5);
			i.applyForceY(sin(atan2(i.getPos().getY() - centerNode.getPos().getY(), i.getPos().getX() - centerNode.getPos().getX()) - .5 * M_PI) * 5);
		}
	}
}
void Player::update(double deltaTime, Level level) {
	softBody.update(deltaTime);
	centerNode.update(deltaTime);
	for (auto &i : softBody.nodes) {
		level.nodeCollision(i);
	}
	for (auto& i : softBody.springs) {
		//level.springCollision(i);
	}
}
void Player::draw(SDL_Renderer* renderer, SDL_Rect screen) {
	softBody.draw(renderer, screen);
}

Player::Player() {
	radius = 50;
	Point Pos;
	Pos.setX(200);
	Pos.setY(200);
	centerNode.setPos(Pos);
	std::vector<Node> nodes;
	for (int i = 0; i < 12; i++) {
		Node newNode;
		Point newPos;
		newPos.setX(Pos.getX() + cos((i * 30) * M_PI / 180) * radius);
		newPos.setY(Pos.getY() + sin((i * 30) * M_PI / 180) * radius);
		newNode.setPos(newPos);
		nodes.push_back(newNode);
	}

	SoftBody newSoftBody(nodes);
	softBody = newSoftBody;

	softBody.fill();

	for (unsigned int i = 0; i < std::size(softBody.nodes) - 1; i++) {	
		if (collision.pointVsCircle(softBody.nodes[i].getPos(), centerNode.getPos(), 40)) {
			Spring newSpring;
			newSpring.setn1(&softBody.nodes[i]);
			newSpring.setn2(&centerNode);
			softBody.springs.push_back(newSpring);
		}
	}
}