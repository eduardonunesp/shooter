#include "AudioManager.h"
#include "Logger.h"
#include <algorithm>

namespace Thing2D {
	void AudioManager::Sound::play() {
		Mix_PlayChannel(-1, mix_chunk, 0);
	}
	
	void AudioManager::Music::play() {
		if (!Mix_PlayingMusic()) {
			if (Mix_PlayMusic(mix_music, loop ? -1 : 1) == -1) {
				ERR("Play Music: " << Mix_GetError());
			}
		}
	}
	
	void AudioManager::Music::halt() {
		Mix_HaltMusic();
	}
	
	void AudioManager::Music::stop() {
		Mix_PauseMusic();
	}
	
	void AudioManager::Music::resume() {
		Mix_ResumeMusic();
	}

	AudioManager::~AudioManager() {
		std::for_each(musics.begin(), musics.end(), [](auto music) {
			music.second->halt();
			delete music.second;
		});
	}

	void AudioManager::init() {
		LOG("Initialize Audio Manager");

		if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) < 0) {
			throw "Failed to init Mixer";
		}

		if (Mix_OpenAudio(22050, AUDIO_S16, 2, (4096 / 2) < 0)) {
			throw "Failed to init OpenAudio";
		}
	}

	void AudioManager::load_music(const std::string& file_path, bool loop, int volume, const std::string& music_id) {
		LOG("Loading music " << file_path << " " << music_id);

		Mix_VolumeMusic(volume);
		auto mix_music = Mix_LoadMUS(file_path.c_str());

		if (mix_music) {
			auto music = new Music();
			music->loop = loop;
			music->volume = volume;
			music->mix_music = mix_music;
			musics[music_id] = music;
		} else {
			ERR("Music not loaded " << music_id << " (" << SDL_GetError() << ")");
		}
	}
	
	void AudioManager::play_music(const std::string& music_id) {
		auto music = musics[music_id];
		if (music) {
			music->play();
		}
	}
	
	void AudioManager::stop_music(const std::string& music_id) {
		auto music = musics[music_id];
		if (music) {
			music->stop();
		}
	}
	
	void AudioManager::resume_music(const std::string& music_id) {
		auto music = musics[music_id];
		if (music) {
			music->resume();
		}
	}
	
	void AudioManager::load_sound(const std::string& file_path, const std::string& sound_id) {
		LOG("Loading sound " << file_path << " " << sound_id);

		auto chunk = Mix_LoadWAV(file_path.c_str());
		if (chunk) {
			auto sound = new Sound();
			sound->mix_chunk = chunk;
			sounds[sound_id] = sound;
		} else {
			ERR("Music not loaded " << sound_id << " (" << SDL_GetError() << ")");
		}
	}
	
	void AudioManager::play_sound(const std::string& sound_id) {
		auto sound = sounds[sound_id];
		if (sound) {
			sound->play();
		}
	}
}
