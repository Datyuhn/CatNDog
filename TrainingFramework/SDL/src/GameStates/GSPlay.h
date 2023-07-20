#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"

class Sprite2D;
class SpriteAnimation;
class FallingObject;
class Items;
class Collision;

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
	//SDL_Rect& character, item;

private:
	std::shared_ptr<Sprite2D>					m_background, frm;
	std::list<std::shared_ptr<FallingObject>>	m_listFood;
	std::shared_ptr<FallingObject>				food;

	//std::shared_ptr<Text>						m_score;
	std::list<std::shared_ptr<MouseButton>>		m_listButton;
	std::shared_ptr<MouseButton>				button, btnPause;

	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<SpriteAnimation>			obj;
	Vector2	MoveDirection;
	float	time = 0.0f;
	float	m_VelocityX = 600.0f;
	float	m_VelocityY = 450.0f;
	bool	isPaused = false;
	bool	isActive = true;
};

