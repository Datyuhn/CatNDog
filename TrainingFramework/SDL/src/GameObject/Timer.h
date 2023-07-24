#pragma once
#include<SDL_stdinc.h>
class Timer
{
public:
	Timer();
	
	// The various clock actions
	void Start();
	void Stop();
	void Pause();
	void UnPause();
	void SetDuration(Uint32 duration);
	Uint32 GetDuration();

	//Getsthe timer's time
	Uint32 GetTicks();
	//Checks the status of the timer
	bool IsStarted();
	bool IsPaused();
private:
	//Duration time
	Uint32 mDuration;
	//The clock time when the timer started
	Uint32 mStartTicks;
	//The ticks stored when the timer was paused
	Uint32 mPausedTicks;
	//The timer status
	bool mPaused;
	bool mStarted;
};

