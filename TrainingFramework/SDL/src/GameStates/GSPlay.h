#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
class Sprite2D;
class SpriteAnimation;

class GSPlay :	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;
	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;
	int		m_KeyPress;

private:
	std::shared_ptr<Sprite2D>					m_background, food, frm;
	//std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<MouseButton>>		m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<SpriteAnimation>			obj;
	std::shared_ptr<MouseButton>				button, btnPause;
	Vector2										MoveDirection;
	float										time = 0.0f;
	float										m_Velocity = 175.0f;
	bool isPaused = false;
};

