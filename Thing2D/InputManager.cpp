#include "InputManager.h"
#include "Logger.h"
#include <string>

namespace Thing2D {
	bool InputManager::init()	{
		LOG("Initialize Input Manager");

		if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0) {
			ERR("Failed to init joystick sub system");
			return false;
		}

		return true;
	}

	void InputManager::read() {
		for (std::pair<SDL_Scancode, bool> key : keys_up) {
			keys_up[key.first] = false;
		}

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit_pressed = true;
				break;

			case SDL_KEYDOWN:
				if (event.key.repeat > 0) { return; }
				LOG("Key down " + std::to_string(event.key.keysym.scancode));
				keys_down[event.key.keysym.scancode] = true;
				keys_up[event.key.keysym.scancode] = false;
				break;

			case SDL_KEYUP:
				if (event.key.repeat > 0) { return; }
				LOG("Key up " + std::to_string(event.key.keysym.scancode));
				keys_up[event.key.keysym.scancode] = true;
				keys_down[event.key.keysym.scancode] = false;
				break;
			}
		}
	}

	void InputManager::destroy() {
		LOG("Destroying input resources");
		SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
	}
	
	bool InputManager::is_key_down(SDL_Scancode key_code) {
		return keys_down[key_code];
	}

	bool InputManager::is_key_up(SDL_Scancode key_code) {
		return keys_up[key_code];
	}
}