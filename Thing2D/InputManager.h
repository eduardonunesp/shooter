#pragma once

#include <SDL.h>
#include <map>

namespace Thing2D {
	class InputManager {
	public:
		InputManager() : quit_pressed(false), focused(true) {}
		~InputManager() {}

		bool init();
		void read();
		void destroy();
		inline bool has_quit() { return quit_pressed; }\
		inline bool has_focus() { return focused; }
		bool is_key_down(SDL_Scancode key_code);
		bool is_key_up(SDL_Scancode key_code);

	private:
		std::map<SDL_Scancode, bool> keys_up;
		std::map<SDL_Scancode, bool> keys_down;
		bool quit_pressed;
		bool focused;
		static InputManager* instance;
	};
}
