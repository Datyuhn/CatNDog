#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "GameObject/FallingObject.h"
#include "GameObject/Items.h"
#include "GameObject/Collision.h"

GSPlay::GSPlay() {}
GSPlay::~GSPlay() {}


void GSPlay::Init()
{
	// auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bgr_09_p1.jpg");

	// background
	m_background = std::make_shared<Sprite2D>( texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	texture = ResourceManagers::GetInstance()->GetTexture("floor.png");
	floor = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	floor->SetSize(SCREEN_WIDTH, 150);
	floor->Set2DPosition(-5, SCREEN_HEIDHT - floor->GetHeight() + 60);

	m_score = std::make_shared<Text>("Data/BADABB__.TTF", m_scoreColor);
	m_score->SetSize(40, 40);
	m_score->Set2DPosition(30, 30);
	// how to play button
	/*
	texture = ResourceManagers::GetInstance()->GetTexture("mBtn_yel.png");
	std::shared_ptr<MouseButton> btnGuide = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);

	btnGuide->SetSize(317, 90);
	btnGuide->Set2DPosition((SCREEN_WIDTH - btnGuide->GetWidth()) / 2, (SCREEN_HEIDHT - btnGuide->GetHeight()) / 2 + 70);
	btnGuide->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_GUIDE);
		});
	m_listButton.push_back(btnGuide);
	*/

	// main menu button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_menu.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);

	button->SetSize(80, 80);
	button->Set2DPosition((SCREEN_WIDTH - button->GetWidth()) / 2 + 120, (SCREEN_HEIDHT - button->GetHeight()) / 2);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	m_listButton.push_back(button);

	// restart button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);

	button->SetSize(80, 80);
	button->Set2DPosition((SCREEN_WIDTH - button->GetWidth()) / 2 - 0, (SCREEN_HEIDHT - button->GetHeight()) / 2);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button);

	// button resume
	texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	button = std::make_shared<MouseButton>( texture, SDL_FLIP_NONE);
	button->SetSize(80, 80);
	button->Set2DPosition((SCREEN_WIDTH - button->GetWidth()) / 2 - 120, (SCREEN_HEIDHT - button->GetHeight()) / 2);
	button->SetOnClick([this]() {
		isPaused = false;
	});
	m_listButton.push_back(button);

	// Pause frame
	auto b_pause = ResourceManagers::GetInstance()->GetTexture("mBtn_yel.png");
	frm = std::make_shared<Sprite2D>(b_pause, SDL_FLIP_NONE);
	frm->SetSize(588, 170);
	frm->Set2DPosition((SCREEN_WIDTH - frm->GetWidth()) / 2, (SCREEN_HEIDHT - frm->GetHeight()) / 2);

	// Button pause
	texture = ResourceManagers::GetInstance()->GetTexture("btn_pause.tga");
	btnPause = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnPause->SetSize(80, 80);
	btnPause->Set2DPosition(SCREEN_WIDTH - 90, 10);
	btnPause->SetOnClick([this]() {
		isPaused = true;
	});

    // Normal animation
	texture = ResourceManagers::GetInstance()->GetTexture("normal19.png");
	obj = std::make_shared<SpriteAnimation>( texture, 1, 19, 1, 0.04f);
	obj->SetFlip(SDL_FLIP_HORIZONTAL);
	obj->SetSize(150, 144);
	obj->Set2DPosition(SCREEN_WIDTH/2-60, SCREEN_HEIDHT - obj->GetHeight());
	m_listAnimation.push_back(obj);

	// Eat animation
	texture = ResourceManagers::GetInstance()->GetTexture("eating21.png");
	obj = std::make_shared<SpriteAnimation>(texture, 1, 21, 1, 0.03f);
	obj->SetFlip(SDL_FLIP_HORIZONTAL);
	obj->SetSize(150, 144);
	obj->Set2DPosition(SCREEN_WIDTH / 2 - 60, SCREEN_HEIDHT - obj->GetHeight());
	m_listAnimation.push_back(obj);

	// Foods
	texture = ResourceManagers::GetInstance()->GetTexture("Items/Piece-of-cake_shadow.png");
	food = std::make_shared<FallingObject>(texture, SDL_FLIP_NONE);
	food->SetSize(60, 60);
	food->Set2DPosition(260, food->GetHeight() * -1);
	m_listFood.push_back(food);

	obj = m_listAnimation[0];
	m_KeyPress = 0;

	for (int i = 0; i < 10; i++) {
		SpawnFood();
	}
	g_point = 0;
}

