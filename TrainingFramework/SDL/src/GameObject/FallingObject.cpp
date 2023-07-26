#include "FallingObject.h"
#include "TextureManager.h"
#include "ResourceManagers.h"
#include "Sprite2D.h"
#include "Define.h"

FallingObject::FallingObject(int f_speed, int foodID, int playerID)
{
	m_iHeight = 60;
	m_iWidth = 60;
	m_speed = f_speed;
	m_foodID = foodID;
	m_playerId = playerID;
	Init();
}

FallingObject::~FallingObject() {}

void FallingObject::Init()
{
	std::string text = "Items/shadow_" + std::to_string(m_foodID) + ".png";
	auto texture = ResourceManagers::GetInstance()->GetTexture(text);
	food = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	food->SetSize(60, 60);
	int start, end;
	if (m_playerId == 1) {
		start = 5;
		end = (SCREEN_WIDTH - food->GetWidth()) / 2 - 20;
	}
	else {
		start = (SCREEN_WIDTH + food->GetWidth()) / 2;
		end = SCREEN_WIDTH - food->GetWidth();
	}
	int range = start + (int)(rand() * (end - start + 1.0) / (1.0 + RAND_MAX));
	food->Set2DPosition(range, -food->GetHeight() - 50);

	//m_listFood.push_back(food);
}

void FallingObject::Draw(SDL_Renderer* renderer)
{
	food->Draw(renderer);
	/*SDL_Rect collider = { (int)m_foodPos.x + 10, (int)m_foodPos.y + 20, m_iWidth - 20, m_iHeight - 35 };
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
		//food->Update(deltatime);
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

void FallingObject::Spawn(int start, int end, int ramdom_y)
{
	int randomX = start + (int)(rand() * (end - start + 1.0) / (1.0 + RAND_MAX));
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
	case 5:
	case 13:
	case 15:
	case 16:
	case 21:
	case 24:
	case 27:
	case 28:
	case 9:
		return 275;
		break;
	case 1:
	case 6:
	case 10:
	case 17:
	case 23:
	case 4:
	case 26:
		return 350;
		break;
	case 2:
	case 7:
	case 11:
	case 18:
	case 22:
		return 425;
		break;
	case 25:
	case 29:
	case 14:
		return 550;
		break;
	case 3:
	case 8:
	case 12:
	case 19:
	case 20:
		return 250;
		break;
	default:
		break;
	}
}
int FallingObject::GetPoint(int m_foodID) 
{
	switch (m_foodID) {
	case 0:
	case 5:
	case 13:
	case 15:
	case 16:
	case 21:
	case 24:
	case 27:
	case 28:
	case 9:
		return 3;
		break;
	case 1:
	case 6:
	case 10:
	case 17:
	case 23:
	case 4:
	case 26:
		return 5;
		break;
	case 2:
	case 7:
	case 11:
	case 18:
	case 22:
		return 10;
		break;
	case 25:
	case 29:
	case 14:
		return 20;
		break;
	case 3:
	case 8:
	case 12:
	case 19:
	case 20:
		return -10;
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

