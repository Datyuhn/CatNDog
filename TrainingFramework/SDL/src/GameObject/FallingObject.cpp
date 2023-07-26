#include "FallingObject.h"
#include "TextureManager.h"
#include "ResourceManagers.h"
#include "Sprite2D.h"
#include "Define.h"

FallingObject::FallingObject(int f_speed, int foodID)
{
	m_iHeight = 60;
	m_iWidth = 60;
	m_speed = f_speed;
	m_foodID = foodID;
	Init();
}

FallingObject::~FallingObject() {}

void FallingObject::Init()
{
	std::string text = "Items/shadow_" + std::to_string(m_foodID) + ".png";
	auto texture = ResourceManagers::GetInstance()->GetTexture(text);
	food = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	food->SetSize(60, 60);
	food->Set2DPosition(rand() % SCREEN_WIDTH, -food->GetHeight());
	//m_listFood.push_back(food);
}

void FallingObject::Draw(SDL_Renderer* renderer)
{
	food->Draw(renderer);
	/*SDL_Rect collider = { (int)m_position.x + 10, (int)m_position.y + 20, m_iWidth - 20, m_iHeight - 35 };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 150);
	SDL_RenderDrawRect(renderer, &collider);*/
}

void FallingObject::Update(float deltatime)
{
	
	if (m_isActive) {
		Vector2 foodPos = food->Get2DPosition();
		foodPos.y += m_speed * deltatime;
		food->Set2DPosition(foodPos.x, foodPos.y);
		food->Update(deltatime);
	}
	else {
		food->Set2DPosition(SCREEN_WIDTH + 10, SCREEN_HEIDHT + 10);
		food->Update(deltatime);
	}
	/*for (auto food : m_listFood) {
		food->Update(deltatime);
	}*/
}

void FallingObject::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
}

void FallingObject::Spawn(int ramdom_x, int ramdom_y)
{
	int randomX = rand() % ramdom_x;
	int randomY = ramdom_y;
	this->Set2DPosition(randomX, randomY);
}

void FallingObject::SetActive(bool active) {
	m_isActive = active;
}

bool FallingObject::IsActive() {
	return m_isActive;
}

int FallingObject::GetFoodID() {
	return m_foodID;
}
int FallingObject::GetFallingSpeed(int m_foodID) {
	switch (m_foodID) {
	case 0:
		return 250;
		break;
	case 1:
		return 350;
		break;
	case 2:
		return 450;
		break;
	default:
		break;
	}
}

void FallingObject::Set2DPosition(float x, float y)
{
	m_foodPos = Vector2((float)x, (float)y);
}

Vector2 FallingObject::Get2DPosition()
{
	return food->Get2DPosition();
}

int FallingObject::GetWidth()
{
	return food->GetWidth();
}

int FallingObject::GetHeight()
{
	return food->GetHeight();
}

