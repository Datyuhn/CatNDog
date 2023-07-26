#include "Player.h"
#include "TextureManager.h"
#include <SDL_scancode.h>
#include <SDL_render.h>
#include "GameObject/SpriteAnimation.h"
#include <vector>
#include "ResourceManagers.h"
#include "Define.h"
#include "Collision.h"
#include <iostream>

Player::Player(int playerID, int boundLeft, int boundRight)
{
	m_playerID = playerID;
	m_boundLeft = boundLeft;
	m_boundRight = boundRight;
	Init();
	m_KeyPress = 0;
}

Player::~Player() {}

void Player::Init()
{
	// Normal animation
	text = "normal19_" + std::to_string(m_playerID) + ".png";
	auto texture = ResourceManagers::GetInstance()->GetTexture(text);

	crtAnimation = std::make_shared<SpriteAnimation>(texture, 1, 19, 1, 0.045f);
	crtAnimation->SetFlip(SDL_FLIP_HORIZONTAL);
	crtAnimation->SetSize(150, 144);
	if (m_playerID == 1)
	{
		crtAnimation->Set2DPosition((SCREEN_WIDTH - crtAnimation->GetWidth() / 2) / 4, SCREEN_HEIDHT - crtAnimation->GetHeight() - 60);
	}
	else
	{
		crtAnimation->Set2DPosition((SCREEN_WIDTH - crtAnimation->GetWidth() / 2) * 3 / 4, SCREEN_HEIDHT - crtAnimation->GetHeight() - 60);
	}

	// Eat animation
	text = "eating21_" + std::to_string(m_playerID) + ".png";
	texture = ResourceManagers::GetInstance()->GetTexture(text);

	eatAnimation = std::make_shared<SpriteAnimation>(texture, 1, 21, 1, 0.03f);
	eatAnimation->SetFlip(SDL_FLIP_HORIZONTAL);
	eatAnimation->SetSize(150, 144);
	eatAnimation->changeAnimation = [=]() mutable {
		crtAnimation->Set2DPosition(eatAnimation->Get2DPosition().x, eatAnimation->Get2DPosition().y);
		IdleAnimation = crtAnimation;
	};

	IdleAnimation = crtAnimation;
}

void Player::Draw(SDL_Renderer* renderer)
{
	IdleAnimation->Draw(renderer);
	/*SDL_Rect collider = { (int)m_position.x + 70, (int)m_position.y + 75, m_iWidth - 110, m_iHeight - 130 };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 150);
	SDL_RenderDrawRect(renderer, &collider);*/
}

void Player::SetControl(const std::vector<SDL_Scancode>& p_control)
{
	p_controlKey = p_control;
}

void Player::HandleKeyEvents(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) //For e.key.repeat it's because key repeat is enabled by default and if you press and hold a key it will report multiple key presses. That means we have to check if the key press is the first one because we only care when the key was first pressed.
	{
		if (e.key.keysym.scancode == p_controlKey[0])
		{
			m_KeyPress |= 1;
		}
		else if (e.key.keysym.scancode == p_controlKey[1])
		{
			m_KeyPress |= 1 << 2;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		if (e.key.keysym.scancode == p_controlKey[0])
		{
			m_KeyPress ^= 1;
		}
		else if (e.key.keysym.scancode == p_controlKey[1])
		{
			m_KeyPress ^= 1 << 2;
		}
	}
}

//bool Player::CheckCollision(SDL_Rect& x, SDL_Rect& y)
//{
//	if (Collision::checkCollision(x, y)) {
//		ChangeAnimation();
//		return true;
//	}
//
//	return false;
//}

void Player::ChangeAnimation()
{
	Vector2 pos_animation = IdleAnimation->Get2DPosition();

	if (IdleAnimation == crtAnimation) {
		eatAnimation->Set2DPosition(pos_animation.x, pos_animation.y);
		IdleAnimation = eatAnimation;
	}
}

void Player::Update(float deltaTime)
{
	Vector2 posPlayer = IdleAnimation->Get2DPosition();
	if (m_KeyPress == 1)
	{
		posPlayer.x -= 1000 * deltaTime;
	}
	if (m_KeyPress == 4)
	{
		posPlayer.x += 1000 * deltaTime;
	}
	if (posPlayer.x < m_boundLeft) {
		posPlayer.x = m_boundLeft;
	}
	else if (posPlayer.x > m_boundRight) {
		posPlayer.x = m_boundRight;
	}
	IdleAnimation->Set2DPosition(posPlayer.x, posPlayer.y);
	IdleAnimation->Update(deltaTime);
}

void Player::Set2DPosition(float x, float y)
{
	m_playerPos = Vector2((float)x, (float)y);
}

Vector2 Player::Get2DPosition()
{
	return IdleAnimation->Get2DPosition();
}

int Player::GetWidth()
{
	return IdleAnimation->GetWidth();
}

int Player::GetHeight()
{
	return IdleAnimation->GetHeight();
}
