#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "GameObject/FallingObject.h"
#include "GameObject/Items.h"
#include "GameObject/Collision.h"
#include "GameObject/Player.h"

GSPlay::GSPlay() {}
GSPlay::~GSPlay() {}


void GSPlay::Init()
{
	// auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bgr_09_p1.jpg");
	
	/// Buttons
	{
		// background
		m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
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

		// resume button
		texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
		button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
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

		// pause button
		texture = ResourceManagers::GetInstance()->GetTexture("btn_pause.tga");
		btnPause = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
		btnPause->SetSize(80, 80);
		btnPause->Set2DPosition(SCREEN_WIDTH - 90, 10);
		btnPause->SetOnClick([this]() {
			isPaused = true;
			});
	}
    // Character 1
	texture = ResourceManagers::GetInstance()->GetTexture("normal19_1.png");
	p1 = std::make_shared<Player>(1, texture, 1, 19, 1, 0.04f);
	p1->SetFlip(SDL_FLIP_HORIZONTAL);
	p1->SetSize(150, 144);
	p1->Set2DPosition((SCREEN_WIDTH - p1->GetWidth()/2) / 4, SCREEN_HEIDHT - p1->GetHeight() - 20);
	p1->SetControl({ SDL_SCANCODE_A, SDL_SCANCODE_D });
	m_listCharacter.push_back(p1);

	// Character 2
	texture = ResourceManagers::GetInstance()->GetTexture("normal19_2.png");
	p2 = std::make_shared<Player>(texture, 1, 19, 1, 0.04f);
	p2->SetFlip(SDL_FLIP_HORIZONTAL);
	p2->SetSize(150, 144);
	p2->Set2DPosition((SCREEN_WIDTH - p2->GetWidth() / 2) * 3/4, SCREEN_HEIDHT - p2->GetHeight() - 20);
	p1->SetControl({ SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT });
	m_listCharacter.push_back(p2);

	// Foods
	texture = ResourceManagers::GetInstance()->GetTexture("Items/Piece-of-cake_shadow.png");
	food = std::make_shared<FallingObject>(texture, SDL_FLIP_NONE);
	food->SetSize(60, 60);
	food->Set2DPosition(260, food->GetHeight() * -1);
	m_listFood.push_back(food);

	//obj = m_listAnimation[0];
	m_KeyPress = 0;

	/*for (int i = 0; i < 10; i++) {
		SpawnFood();
	}*/
	g_point_1 = 0;
	g_point_2 = 0;
}

void GSPlay::SpawnFood()
{
	food->Spawn(SCREEN_WIDTH - food->GetWidth(), -food->GetHeight());
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
	p1->HandleKeyEvents(e);
	p2->HandleKeyEvents(e);
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
	MoveDirection.y = 1;

	
	Vector2 crtFoodPosition = food->Get2DPosition();
	food->Set2DPosition(crtFoodPosition.x, crtFoodPosition.y + MoveDirection.y * deltaTime * m_VelocityY);

	if (!isPaused) {
		p1->Update(deltaTime);
		p2->Update(deltaTime);
	}

	//Update position of camera
	//Camera::GetInstance()->Update(deltaTime);
	//obj->Update(deltaTime);
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	floor->Draw(renderer);

	for (auto it : m_listCharacter)
	{
		it->Draw(renderer);
	}

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