#pragma once
#include "SDL.h"

class Collision
{
public:
	Collision();
	~Collision();
	static bool checkCollision(const SDL_Rect& rect1, const SDL_Rect& rect2);
	
};

