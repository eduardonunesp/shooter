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

		bool Init();
		void Read();
		void Destroy();
		inline bool HasQuit() { return hasQuit; }
		bool KeyDown(SDL_Scancode keyCode);

	private:
		InputManager() {}
		~InputManager() {}

		const Uint8* keystates;
		bool hasQuit;
		static InputManager* instance;
	};
}

