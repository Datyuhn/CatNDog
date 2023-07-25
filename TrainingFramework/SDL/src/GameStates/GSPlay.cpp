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
#include "GameObject/Timer.h"

GSPlay::GSPlay() {}
GSPlay::~GSPlay() {}


void GSPlay::Init()
{
	// auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bgcandy.jpg");

	// background
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// wall
	texture = ResourceManagers::GetInstance()->GetTexture("wall.png");
	wall = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	wall->SetSize(40, SCREEN_HEIDHT * 5/6);
	wall->Set2DPosition((SCREEN_WIDTH - wall->GetWidth()) / 2 + 16, 70);

	// floor
	texture = ResourceManagers::GetInstance()->GetTexture("floor.png");
	floor = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	floor->SetSize(SCREEN_WIDTH, 150);
	floor->Set2DPosition(-5, SCREEN_HEIDHT - floor->GetHeight() + 60);

	// score
	m_score1 = std::make_shared<Text>("Data/BADABB__.TTF", m_scoreColor);
	m_score1->SetSize(150, 40);
	m_score1->Set2DPosition((SCREEN_WIDTH - m_score1->GetWidth() / 4) / 4, 30);
	m_listScore.push_back(m_score1);

	m_score2 = std::make_shared<Text>("Data/BADABB__.TTF", m_scoreColor);
	m_score2->SetSize(150, 40);
	m_score2->Set2DPosition((SCREEN_WIDTH - m_score1->GetWidth() / 4) * 3 / 4, 30);
	m_listScore.push_back(m_score2);

	///Button
	{
		// resume button
		texture = ResourceManagers::GetInstance()->GetTexture("x.png");
		button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
		button->SetSize(352 / 5, 372 / 5);
		button->Set2DPosition((SCREEN_WIDTH - button->GetWidth()) / 2, (SCREEN_HEIDHT - button->GetHeight()) / 2 + 150);
		button->SetOnClick([this]() {
			isPaused = false;
			});
		m_listButton.push_back(button);

		// restart button
		texture = ResourceManagers::GetInstance()->GetTexture("restart.png");
		button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);

		button->SetSize(120, 120);
		button->Set2DPosition((SCREEN_WIDTH - button->GetWidth()) / 2 - 192, (SCREEN_HEIDHT - button->GetHeight()) / 2);
		button->SetOnClick([]() {
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
			});
		m_listButton.push_back(button);

		// main menu button
		texture = ResourceManagers::GetInstance()->GetTexture("home.png"); 
		button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE); 

		button->SetSize(120, 120); 
		button->Set2DPosition((SCREEN_WIDTH - button->GetWidth()) / 2 - 64, (SCREEN_HEIDHT - button->GetHeight()) / 2);
		button->SetOnClick([]() { 
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU); 
			}); 
		m_listButton.push_back(button); 

		// Music sound button
		texture = ResourceManagers::GetInstance()->GetTexture("turnonvolume.png");
		button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);

		button->SetSize(120, 120); 
		button->Set2DPosition((SCREEN_WIDTH - button->GetWidth()) / 2 + 64, (SCREEN_HEIDHT - button->GetHeight()) / 2);
		button->SetOnClick([]() {
			//Turn on sound
			});
		m_listButton.push_back(button);

		// Music sound button
		texture = ResourceManagers::GetInstance()->GetTexture("turnoffvolume.png");
		button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE); 

		button->SetSize(120, 120); 
		button->Set2DPosition((SCREEN_WIDTH - button->GetWidth()) / 2 + 192, (SCREEN_HEIDHT - button->GetHeight()) / 2);
		button->SetOnClick([]() {
			//Turn off sound
			});
		m_listButton.push_back(button);

		// Pause frame
		auto b_pause = ResourceManagers::GetInstance()->GetTexture("pause_frame.png");
		frm = std::make_shared<Sprite2D>(b_pause, SDL_FLIP_NONE);
		frm->SetSize(694, 516);
		frm->Set2DPosition((SCREEN_WIDTH - frm->GetWidth()) / 2, (SCREEN_HEIDHT - frm->GetHeight()) / 2);

		// pause button
		texture = ResourceManagers::GetInstance()->GetTexture("setting.png");
		btnPause = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
		btnPause->SetSize(100, 100);
		btnPause->Set2DPosition(SCREEN_WIDTH - 110, 10);
		btnPause->SetOnClick([this]() {
			isPaused = true;
			});
	}

	// Character 1
	texture = ResourceManagers::GetInstance()->GetTexture("normal19_1.png");
	p1 = std::make_shared<Player>(1, -30, (SCREEN_WIDTH - wall->GetWidth())/2 - 125);
	p1->SetControl({ SDL_SCANCODE_A, SDL_SCANCODE_D });
	m_listCharacter.push_back(p1);

	// Character 2
	texture = ResourceManagers::GetInstance()->GetTexture("normal19_2.png");
	p2 = std::make_shared<Player>(2, (SCREEN_WIDTH + wall->GetWidth())/2 - 25, SCREEN_WIDTH - 150);
	p2->SetControl({ SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT });
	m_listCharacter.push_back(p2);

	// Foods
	//texture = ResourceManagers::GetInstance()->GetTexture("Items/shadow_0.png");
	food = std::make_shared<FallingObject>(200, 0);
	food->SetActive(true);
	m_listFood.push_back(food);

	//texture = ResourceManagers::GetInstance()->GetTexture("Items/shadow_1.png");
	//food = std::make_shared<FallingObject>(400, 1);
	//m_listFood.push_back(food);

	m_KeyPress = 0;
	g_point1 = 0;
	g_point2 = 0;

	if (!g_timer.IsStarted()) {
		g_timer.Start();
	}
	g_timer.SetDuration(3000);
	food_timer.SetDuration(1400);
	food_timer.Start();
}

