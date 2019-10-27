#pragma once

#include <vector>

class Map;

class SoundManager
{
public:

	enum Sounds
	{
		punch, bow, sword, size
	};


	SoundManager();
	~SoundManager();

	SoundManager(const SoundManager& other) = delete;
	SoundManager& operator=(const SoundManager& other) = delete;
	SoundManager(SoundManager&& other) = delete;
	SoundManager& operator=(SoundManager&& other) = delete;

	void PlaySound(Sounds type);
	bool IsPlaying(int track = -1);
	void PlayMusic(Map* stage);
	void StopAll();

	void IncreaseVolume();
	void DecreaseVolume();



private:
	std::vector<Mix_Chunk*> m_SFX;
	int m_Volume;
};

