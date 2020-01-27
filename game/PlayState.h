#pragma once

#include <Thing2D.h>

namespace Shooter {
	class Player;

	class PlayState : public Thing2D::State
	{
	public:
		PlayState();

		void init() override;
		void update() override;
	};
}