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

}

void FallingObject::Update(float deltatime) {}

