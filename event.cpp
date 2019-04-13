#include "stdafx.h"

void Event::update(SDL_Event &e, bool &quit, bool &inGame, SDL_Rect screen) {
	SDL_PumpEvents();//push up new events
	SDL_GetMouseState(&mX, &mY);//update the mouse positions
	mPos.setX((double)mX + screen.x);
	mPos.setY((double)mY + screen.y);
	while (SDL_PollEvent(&e) != 0) {//while there are events yet to be processed
		switch (e.type) {
		case SDL_QUIT://user quits the program
			inGame = false;
			quit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			SDL_PumpEvents();
			switch (e.button.button) {
			case SDL_BUTTON_LEFT:
				m1 = true;
				break;
			case SDL_BUTTON_RIGHT:
				m2 = true;
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			SDL_PumpEvents();
			switch (e.button.button) {
			case SDL_BUTTON_LEFT:
				m1 = false;
				break;
			case SDL_BUTTON_RIGHT:
				m2 = false;
				break;
			}
			break;
		}
	}
}

bool Event::testKey(char key) {
	keyboard_state_array = SDL_GetKeyboardState(NULL);
	if (key == 'a' && keyboard_state_array[SDL_SCANCODE_A]) return true;
	else if (key == 'b' && keyboard_state_array[SDL_SCANCODE_B]) return true;
	else if (key == 'c' && keyboard_state_array[SDL_SCANCODE_C]) return true;
	else if (key == 'd' && keyboard_state_array[SDL_SCANCODE_D]) return true;
	else if (key == 'e' && keyboard_state_array[SDL_SCANCODE_E]) return true;
	else if (key == 'f' && keyboard_state_array[SDL_SCANCODE_F]) return true;
	else if (key == 'g' && keyboard_state_array[SDL_SCANCODE_G]) return true;
	else if (key == 'h' && keyboard_state_array[SDL_SCANCODE_H]) return true;
	else if (key == 'i' && keyboard_state_array[SDL_SCANCODE_I]) return true;
	else if (key == 'j' && keyboard_state_array[SDL_SCANCODE_J]) return true;
	else if (key == 'k' && keyboard_state_array[SDL_SCANCODE_K]) return true;
	else if (key == 'l' && keyboard_state_array[SDL_SCANCODE_L]) return true;
	else if (key == 'm' && keyboard_state_array[SDL_SCANCODE_M]) return true;
	else if (key == 'n' && keyboard_state_array[SDL_SCANCODE_N]) return true;
	else if (key == 'o' && keyboard_state_array[SDL_SCANCODE_O]) return true;
	else if (key == 'p' && keyboard_state_array[SDL_SCANCODE_P]) return true;
	else if (key == 'q' && keyboard_state_array[SDL_SCANCODE_Q]) return true;
	else if (key == 'r' && keyboard_state_array[SDL_SCANCODE_R]) return true;
	else if (key == 's' && keyboard_state_array[SDL_SCANCODE_S]) return true;
	else if (key == 't' && keyboard_state_array[SDL_SCANCODE_T]) return true;
	else if (key == 'u' && keyboard_state_array[SDL_SCANCODE_U]) return true;
	else if (key == 'v' && keyboard_state_array[SDL_SCANCODE_V]) return true;
	else if (key == 'w' && keyboard_state_array[SDL_SCANCODE_W]) return true;
	else if (key == 'x' && keyboard_state_array[SDL_SCANCODE_X]) return true;
	else if (key == 'y' && keyboard_state_array[SDL_SCANCODE_Y]) return true;
	else if (key == 'z' && keyboard_state_array[SDL_SCANCODE_Z]) return true;
	return false;
}