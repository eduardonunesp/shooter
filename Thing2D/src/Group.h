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
			position(x, y),
			video_manager(nullptr),
			input_manager(nullptr) {}

		Group() :
			position(0, 0),
			video_manager(nullptr),
			input_manager(nullptr) {}

		virtual ~Group() {
			destroy();
		};

		virtual void init() {};
		virtual void update();
		virtual void destroy();

		virtual void add(const std::string& game_object_id, GameObject* game_object);
		virtual void add(GameObject* game_object);
		virtual void add(Group* other_group);

		void remove(GameObject* game_object_to_remove);
		void remove(const std::string& game_object_id);
		inline auto get(const std::string& id) { return game_objects_map[id]; }
		void draw();

		int count() { return game_objects.size(); }
		int count_visible();
		int count_dead();

	protected:
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
