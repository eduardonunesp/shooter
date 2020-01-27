#include <algorithm>
#include "Layer.h"
#include "GameObject.h"

namespace Thing2D {
	Layer::Layer() : 
		Layer(0) {}

	Layer::Layer(int order) :
		Group(), order(order) {}

	Layer::Layer(float x, float y) : 
		Group(x, y), order(0) {}

	void Layer::render() {
		if (!visible) {
			return;
		}

		std::for_each(game_objects.begin(), game_objects.end(), [](auto game_object) {
			if (!game_object->dead) {
				return game_object->render();
			}
		});
	}
}
