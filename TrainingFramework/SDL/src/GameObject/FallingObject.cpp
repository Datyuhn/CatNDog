#include "FallingObject.h"
#include "TextureManager.h"

FallingObject::FallingObject(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip)
	:BaseObject(texture), m_iWidth(100), m_iHeight(50)
{
	m_flip = flip;
	Init();
}

FallingObject::~FallingObject() {}

void FallingObject::Init() {}

void FallingObject::Draw(SDL_Renderer* renderer)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Render(m_position.x, m_position.y, m_iWidth, m_iHeight, m_angle, m_flip);
	}
	SDL_Rect collider = { (int)m_position.x + 10, (int)m_position.y + 20, m_iWidth - 20, m_iHeight - 35 };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 150);
	SDL_RenderDrawRect(renderer, &collider);
}

void FallingObject::Update(float deltatime) {}

void FallingObject::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

void FallingObject::Spawn(int ramdom_x, int ramdom_y)
{
	int randomX = rand() % ramdom_x;
	int randomY = ramdom_y;
	this->Set2DPosition(randomX, randomY);
}

void FallingObject::Set2DPosition(float x, float y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
}

Vector2 FallingObject::Get2DPosition()
{
	return Vector2(m_position.x, m_position.y);

}

void FallingObject::SetRotation(double angle)
{
}

void FallingObject::SetFlip(SDL_RendererFlip flip)
{
}

void FallingObject::SetVelocityY(float velocity)
{
}


int FallingObject::GetWidth()
{
	return m_iWidth;
}

int FallingObject::GetHeight()
{
	return m_iHeight;
}

