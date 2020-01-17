#include "InputManager.h"
#include "Logger.h"

namespace Thing2D {
	bool InputManager::Init()	{
		LOG("Initialize Input Manager");

		int iResult = SDL_InitSubSystem(SDL_INIT_JOYSTICK);
		if (iResult < 0)
			return false;
		return true;
	}

	void InputManager::Read() {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				hasQuit = true;
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

	void InputManager::Destroy() {
		SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
	}
	
	bool InputManager::KeyDown(SDL_Scancode keyCode) {
		if (keystates != 0) {
			return keystates[keyCode] == 1;
		}

		return false;
	}
}