#pragma once
#include"BaseObject.h"

class Items : public BaseObject
{
protected:
	int m_iWidth;
	int m_iHeight;
	SDL_RendererFlip m_flip;

public:
	Items() : BaseObject(), m_iWidth(0), m_iHeight(0) {}
	Items(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip);
	void	Init() override;
	void	Draw(SDL_Renderer* renderer) override;
	void	Update(float deltatime) override;
	//void	Spawn(int ram_x, int ram_y);

	void	Set2DPosition(float x, float y);
	Vector2	Get2DPosition();
	void	SetSize(int width, int height);
	int		GetWidth();
	int		GetHeight();
	void	SetRotation(double angle);
	void	SetFlip(SDL_RendererFlip flip);
};