#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "GameObject/Text.h"
#include "GameObject/Timer.h"
#include <vector>

class Sprite2D;
class Player;
class SpriteAnimation;
class FallingObject;
class Items;
class Collision;
class Timer;

class GSPlay :	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;
	void	Pause() override;
	void	Resume() override;
	void	SpawnFood();

	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;
	int		m_KeyPress;
	SDL_Rect p_char1, p_char2, item;
	int		temp;

private:
	std::shared_ptr<Sprite2D>						m_background, frm, floor, wall;

	std::vector<std::shared_ptr<Player>>			m_listCharacter;
	std::shared_ptr<Player>							p1, p2;

	std::shared_ptr<Text>							m_score1, m_score2;
	std::shared_ptr<Text>							m_time;
	std::vector<std::shared_ptr<Text>>				m_listScore;

	std::list<std::shared_ptr<MouseButton>>			m_listButton;
	std::shared_ptr<MouseButton>					button, btnPause;

	std::vector<std::shared_ptr<FallingObject>>		m_listFood;
	std::shared_ptr<FallingObject>					food;

	std::vector<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<SpriteAnimation>				obj;
	
	Timer g_timer, t_duration, food_timer;
	
	SDL_Color m_scoreColor = {255, 255, 255, 255};
	std::vector<SDL_Scancode> p_controlKey;

	float time = 0.0f;
	float m_VelocityX = 600.0f;
	float m_VelocityY = 500.0f;
	bool isPaused = false;
	bool inTime = false;
	bool isActive = true;
	int	 g_point1, g_point2;
};