void GSPlay::SpawnFood()
{
	food->Spawn(SCREEN_WIDTH - food->GetWidth(), -food->GetHeight());
	// m_listFood.push_back(food);
}

void GSPlay::Exit()
{
	
}

void GSPlay::Pause()
{

}

void GSPlay::Resume()
{
	
}

void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) //For e.key.repeat it's because key repeat is enabled by default and if you press and hold a key it will report multiple key presses. That means we have to check if the key press is the first one because we only care when the key was first pressed.
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			m_KeyPress |= 1 << 3;
			break;
		case SDLK_DOWN:
			m_KeyPress |= 1 << 1;
			break;
		case SDLK_LEFT:
			m_KeyPress |= 1;
			break;
		case SDLK_RIGHT:
			m_KeyPress |= 1 << 2;
			break;
		default:
			break;
		}
	}
	////Key Up
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_KeyPress ^= 1;
			break;
		case SDLK_DOWN:
			m_KeyPress ^= 1 << 1;
			break;
		case SDLK_RIGHT:
			m_KeyPress ^= 1 << 2;
			break;
		case SDLK_UP:
			m_KeyPress ^= 1 << 3;
			break;
		default:
			break;
		}
	}
}

void GSPlay::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
	btnPause->HandleTouchEvent(&e);
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	if (!isPaused) {
		if (m_KeyPress & 1) {
			MoveDirection.x = -1;
		}
		else if (m_KeyPress & 4) {
			MoveDirection.x = 1;
		}
		else {
			MoveDirection.x = 0;
		}

		MoveDirection.y = 1;

		Vector2 crtObjPosition = obj->Get2DPosition();
		Vector2 crtFoodPosition = food->Get2DPosition();

		obj->Set2DPosition(crtObjPosition.x + MoveDirection.x * deltaTime * m_VelocityX, SCREEN_HEIDHT - obj->GetHeight());

		food->Set2DPosition(crtFoodPosition.x, crtFoodPosition.y + MoveDirection.y * deltaTime * m_VelocityY);

		character = { (int)crtObjPosition.x+70, (int)crtObjPosition.y+75, obj->GetWidth()-110, obj->GetHeight()-130 };
		item = { (int)crtFoodPosition.x+10, (int)crtFoodPosition.y+20, food->GetWidth()-20, food->GetHeight()-35 };
		

		for (auto food : m_listFood) {
			food->Update(deltaTime);
			if (Collision::checkCollision(character, item)) {
				g_point += 1;
				SpawnFood();
				obj = m_listAnimation[1];
			}
		}
		if (SpriteAnimation::Change()) {
			obj = m_listAnimation[0];
		}
		for (auto food : m_listFood) {
			food->Update(deltaTime);	
			if (food->Get2DPosition().y > SCREEN_HEIDHT) {
			SpawnFood();
			}
		}
		//for (auto obj : m_listAnimation) {
		obj->Update(deltaTime);
		//}
		std::string str = std::to_string(g_point);
		m_score->LoadFromRenderText(str);
		//food->Update(deltaTime);
	}
	else {
		//
	}
	//Update position of camera
	//Camera::GetInstance()->Update(deltaTime);
	//obj->Update(deltaTime);
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	floor->Draw(renderer);
	/*for (auto it : m_listAnimation)
	{
		it->Draw(renderer);
	}*/
	obj->Draw(renderer);
	for (auto food : m_listFood) {
		food->Draw(renderer);
	}
	m_score->Draw(renderer);
	if (isPaused)
	{
		SDL_Rect rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIDHT };
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_MUL);
		SDL_RenderFillRect(renderer, &rect);

		frm->Draw(renderer);
		for (auto it : m_listButton)
		{
			it->Draw(renderer);
		}
	} else btnPause->Draw(renderer);
}