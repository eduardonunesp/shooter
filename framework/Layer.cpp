#include "Layer.h"

namespace Thing2D {
	Layer::Layer() : 
		Layer(0) {}

	Layer::Layer(int order) :
		Group(), order(order) {}

	Layer::Layer(float x, float y) : 
		Group(x, y), order(0) {}
}
