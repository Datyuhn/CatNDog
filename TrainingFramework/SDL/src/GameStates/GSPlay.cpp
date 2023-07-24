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

		// score
		m_score1 = std::make_shared<Text>("Data/BADABB__.TTF", m_scoreColor);
		m_score1->SetSize(40, 40);
		m_score1->Set2DPosition(30, 30);
		m_listScore.push_back(m_score1);

		m_score2 = std::make_shared<Text>("Data/BADABB__.TTF", m_scoreColor);
		m_score2->SetSize(40, 40);
		m_score2->Set2DPosition(SCREEN_WIDTH / 2 + 30, 30);
		m_listScore.push_back(m_score2);


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
	p1 = std::make_shared<Player>(1);
	p1->SetControl({ SDL_SCANCODE_A, SDL_SCANCODE_D });
	m_listCharacter.push_back(p1);

	// Character 2
	texture = ResourceManagers::GetInstance()->GetTexture("normal19_2.png");
	p2 = std::make_shared<Player>(2);
	p2->SetControl({ SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT });
	m_listCharacter.push_back(p2);

	// Foods
	texture = ResourceManagers::GetInstance()->GetTexture("Items/Piece-of-cake_shadow.png");
	food = std::make_shared<FallingObject>(texture, SDL_FLIP_NONE);
	food->SetSize(60, 60);
	food->Set2DPosition(260, food->GetHeight() * -1);
	m_listFood.push_back(food);

	m_KeyPress = 0;
	g_point1 = 0;
	g_point2 = 0;
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
	Vector2 crtPos1 = p1->Get2DPosition();
	Vector2 crtPos2 = p2->Get2DPosition();

	food->Set2DPosition(crtFoodPosition.x, crtFoodPosition.y + MoveDirection.y * deltaTime * m_VelocityY);

	p_char1 = { (int)crtPos1.x + 70, (int)crtPos1.y + 75, p1->GetWidth() - 110, p1->GetHeight() - 130 };
	p_char2 = { (int)crtPos2.x + 70, (int)crtPos1.y + 75, p2->GetWidth() - 110, p2->GetHeight() - 130 };
	item = { (int)crtFoodPosition.x + 10, (int)crtFoodPosition.y + 20, food->GetWidth() - 20, food->GetHeight() - 35 };

	if (!isPaused) {
		for (auto food : m_listFood) {
			food->Update(deltaTime);
			if (Collision::checkCollision(p_char1, item)) {
				g_point1++;
				SpawnFood();
			}
			if (Collision::checkCollision(p_char2, item)) {
				g_point2++;
				SpawnFood();
			}
		}
		for (auto food : m_listFood) {
			food->Update(deltaTime);
			if (food->Get2DPosition().y > SCREEN_HEIDHT) {
				SpawnFood();
			}
		}
		
		std::string str1 = std::to_string(g_point1);
		m_score1->LoadFromRenderText(str1);

		std::string str2 = std::to_string(g_point2);
		m_score2->LoadFromRenderText(str2);

		for (auto it : m_listScore) {
			it->Update(deltaTime);
		}
		p1->Update(deltaTime);
		p2->Update(deltaTime);
	}
	else {

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
	for (auto it : m_listScore)
	{
		it->Draw(renderer);
	}
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
	}
	else btnPause->Draw(renderer);
}