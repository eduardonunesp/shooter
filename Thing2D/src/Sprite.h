#pragma once

#include "GameObject.h"
#include <vector>
#include <map>

namespace Thing2D {
	class Sprite : public GameObject {
	public:
		Sprite(const std::string& texture_id, float x, float y, int width, int height);
		Sprite(const std::string& texture_id, float x, float y, int width, int height, int rows, int cols);
		virtual ~Sprite();

		void add_animations(const std::string& name, int speed, bool loop, int frames, ...);
		void add_animations(const std::string& name, int speed);
		void play(const std::string& animation_name);

		virtual void update();
		void draw();
		virtual void destroy();

	private:
		struct AnimFrame {
			AnimFrame(int x, int y) :
				row(x),
				col(y) {}

			int row;
			int col;
		};

		struct Animation {
			Animation() :
				loop(false),
				sum(0),
				anim_speed(1),
				curr_anim_frame(0) {}

			bool loop;
			int sum;
			int anim_speed;
			int curr_anim_frame;
			std::vector<int> frames;
		};

		void calculate_frames(int rows, int cols);

		Animation *curr_animation;
		std::vector<AnimFrame*> anim_frames;
		std::map<std::string, Animation*> animations;
	};
}