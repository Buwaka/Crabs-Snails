#include "stdafx.h"
#include "SoundManager.h"
#include "Map.h"


SoundManager::SoundManager()
{

	m_SFX.resize(Sounds::size);

	m_SFX[punch] = Mix_LoadWAV("resources/punch.wav");

	m_SFX[bow] = Mix_LoadWAV("resources/bow.wav");

	m_SFX[sword] = Mix_LoadWAV("resources/sword.wav");

	m_Volume = 48;

	Mix_VolumeMusic(m_Volume + 36);
	Mix_Volume(-1, m_Volume);

}


SoundManager::~SoundManager()
{
	StopAll();

	for (Mix_Chunk* chunk : m_SFX)
	{
		Mix_FreeChunk(chunk);
	}

}

void SoundManager::PlaySound(Sounds type)
{
	Mix_PlayChannel(type, m_SFX[type], 0);
}

bool SoundManager::IsPlaying(int track)
{
	return (Mix_Playing(track) > 0);
}

void SoundManager::PlayMusic(Map * stage)
{
	Mix_PlayMusic(stage->GetBGM(), -1);
}

void SoundManager::StopAll()
{
	Mix_HaltMusic();
	Mix_HaltChannel(-1);
}

void SoundManager::IncreaseVolume()
{
	m_Volume += 4;

	m_Volume = std::min(m_Volume, MIX_MAX_VOLUME - 36);

	Mix_VolumeMusic(m_Volume  + 36);
	Mix_Volume(-1, m_Volume);
}

void SoundManager::DecreaseVolume()
{
	m_Volume -= 4;

	m_Volume = std::min(m_Volume, MIX_MAX_VOLUME - 36);

	Mix_VolumeMusic(m_Volume + 36);
	Mix_Volume(-1, m_Volume);
}
