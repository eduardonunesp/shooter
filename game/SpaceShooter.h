#pragma once

#include <Thing2D.h>

using namespace Thing2D;

class PlayState;

class SpaceShooter : public Game {
public:
	SpaceShooter();
	void init() override;

private:
	PlayState* play_state;
};