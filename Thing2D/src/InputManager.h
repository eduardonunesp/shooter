#pragma once

#include <SDL.h>
#include <map>

namespace Thing2D {
	class InputManager {
	public:
		static InputManager* get_instance() {
			if (!instance) {
				instance = new InputManager();
			}

			return instance;
		}

		bool init();
		void read();
		void destroy();
		inline bool has_quit() { return quit_pressed; }
		bool is_key_down(SDL_Scancode key_code);
		bool is_key_up(SDL_Scancode key_code);

	private:
		InputManager(): quit_pressed(false) {}
		~InputManager() {}

		std::map<SDL_Scancode, bool> keys_up;
		std::map<SDL_Scancode, bool> keys_down;
		bool quit_pressed;
		static InputManager* instance;
	};
}

