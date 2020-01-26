#pragma once

#ifdef WIN 
#define main SDL_main
#endif

#include <string>
#include <map>

namespace Thing2D {
	enum class PlatformOS {
		UNKNOW = 0x0,
		MACOS = 0x1,
		IOS_SIM = 0x2,
		IOS_IPHONE = 0x3,
		WIN_386 = 0x4,
		WIN_X64 = 0x5,
		LINUX = 0x6
	};

	class VideoManager;
	class InputManager;
	class AudioManager;
	class TiledMapLoader;
	class State;

	class Game {
	public:
		Game(int screen_width, int screen_height);
		virtual ~Game();

		// Lifecycle
		virtual void init();
		virtual void run();
		virtual void destroy();

		// State management
		void add_state(const std::string& state_id, State* state, bool is_the_current_state = false);
		auto get_state_by_id(const std::string& state_id);
		void set_current_state(const std::string& state_id);
		State* get_current_state();

		// Window properties
		inline int get_screen_width() { return screen_width; }
		inline int get_screen_height() { return screen_height; }

		// Core properties
		inline unsigned int delta_time() { return frame_time; }
		
		inline void halt() {
			running = false;
		}

		inline PlatformOS& get_curr_platform_os() {
			return curr_platform_os;
		}

		inline bool is_debug_mode() {
			return debug_mode;
		}

	protected:
		bool debug_mode;
		int screen_width;
		int screen_height;

		VideoManager* video_manager;
		InputManager* input_manager;
		AudioManager* audio_manager;
		TiledMapLoader* tiled_map_loader;

	private:
		PlatformOS curr_platform_os;
		bool running;
		unsigned int frame_time;
		State* current_state;
		std::map<std::string, State*> states;
	};

	Game* CreateGame();
}