void GSPlay::SpawnFood()
{
	int index = rand() % 3;
	int f_speed = food->GetFallingSpeed(index);
	food = std::make_shared<FallingObject>(f_speed, index);

	food->SetActive(true);
	m_listFood.push_back(food);
	food->Spawn(SCREEN_WIDTH - food->GetWidth() - 10, food->GetHeight());
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
	Vector2 crtFoodPosition = food->Get2DPosition();
	Vector2 crtPos1 = p1->Get2DPosition();
	Vector2 crtPos2 = p2->Get2DPosition();

	p_char1 = { (int)crtPos1.x + 70, (int)crtPos1.y + 75, p1->GetWidth() - 110, p1->GetHeight() - 130 };
	p_char2 = { (int)crtPos2.x + 70, (int)crtPos1.y + 75, p2->GetWidth() - 110, p2->GetHeight() - 130 };
	item    = { (int)crtFoodPosition.x + 20, (int)crtFoodPosition.y + 30, food->GetWidth() - 20, food->GetHeight() - 35 };

	/*Uint32 countTime = g_timer.GetTicks();
	if (countTime >= g_timer.GetDuration()) 
	{ 
		t_duration.SetDuration(120000);
	 	inTime = true;
	 	t_duration.Start();
	}*/	

	if (!isPaused) {
		if (food->IsActive() && Collision::checkCollision(p_char1, item)) {
			g_point1++;
			food->SetActive(false);
		}
		if (food->IsActive() && Collision::checkCollision(p_char2, item)) {
			g_point2++;
			food->SetActive(false);
		}
		
		
		food->Update(deltaTime);
		if (food_timer.GetTicks() >= food_timer.GetDuration()) {
			SpawnFood();
			food_timer.Start();
		}
		

		std::string str1 = "Score:" + std::to_string(g_point1);
		m_score1->LoadFromRenderText(str1);
		std::string str2 = "Score:" + std::to_string(g_point2);
		m_score2->LoadFromRenderText(str2);

		if (t_duration.GetTicks() >= t_duration.GetDuration())
		{
			isPaused = true;
		}
		
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
	wall->Draw(renderer);
	floor->Draw(renderer);

	for (auto it : m_listCharacter)
	{
		it->Draw(renderer);
	}

	for (auto food : m_listFood) {
		if (food->IsActive())
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