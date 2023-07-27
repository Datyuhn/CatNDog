#pragma once
#include "SDL_mixer.h"
#include <string>
class Sound
{
public:
	Sound(std::string pathMusic);
	~Sound();
	bool Init();
	void PlaySound();
	void PauseSound();
	void ResumeSound();
	void StopSound();
	void LoadSound(std::string pathMusic);
	void Free();
	static inline bool isPlay = true;
private:
	std::string m_PathMusic;
	Mix_Music* m_Music = NULL;
	
};
