#include "Items.h"
#include "TextureManager.h"

Items::Items(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip)
	:BaseObject(texture), m_iWidth(100), m_iHeight(50)
{
	m_flip = flip;
	Init();

}

void Items::Init()
{

}

void Items::Draw(SDL_Renderer* renderer)
{
	
}

void Items::Update(float deltatime)
{

}

//void Items::Spawn(int ram_x, int ram_y)
//{
//	int randomX = rand() % ram_x;
//	int randomY = ram_y;
//	this->Set2DPosition(randomX, randomY);
//}

void Items::Set2DPosition(float x, float y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
}

Vector2 Items::Get2DPosition()
{
	return Vector2(m_position.x, m_position.y);

}

void Items::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

int Items::GetWidth()
{
	return m_iWidth;
}

int Items::GetHeight()
{
	return m_iHeight;
}

void Items::SetRotation(double angle)
{
	m_angle = angle;
}

void Items::SetFlip(SDL_RendererFlip flip)
{
	m_flip = flip;
}

