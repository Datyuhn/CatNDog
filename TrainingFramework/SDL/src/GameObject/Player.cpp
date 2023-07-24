#include "Player.h"
#include "TextureManager.h"
#include <SDL_scancode.h>
#include <SDL_render.h>
#include "GameObject/SpriteAnimation.h"
#include <vector>
#include "ResourceManagers.h"
#include "Define.h"
Player::Player(int playerID)
{
	m_playerID = playerID;
	Init();
	m_KeyPress = 0;
}

Player::~Player() {}

void Player::Init()
{
	// Normal animation
	text = "normal19_" + std::to_string(m_playerID) + ".png";
	auto texture = ResourceManagers::GetInstance()->GetTexture(text);

	crtAnimation = std::make_shared<SpriteAnimation>(texture, 1, 19, 1, 0.04f);
	crtAnimation->SetFlip(SDL_FLIP_HORIZONTAL);
	crtAnimation->SetSize(150, 144);
	if (m_playerID == 1)
	{
		crtAnimation->Set2DPosition((SCREEN_WIDTH - crtAnimation->GetWidth() / 2) / 4, SCREEN_HEIDHT - crtAnimation->GetHeight() - 20);
	}
	else
	{
		crtAnimation->Set2DPosition((SCREEN_WIDTH - crtAnimation->GetWidth() / 2) * 3 / 4, SCREEN_HEIDHT - crtAnimation->GetHeight() - 20);
	}

	// Eat animation
	text = "eating21_" + std::to_string(m_playerID) + ".png";
	texture = ResourceManagers::GetInstance()->GetTexture(text);

	eatAnimation = std::make_shared<SpriteAnimation>(texture, 1, 21, 1, 0.03f);
	eatAnimation->SetFlip(SDL_FLIP_HORIZONTAL);
	eatAnimation->SetSize(150, 144);
	if (m_playerID == 1)
	{
		eatAnimation->Set2DPosition((SCREEN_WIDTH - crtAnimation->GetWidth() / 2) / 4, SCREEN_HEIDHT - crtAnimation->GetHeight() - 20);
	}
	else
	{
		eatAnimation->Set2DPosition((SCREEN_WIDTH - crtAnimation->GetWidth() / 2) * 3 / 4, SCREEN_HEIDHT - crtAnimation->GetHeight() - 20);
	}
	//	eatAnimation->Set2DPosition(SCREEN_WIDTH / 2 - 60, SCREEN_HEIDHT - crtAnimation->GetHeight());
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
		//Adjust the velocity
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
		//Adjust the velocity
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

void Player::Update(float deltaTime)
{
	Vector2 posPlayer = crtAnimation->Get2DPosition();
	if (m_KeyPress == 1)
	{
		posPlayer.x -= 300 * deltaTime;
	}
	if (m_KeyPress == 4)
	{
		posPlayer.x += 300 * deltaTime;
	}
	crtAnimation->Set2DPosition(posPlayer.x, posPlayer.y);
	crtAnimation->Update(deltaTime);
}

void Player::Set2DPosition(float x, float y)
{
	m_playerPos = Vector2((float)x, (float)y);
}

//void Player::MoveLeft(float deltaTime)
//{
//	m_playerPos.x += 200 * deltaTime;
//}

Vector2 Player::Get2DPosition()
{
	return Vector2(m_playerPos.x, m_playerPos.y);
}

int Player::GetWidth()
{
	return crtAnimation->GetWidth();
}

int Player::GetHeight()
{
	return crtAnimation->GetHeight();
}


int Player::GetPoint(int g_point)
{
	return g_point;
}

