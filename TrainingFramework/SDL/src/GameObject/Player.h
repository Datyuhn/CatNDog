#pragma once
#include "BaseObject.h"
#include "GameStateBase.h"
#include "SDL_scancode.h"
#include <vector>
#include <string>

class Collision;
class Sprite2D;
class SpriteAnimation;
class TextureManager;

class Player : public BaseObject, GameStateBase
{
protected:
	int m_iWidth;
	int m_iHeight;
	int m_playerID;
	
	float	m_numFrames;
	int		m_currentFrame;
	float	m_frameTime;
	float	m_currentTime;

	int		m_spriteRow;
	int		m_frameCount;
	float	m_currentTicks;
	int		m_animSpeed;
	int		m_numAction;

	Uint32	m_lastUpdate;
	SDL_RendererFlip m_flip;
	std::string text;
	std::vector<SDL_Scancode> p_controlKey;

public:
	Player() : BaseObject(), m_iWidth(0), m_iHeight(0), g_point(0), m_playerID(player_id) {}
	Player(int playerID, std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime, SDL_RendererFlip flip);
	~Player();

	void	Init() override;
	void	Draw(SDL_Renderer* renderer) override;
	void	Update(float deltatime) override;

	void	SetControl(const std::vector<SDL_Scancode>& p_control);
	void	HandleKeyEvents(SDL_Event& e) override;

	void	Set2DPosition(float x, float y);
	void	SetSize(int width, int height);
	void	SetRotation(double angle);
	void	SetFlip(SDL_RendererFlip flip);
	
	Vector2	Get2DPosition();
	int		GetWidth();
	int		GetHeight();
	int		GetPoint(int g_point);

private:
	std::vector<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<SpriteAnimation>				crtAnimation;
	
	Vector2	MoveDirection;
	//std::string text1, text2;
	int player_id;
	int g_point;
	int m_KeyPress;

	float time = 0.0f;
	float m_VelocityX = 600.0f;
	float m_VelocityY = 250.0f;
	bool isActive = true;

};

