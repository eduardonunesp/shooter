#include "Group.h"
#include "GameObject.h"
#include "Logger.h"

namespace Thing2D {
	int Group::id_counter = 0;

	void Group::init() {
		LOG("Initialize scene");
	}

	void Group::update() {
		for (GameObject* game_object : game_objects) {
			game_object->move(x, y);
			game_object->update();
		}
	}

	void Group::add(const std::string& id, GameObject* game_object) {
		LOG("Adding game object:" + id);

		if (game_object) {
			game_object->move(x, y);
			game_objects.push_back(game_object);
			game_object_map[id] = game_object;
		}
	}

	void Group::add(GameObject* game_object) {
		add("__INTERNAL_ID_" + std::to_string(id_counter), game_object);
		id_counter++;
	}

	void Group::add(Group* other_group)	{
		for (GameObject* game_object : other_group->game_objects) {
			add(game_object);
		}
	}

	void Group::remove(GameObject* game_object)	{
		std::vector<GameObject*>::iterator position = std::find(game_objects.begin(), game_objects.end(), game_object);
		if (position != game_objects.end()) {
			game_objects.erase(position);
		}
	}

	void Group::remove(const std::string& id) {
		LOG("Remove object " + id);
		remove(game_object_map[id]);
	}

	int Group::count_visible() {
		int count = 0;
		for (GameObject* game_object : game_objects) {
			if (game_object->is_visible()) {
				count++;
			}
		}
		return count;
	}

	int Group::count_dead() {
		int count = 0;
		for (GameObject* game_object : game_objects) {
			if (game_object->is_dead()) {
				count++;
			}
		}
		return count;
	}

	void Group::draw() {
		for (GameObject* game_object : game_objects) {
			game_object->draw();
		}
	}

	void Group::destroy() {
		for (GameObject* game_object : game_objects) {
			game_object->destroy();
		}
	}
}