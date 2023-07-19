#pragma once
#include "BaseObject.h"
#include "SDL_render.h"

class FallingObject : public BaseObject
{
protected:
	//Vector2 m_Vec2DPos;
	int     m_iWidth;
	int     m_iHeight;
	SDL_RendererFlip m_flip;
	//float   velocityY;

public:
	FallingObject() : BaseObject(), m_iWidth(0), m_iHeight(0) {}
	FallingObject(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip);
	~FallingObject();

	void Init() override;
	void Draw(SDL_Renderer* renderer) override;
	void Update(float deltatime) override;

	void Spawn(int ramdom_x, int ramdom_y);
	void SetSize(int width, int height);
	void Set2DPosition(float x, float y);

	void SetRotation(double angle);
	void SetFlip(SDL_RendererFlip flip);
	void SetVelocityY(float velocity);

	Vector2	Get2DPosition();
	int		GetWidth();
	int		GetHeight();
};