#include "InputManager.h"
#include "Logger.h"

namespace Thing2D {
	InputManager* InputManager::instance = NULL;

	bool InputManager::init()	{
		LOG("Initialize Input Manager");

		int iResult = SDL_InitSubSystem(SDL_INIT_JOYSTICK);
		if (iResult < 0)
			return false;
		return true;
	}

	void InputManager::read() {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit_pressed = true;
				break;
			case SDL_KEYDOWN:
				keystates = SDL_GetKeyboardState(0);
				break;

			case SDL_KEYUP:
				keystates = SDL_GetKeyboardState(0);
				break;
			}
		}
	}

	void InputManager::destroy() {
		SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
	}
	
	bool InputManager::key_down(SDL_Scancode keyCode) {
		return keystates != 0 ? keystates[keyCode] : false;
	}
}