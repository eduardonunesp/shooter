#pragma once

#include "GameObject.h"
#include <vector>
#include <map>

namespace Thing2D {
	class AnimationFrame;
	class Animation;

	class Sprite : public GameObject {
	public:
		Sprite(const std::string& texture_id, float x, float y, int width, int height);
		Sprite(const std::string& texture_id, float x, float y, int width, int height, int rows, int cols);
		virtual ~Sprite();

		void add_animations(const std::string& animation_id, int speed, bool loop, int frames, ...);
		void add_idle_animation(const std::string& animation_id);
		void play(const std::string& animation_id);

		virtual void init();
		virtual void update();
		virtual void draw();
		virtual void destroy();

	private:
		void calculate_frames(int rows, int cols);

		std::vector<AnimationFrame*> anim_frames;
		std::map<std::string, Animation*> animations;

	protected:
		Animation* curr_animation;
	};
}
