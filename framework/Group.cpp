#include <algorithm>
#include "Group.h"
#include "GameObject.h"
#include "Logger.h"
#include "VideoManager.h"
#include "InputManager.h"
#include "AudioManager.h"

namespace Thing2D {
	int Group::id_counter = 0;

	void Group::add(const std::string& game_object_id, GameObject* game_object) {
		if (!game_object) {
			return;
		}

		LOG("Adding game object label " + game_object_id + " tag " + game_object->tag);
			
		game_object->video_manager = video_manager;
		game_object->input_manager = input_manager;
		game_object->audio_manager = audio_manager;
		game_object->game = game;

		game_object->label = game_object_id;
		game_object->init();
		game_object->move(position);

		game_objects.push_back(game_object);
		game_objects_map[game_object_id] = game_object;
	}

	void Group::add(GameObject* game_object) {
		if (!game_object) {
			return;
		}

		if (game_object->label.size() == 0) {
			const std::string& auto_id = "__INTERNAL_ID__" + std::to_string(id_counter);
			add(auto_id, game_object);
			id_counter++;
		} else {
			add(game_object->label, game_object);
		}
	}

	void Group::add(Group* other_group)	{
		LOG("Adding from another group");
		std::for_each(other_group->game_objects.begin(), other_group->game_objects.end(), [&](auto game_object) {
			add(game_object);
		});
	}

	void Group::kill(GameObject* game_object_to_kill) {
		LOG("Kill game object: " << game_object_to_kill->label);
		auto game_object = std::find_if(game_objects.begin(), game_objects.end(), [&](auto game_object) {
			return game_object == game_object_to_kill;
		});

		if (game_object != game_objects.end()) {
			(*game_object)->dead = true;
		}
	}

	void Group::kill(const std::string& game_object_id) {
		kill(game_objects_map[game_object_id]);
	}

	void Group::remove(GameObject* game_object_to_remove)	{
		LOG("Removing game object: " << game_object_to_remove->label);
		game_objects.erase(std::remove_if(game_objects.begin(), game_objects.end(), [&](auto game_object) {
			return game_object == game_object_to_remove;
		}), game_objects.end());
	}

	void Group::remove(const std::string& game_object_id) {
		remove(game_objects_map[game_object_id]);
	}

	int Group::count_visible() {
		return  std::count_if(game_objects.begin(), game_objects.end(), [](auto game_object) {
			return game_object->is_visible();
		});
	}

	int Group::count_dead() {
		return  std::count_if(game_objects.begin(), game_objects.end(), [](auto game_object) {
			return game_object->is_dead();
		});
	}

	std::vector<GameObject*> Group::all_by_tag(const std::string& tag) {
		std::vector<GameObject*> objects_found;
		std::for_each(game_objects.begin(), game_objects.end(), [&](auto game_object) {
			if (game_object->tag == tag) {
				objects_found.push_back(game_object);
			}
		});
		return objects_found;
	}

	void Group::update() {
		std::for_each(game_objects.begin(), game_objects.end(), [](auto game_object) {
			if (!game_object->dead) {
				game_object->update();
			}
		});
	}

	void Group::draw() {
		if (!visible) {
			return;
		}

		std::for_each(game_objects.begin(), game_objects.end(), [](auto game_object) {
			if (!game_object->dead) {
				return game_object->draw();
			}
		});
	}

	void Group::destroy() {
		LOG("Destroy resources on group");
		std::for_each(game_objects.begin(), game_objects.end(), [](auto game_object) {
			game_object->destroy();
		});
	}
}