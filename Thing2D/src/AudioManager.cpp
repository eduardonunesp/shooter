#include "AudioManager.h"
#include "Logger.h"
#include <algorithm>

namespace Thing2D {
	void AudioManager::Sound::play() {
		Mix_PlayChannel(-1, mix_chunk, 0);
	}
	
	void AudioManager::Music::play() {
		if (!Mix_PlayingMusic()) {
			LOG("PLAY: ");
			Mix_PlayMusic(mix_music, (int)loop);
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

	void AudioManager::load_music(const std::string& file_path, bool loop, int volume, const std::string& music_id) {
		if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) < 0) {
			throw "Failed to init Mixer";
		}
		
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
			throw "Failed to init OpenAudio";
		}

		Mix_VolumeMusic(volume);
		auto music = Mix_LoadMUS(file_path.c_str());

		if (music) {
			auto music = new Music();
			music->loop = loop;
			music->volume = volume;
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
}
