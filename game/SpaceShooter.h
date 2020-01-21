#pragma once

#include <Thing2D.h>

using namespace Thing2D;

class PlayState;

class SpaceShooter : public Game {
public:
	SpaceShooter() : Game(640, 480) {}
	void init() override;

private:
	PlayState* play_state;
};