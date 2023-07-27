#pragma once
#include "BaseObject.h"
//#include "GameStateBase.h"
#include "SDL_scancode.h"
#include <vector>
#include <string>
#include "Sound.h"

class Collision;
class Sprite2D;
class SpriteAnimation;
class TextureManager;

class Player
{
protected:
	int m_playerID;
	int m_boundLeft, m_boundRight;
	std::string text;
	std::vector<SDL_Scancode> p_controlKey;
	Vector2 m_playerPos;

public:
	Player() {}
	Player(int playerID, int boundLeft, int boundRight);
	~Player();

	void	Init();
	void	Draw(SDL_Renderer* renderer);
	void	Update(float deltatime);

	void	SetControl(const std::vector<SDL_Scancode>& p_control);
	void	HandleKeyEvents(SDL_Event& e);
	//bool	CheckCollision(SDL_Rect& x, SDL_Rect& y);
	void	ChangeAnimation();
	void	Set2DPosition(float x, float y);
	int		GetWidth();
	int		GetHeight();

	Vector2	Get2DPosition();

private:
	std::vector<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<SpriteAnimation>				crtAnimation;
	std::shared_ptr<SpriteAnimation>				IdleAnimation;
	std::shared_ptr<SpriteAnimation>				eatAnimation;

	//Vector2	MoveDirection;
	int player_id;
	int g_point;
	int m_KeyPress;

	float time = 0.0f;
	float m_VelocityX = 600.0f;
	float m_VelocityY = 250.0f;
	bool isActive;

};

