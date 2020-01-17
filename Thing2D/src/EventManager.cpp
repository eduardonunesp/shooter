#include "EventManager.h"

namespace Thing2D {
	bool EventManager::Init()	{
        int iResult = SDL_InitSubSystem(SDL_INIT_JOYSTICK);
        if (iResult < 0)
            return false;
        return true;
	}

    void EventManager::Read() {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                hasQuit = true;
                break;
            } else {
                continue;
            }
        }
    }

    void EventManager::Destroy() {
        SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
    }   
}