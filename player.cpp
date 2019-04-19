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
			i.applyForceX(cos(atan2(i.getPos().getY() - centerNode.getPos().getY(), i.getPos().getX() - centerNode.getPos().getX()) + .5 * M_PI) * 10);
			i.applyForceY(sin(atan2(i.getPos().getY() - centerNode.getPos().getY(), i.getPos().getX() - centerNode.getPos().getX()) + .5 * M_PI) * 10);
		}
	} if (keyboard_state_array[SDL_SCANCODE_A] || keyboard_state_array[SDL_SCANCODE_LEFT]) {
		for (auto &i : softBody.nodes) {
			i.applyForceX(cos(atan2(i.getPos().getY() - centerNode.getPos().getY(), i.getPos().getX() - centerNode.getPos().getX()) - .5 * M_PI) * 10);
			i.applyForceY(sin(atan2(i.getPos().getY() - centerNode.getPos().getY(), i.getPos().getX() - centerNode.getPos().getX()) - .5 * M_PI) * 10);
		}
	}
}
void Player::update(double deltaTime, SDL_Rect level) {
	softBody.update(deltaTime, level);
	centerNode.update(deltaTime);
}
void Player::draw(SDL_Renderer* renderer, SDL_Rect screen) {
	softBody.draw(renderer, screen);
}

Player::Player() {
	Point Pos;
	Pos.setX(200);
	Pos.setY(200);
	centerNode.setPos(Pos);
	std::vector<Node> nodes;
	for (int i = 0; i < 12; i++) {
		Node newNode;
		Point newPos;
		newPos.setX(Pos.getX() + cos((i * 30) * M_PI / 180) * 50);
		newPos.setY(Pos.getY() + sin((i * 30) * M_PI / 180) * 50);
		newNode.setPos(newPos);
		nodes.push_back(newNode);
	}
	SoftBody newSoftBody(nodes);
	softBody = newSoftBody;

	for (unsigned int i = 0; i < std::size(softBody.nodes); i++) {
		for (unsigned int j = 0; j < std::size(softBody.nodes); j++) {
			if (collision.pointVsCircle(softBody.nodes[i].getPos(), softBody.nodes[j].getPos(), 90)) {
				Spring newSpring;
				newSpring.setn1(&softBody.nodes[i]);
				newSpring.setn2(&softBody.nodes[j]);
				softBody.springs.push_back(newSpring);
			}
		}
	}
	for (unsigned int i = 0; i < std::size(softBody.nodes); i++) {
		Spring newSpring;
		newSpring.setn1(&softBody.nodes[i]);
		newSpring.setn2(&centerNode);
		softBody.springs.push_back(newSpring);
	}
}