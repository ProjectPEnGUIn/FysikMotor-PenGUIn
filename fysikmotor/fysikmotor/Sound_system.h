#pragma once

#include "SFML\Audio.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Main.hpp"

#include <unordered_map>
#include <memory>
#include <cassert>
#include <iostream>

#ifndef  _SOUNDSYSTEM_
#define _SOUNDSYSTEM_

class Sound_System
{
public:
	Sound_System(const std::string& filename, float volume, float pitch, bool loop)
		:
		m_musicFile(),
		m_pBuffer(nullptr),
		m_Filename(filename)

	{
		if (s_SoundBufferCache.count(filename))
		{
			m_pBuffer = s_SoundBufferCache[filename];

		}
		else
		{
			auto& soundBuffer = s_SoundBufferCache[filename];
			soundBuffer = std::make_unique<sf::SoundBuffer>();
			assert(soundBuffer != nullptr && "FEL Sound_System.h, line 20"); //Försäkrar om koden över fungerar
		
			if (!soundBuffer->loadFromFile(filename))
				std::cerr << "Failed to load sound " << filename << " correctly!\n";
			else
				std::cout << "Loaded sound " << filename << "!\n";
			m_pBuffer = soundBuffer;
		}
		assert(m_pBuffer != nullptr);
		
		m_musicFile.setBuffer(*m_pBuffer);
		m_musicFile.setVolume(volume);
		m_musicFile.setPitch(pitch);
		m_musicFile.setLoop(loop);
	};
	~Sound_System()
	{
		m_pBuffer.reset();
		//Om detta är sista instansen av ljud i "Cache" så ta bort den från "cache"
		if (s_SoundBufferCache[m_Filename].unique())
		{
			s_SoundBufferCache.erase(m_Filename);
			std::cout << "Deleted sound " << m_Filename << "!\n";
		}
	}

	void setVolume(float volume)
	{
		m_musicFile.setVolume(volume);
	}
	void setPitch(float pitch)
	{
		m_musicFile.setPitch(pitch);
	}
	void setLoop(bool loop)
	{
		m_musicFile.setLoop(loop);
	}
	void playMusic()
	{
		m_musicFile.play();
	}
	void stopMusic()
	{
		m_musicFile.stop();
	}
	void pauseMusic()
	{
		m_musicFile.pause();
	}

private:
	static std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> s_SoundBufferCache;

	std::string m_Filename;
	std::shared_ptr<sf::SoundBuffer> m_pBuffer;
	sf::Sound m_musicFile;
};
#endif // ! _SOUNDSYSTE_
