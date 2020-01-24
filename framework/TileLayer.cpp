#include "TileLayer.h"

namespace Thing2D {
	TileLayer::TileLayer(const std::string& name) : 
		Layer(), name(name), height(0), width(0) {}

	TileLayer::TileLayer(float x, float y, const std::string& name) :
		Layer(x, y), name(name), height(0), width(0) {}
}
