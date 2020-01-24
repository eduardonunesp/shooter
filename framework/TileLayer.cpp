#include "TileLayer.h"

namespace Thing2D {
	TileLayer::TileLayer(const std::string& name) : 
		Layer(), name(name) {}

	TileLayer::TileLayer(float x, float y, const std::string& name) :
		Layer(x, y), name(name) {}
}
