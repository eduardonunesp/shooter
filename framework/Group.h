#pragma once
#include <string>
#include <vector>
#include <map>
#include "Vector.h"

namespace Thing2D {
	class GameObject;
	class VideoManager;
	class InputManager;
	class AudioManager;
	class Game;

	class Group {
	public:
		Group(float x, float y) :
			visible(true),
			position(x, y),
			video_manager(nullptr),
			input_manager(nullptr),
			audio_manager(nullptr),
			game(nullptr) {}

		Group() :
			visible(true),
			position(0, 0),
			video_manager(nullptr),
			input_manager(nullptr),
			audio_manager(nullptr),
			game(nullptr) {}

		virtual ~Group() {
			destroy();
		};

		// Life cycle
		virtual void init() {};
		virtual void update();
		void draw();
		virtual void destroy();

		// Adding game objects
		virtual void add(const std::string& game_object_id, GameObject* game_object);
		virtual void add(GameObject* game_object);
		virtual void add(Group* other_group);

		inline auto get(const std::string& game_object_id) { return game_objects_map[game_object_id]; }

		// Killing
		void kill(GameObject* game_object_to_kill);
		void kill(const std::string& game_object_id);
		
		// Remove (be careful)
		void remove(GameObject* game_object_to_remove);
		void remove(const std::string& game_object_id);

		// Queries
		unsigned int count() { return game_objects.size(); }
		int count_visible();
		int count_dead();
		std::vector<GameObject*> all_by_tag(const std::string& tag);

	protected:
		friend class State;

		bool visible;
		Vector position;

		VideoManager* video_manager;
		InputManager* input_manager;
		AudioManager* audio_manager;
		Game* game;

	private:
		static int id_counter;
		std::map<std::string, GameObject*> game_objects_map;
		std::vector<GameObject*> game_objects;
	};
}
