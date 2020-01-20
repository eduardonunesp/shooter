#pragma once
#include <string>
#include <vector>
#include <map>
#include "Vector.h"

namespace Thing2D {
	class GameObject;
	class VideoManager;
	class InputManager;

	class Group {
	public:
		Group(int x, int y): position(x, y) {}
		Group() : position(0, 0) {}
		virtual ~Group() {};

		virtual void init();
		virtual void update();

		void add(const std::string& id, GameObject* game_object);
		void add(GameObject* game_object);
		void add(Group* other_group);
		void remove(GameObject* game_object);
		void remove(const std::string& id);
		inline GameObject *get(const std::string& id) {	return game_object_map[id]; }
		void draw();
		
		int count() { return game_objects.size(); }
		int count_visible();
		int count_dead();

		void destroy();

	protected:
		Vector position;

	private:
		static int id_counter;
		std::map<std::string, GameObject*> game_object_map;
		std::vector<GameObject*> game_objects;
	};
}