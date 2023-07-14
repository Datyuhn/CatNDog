#include "SpriteAnimation.h"
#include "TextureManager.h"

// static bool reverseAnimation=1;

SpriteAnimation::SpriteAnimation(std::shared_ptr<TextureManager> texture, int spriteColumn, int frameCount, int numAction, float frameTime) : BaseObject(texture)
{
	m_spriteColumn = spriteColumn;
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
		m_pTexture->RenderFrame(m_position.x, m_position.y, m_iWidth, m_iHeight, m_spriteColumn, m_currentFrame, m_frameCount, m_numAction, m_angle, m_flip);
	}
}

// Loop animation
//void SpriteAnimation::Update(float deltatime)
//{
//	m_currentTicks += deltatime;
//		if(m_currentTicks  >= m_frameTime) {
//			if (reverseAnimation == 1) m_currentFrame++;
//			else m_currentFrame--;
//		if (m_currentFrame >= m_frameCount) {
//			//m_currentFrame = 0;
//			reverseAnimation = 0;
//		}
//		if (m_currentFrame <= 0) reverseAnimation = 1;
//		m_currentTicks -= m_frameTime;
//	}
//}

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

//void SpriteAnimation::MoveLeft(float deltaTime)
//{
//	m_position.x -= 30 * deltaTime;
//}
//void SpriteAnimation::MoveRight(float deltaTime)
//{
//	m_position.x += 30 * deltaTime;
//}
//void SpriteAnimation::Jump(float deltaTime)
//{}
//void SpriteAnimation::Crouch(float deltaTime)
//{}
