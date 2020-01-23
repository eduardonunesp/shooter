#include "Sprite.h"
#include "Logger.h"
#include "VideoManager.h"
#include "AnimationFrame.h"
#include "Animation.h"
#include <cstdarg>

namespace Thing2D {
	Sprite::Sprite(const std::string& texture_id, float x, float y, int width, int height) :
		GameObject(texture_id, x, y, width, height), curr_animation(nullptr) {
		calculate_frames(0, 0);
	}

	Sprite::Sprite(const std::string& texture_id, float x, float y, int width, int height, int rows, int cols) :
		GameObject(texture_id, x, y, width, height), curr_animation(nullptr) {
		calculate_frames(rows, cols);
	}

	Sprite::~Sprite() {
		LOG("Destroying sprite resource");
		destroy();
	}

	void Sprite::init() {
		GameObject::init();
	}

	void Sprite::add_animations(const std::string& animation_id, int speed, bool loop, int frames, ...) {
		LOG("Adding animation :" << animation_id << " speed: " << speed << " loop: " << loop);

		Animation* new_animation = new Animation();
		new_animation->anim_speed = speed;
		new_animation->loop = loop;

		va_list marker;
		va_start(marker, frames);

		for (int i = 0; i < frames; i++) {
			int f = va_arg(marker, int);
			LOG("Add animation " + animation_id + " with frame: " + std::to_string(f));
			new_animation->frames.push_back(f);
		}

		va_end(marker);
		animations[animation_id] = new_animation;
		curr_animation = new_animation;
	}

	void Sprite::add_idle_animation(const std::string& animation_id) {
		add_animations(animation_id, 1, false, 1, 0);
	}

	void Sprite::play(const std::string& animation_id) {
		Animation* animation = animations[animation_id];
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
			AnimationFrame* anim_frame = anim_frames[animation->curr_anim_frame];
			curr_row = anim_frame->row;
			curr_col = anim_frame->col;
		}

		GameObject::draw();
	}

	void Sprite::destroy() {
		for (AnimationFrame* anim_frame : anim_frames) {
			delete anim_frame;
		}
	}

	void Sprite::calculate_frames(int rows, int cols) {
		LOG("Parse sprite frames " << rows << ":" << cols);
		for (int x = 0; x < rows; x++) {
			for (int y = 0; y < cols; y++) {
				anim_frames.push_back(new AnimationFrame(x, y));
			}
		}
	}
}
