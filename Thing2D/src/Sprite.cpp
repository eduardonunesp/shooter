#include "Sprite.h"
#include "Logger.h"
#include "VideoManager.h"
#include <cstdarg>

namespace Thing2D {
	Sprite::Sprite(const std::string& texture_id, float x, float y, int width, int height) :
		GameObject(texture_id, x, y, width, height), curr_animation(NULL) {
		calculate_frames(0, 0);
	}

	Sprite::Sprite(const std::string& texture_id, float x, float y, int width, int height, int rows, int cols) :
		GameObject(texture_id, x, y, width, height), curr_animation(NULL) {
		calculate_frames(rows, cols);
	}

	Sprite::~Sprite() {
		destroy();
	}

	void Sprite::add_animations(const std::string& name, int speed, bool loop, int frames, ...) {
		Animation* new_animation = new Animation();
		new_animation->anim_speed = speed;
		new_animation->loop = loop;

		va_list marker;
		va_start(marker, frames);

		for (int i = 0; i < frames; i++) {
			int f = va_arg(marker, int);
			LOG("Add animation " + name + " with frame: " + std::to_string(f));
			new_animation->frames.push_back(f);
		}

		va_end(marker);
		animations[name] = new_animation;
		curr_animation = new_animation;
	}

	void Sprite::add_animations(const std::string& name, int speed) {
		add_animations(name, speed == 0 ? 1 : speed, false, 1, 0);
	}

	void Sprite::play(const std::string& animation_name) {
		Animation* animation = animations[animation_name];
		if (animation) {
			curr_animation = animation;
		}
	}

	void Sprite::update() {
		if (curr_animation) {
			curr_animation->set_current_frame(int(((SDL_GetTicks() / (1000 / curr_animation->anim_speed)) % curr_animation->frames.size())));
		}

		GameObject::update();
	}

	void Sprite::draw() {
		if (curr_animation) {
			Animation* animation = curr_animation;
			AnimFrame* anim_frame = anim_frames[animation->curr_anim_frame];
			curr_row = anim_frame->row;
			curr_col = anim_frame->col;
		}

		GameObject::draw();
	}

	void Sprite::destroy() {
		for (AnimFrame* anim_frame : anim_frames) {
			delete anim_frame;
		}
	}

	void Sprite::calculate_frames(int rows, int cols) {
		for (int x = 0; x < rows; x++) {
			for (int y = 0; y < cols; y++) {
				LOG("Parse sprite frame " << x << ":" << y);
				anim_frames.push_back(new AnimFrame(x, y));
			}
		}
	}

	void Sprite::Animation::set_current_frame(int frame) {
		if (curr_anim_frame == frame) {
			return;
		}

		if (ended) {
			return;
		}

		if (!loop) {
			sum++;

			if (sum >= frames.size()) {
				ended = true;
			}
		}

		LOG(frame);

		curr_anim_frame = frame;
	}
}
