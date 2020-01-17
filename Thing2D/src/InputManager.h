#pragma once

#include <SDL.h>

namespace Thing2D {
	class InputManager {
	public:
		bool Init();
		void Read();
		void Destroy();
		inline bool HasQuit() { return hasQuit; }
		bool KeyDown(SDL_Scancode keyCode);

	private:
		const Uint8* keystates;
		bool hasQuit;
	};
}

