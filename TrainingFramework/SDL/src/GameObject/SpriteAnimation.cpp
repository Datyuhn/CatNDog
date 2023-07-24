#include "SpriteAnimation.h"
#include "GameObject/TextureManager.h"
#include <SDL_render.h>

SpriteAnimation::SpriteAnimation(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) 
	: BaseObject(texture)
{
	m_spriteRow = spriteRow;
	m_frameCount = frameCount;
	m_numAction = numAction;
	//m_animSpeed = animSpeed;
	m_frameTime = frameTime;
	//m_flip = flip;
	m_currentFrame = 0;
	m_currentTicks = 0;
	m_lastUpdate = SDL_GetTicks();
	Init();
}
SpriteAnimation::~SpriteAnimation()
{
}

void SpriteAnimation::Init()
{
}

void SpriteAnimation::Draw(SDL_Renderer* renderer)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->RenderFrame(m_position.x, m_position.y, m_iWidth, m_iHeight, m_spriteRow, m_currentFrame, m_frameCount, m_numAction, m_angle, m_flip);
	}
	SDL_Rect collider = { (int)m_position.x + 70, (int)m_position.y + 75, m_iWidth - 110, m_iHeight - 130 };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 150);
	SDL_RenderDrawRect(renderer, &collider);
}

void SpriteAnimation::Update(float deltatime)
{
	m_currentTicks += deltatime;
	if (m_currentTicks >= m_frameTime) {
		m_currentFrame++;
		if (m_currentFrame >= m_frameCount) {
			m_currentFrame = 0;
		}
		m_currentTicks -= m_frameTime;
	}
	m_lastUpdate = SDL_GetTicks();
	m_currentFrame = static_cast<int>((m_lastUpdate / static_cast<Uint32>(m_frameTime * 1000.0f)) % static_cast<Uint32>(m_frameCount));
	if (m_currentFrame == m_frameCount - 1) {
		SpriteAnimation::Change();
	}
}

bool SpriteAnimation::Change() {
	return true;
}


void SpriteAnimation::Set2DPosition(float x, float y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
}

void SpriteAnimation::SetRotation(double angle)
{
	m_angle = angle;
}

void SpriteAnimation::SetFlip(SDL_RendererFlip flip)
{ 
	m_flip = flip;
}

Vector2 SpriteAnimation::Get2DPosition()
{
	return Vector2(m_position.x, m_position.y);
}

void SpriteAnimation::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

int SpriteAnimation::GetWidth()
{
	return m_iWidth;
}

int SpriteAnimation::GetHeight()
{
	return m_iHeight;
}
