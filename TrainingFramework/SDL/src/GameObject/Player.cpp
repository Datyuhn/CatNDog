#include "Player.h"
#include "TextureManager.h"
#include <SDL_scancode.h>
#include <SDL_render.h>
#include "GameObject/SpriteAnimation.h"
#include <vector>

Player::Player(int playerID, std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime, SDL_RendererFlip flip)
	: BaseObject(texture), m_iWidth(100), m_iHeight(50), g_point(0), m_playerID(playerID)
{
	m_spriteRow = spriteRow;
	m_frameCount = frameCount;
	m_numAction = numAction;
	//m_animSpeed = animSpeed;
	m_frameTime = frameTime;
	m_currentFrame = 0;
	m_currentTicks = 0;
	m_lastUpdate = SDL_GetTicks();
	m_flip = flip;
	m_playerID = playerID;
	Init();
}

Player::~Player() {}

void Player::Init()
{
	// Normal animation
	text = "normal19_" + std::to_string(m_playerID) + ".png";
	auto texture = ResourceManagers::GetInstance()->GetTexture(text);
	
	crtAnimation = std::make_shared<SpriteAnimation>(texture, 1, 19, 1, 0.04f);
	//crtAnimation->SetFlip(SDL_FLIP_HORIZONTAL);
	//crtAnimation->SetSize(150, 144);
	//crtAnimation->Set2DPosition(SCREEN_WIDTH / 2 - 60, SCREEN_HEIDHT - crtAnimation->GetHeight());
	m_listAnimation.push_back(crtAnimation);

	// Eat animation
	text = "eating21_" + std::to_string(m_playerID) + ".png";
	texture = ResourceManagers::GetInstance()->GetTexture(text);

	crtAnimation = std::make_shared<SpriteAnimation>(texture, 1, 21, 1, 0.03f);
	//crtAnimation->SetFlip(SDL_FLIP_HORIZONTAL);
	//crtAnimation->SetSize(150, 144);
	//crtAnimation->Set2DPosition(SCREEN_WIDTH / 2 - 60, SCREEN_HEIDHT - crtAnimation->GetHeight());
	m_listAnimation.push_back(crtAnimation);

	crtAnimation = m_listAnimation[0];
}

void Player::Draw(SDL_Renderer* renderer)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->RenderFrame(m_position.x, m_position.y, m_iWidth, m_iHeight, m_spriteRow, m_currentFrame, m_frameCount, m_numAction, m_angle, m_flip);
	}
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
		if (m_KeyPress & 1) {
			MoveDirection.x = -1;
		}
		else if (m_KeyPress & 4) {
			MoveDirection.x = 1;
		}
		else {
			MoveDirection.x = 0;
		}

		//MoveDirection.y = 1;

		Vector2 crtObjPosition = m_listAnimation[0]->Get2DPosition();
		//Vector2 crtFoodPosition = food->Get2DPosition();

		m_listAnimation[0]->Set2DPosition(crtObjPosition.x + MoveDirection.x * deltaTime * m_VelocityX, SCREEN_HEIDHT - m_listAnimation[0]->GetHeight());

		//food->Set2DPosition(crtFoodPosition.x, crtFoodPosition.y + MoveDirection.y * deltaTime * m_VelocityY);

		//character = { (int)crtObjPosition.x + 70, (int)crtObjPosition.y + 75, m_listAnimation[0]->GetWidth() - 110, m_listAnimation[0]->GetHeight() - 130 };
		//item = { (int)crtFoodPosition.x + 10, (int)crtFoodPosition.y + 20, food->GetWidth() - 20, food->GetHeight() - 35 };

		/*for (auto food : m_listFood) {
			food->Update(deltaTime);
			if (Collision::checkCollision(character, item)) {
				g_point += 1;
				SpawnFood();
			}
		}

		for (auto food : m_listFood) {
			food->Update(deltaTime);
			if (food->Get2DPosition().y > SCREEN_HEIDHT) {
				SpawnFood();
			}
		}

		std::string str = std::to_string(g_point);
		m_score->LoadFromRenderText(str);*/

		m_listAnimation[0]->Update(deltaTime);
}

void Player::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

void Player::Set2DPosition(float x, float y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
}

void Player::SetRotation(double angle)
{
	m_angle = angle;
}

void Player::SetFlip(SDL_RendererFlip flip)
{
	m_flip = flip;
}

Vector2 Player::Get2DPosition()
{
	//return Vector3(m_position.x, m_position.y, 0.0f);
	return Vector2(m_position.x, m_position.y);

}

int Player::GetWidth()
{
	return m_iWidth;
}

int Player::GetHeight()
{
	return m_iHeight;
}

int Player::GetPoint(int g_point)
{
	return g_point;
}