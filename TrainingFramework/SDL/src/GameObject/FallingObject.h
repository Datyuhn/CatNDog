#pragma once
#include "BaseObject.h"
#include "SDL_render.h"
#include <vector>

class Sprite2D;
class TextureManager;

class FallingObject
{
protected:
	int m_iWidth;
	int m_iHeight;
	int	m_speed;
	int m_playerId;
	int m_foodID;
	bool m_isActive;
	Vector2 m_foodPos;

	std::shared_ptr<Sprite2D>				food;
	std::vector<std::shared_ptr<Sprite2D>>	m_listFood;
	std::vector<std::shared_ptr<Sprite2D>>	arr;

	//float   velocityY;

public:
	FallingObject() {};
	FallingObject(int f_speed, int foodID);
	~FallingObject();

	void Init();
	void Draw(SDL_Renderer* renderer);
	void Update(float deltatime);

	void Spawn(int ramdom_x, int ramdom_y);
	void SetActive(bool active);
	bool IsActive();
	int GetFoodID();
	int GetFallingSpeed(int m_foodID);

	void SetSize(int width, int height);
	void Set2DPosition(float x, float y);
	Vector2	Get2DPosition();
	int		GetWidth();
	int		GetHeight();
};