#pragma once

#include <SDL.h>

namespace Thing2D {
	class InputManager {
	public:
		static InputManager* Instance() {
			if (!instance) {
				instance = new InputManager();
			}

			return instance;
		}

		bool init();
		void read();
		void destroy();
		inline bool has_quit() { return quit_pressed; }
		bool key_down(SDL_Scancode keyCode);

	private:
		InputManager() {}
		~InputManager() {}

		const Uint8* keystates;
		bool quit_pressed;
		static InputManager* instance;
	};
}

