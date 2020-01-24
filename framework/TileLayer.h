#pragma once

#include <string>
#include <map>
#include "Layer.h"
#include "Props.h"

namespace Thing2D {
	class TileLayer : public Layer, public Props {
	public:
		TileLayer(const std::string &name);
		TileLayer(float x, float y, const std::string& name);

	protected:
		std::string name;
		int width;
		int height;
	};
}