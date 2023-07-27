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
#include "GameObject/Sound.h"

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

	// Time
	m_time = std::make_shared<Text>("Data/BADABB__.TTF", m_scoreColor);
	m_time->SetSize(60, 40);
	m_time->Set2DPosition((SCREEN_WIDTH - m_time->GetWidth()) / 2, 30);
	m_listScore.push_back(m_time);

	m_Sound = std::make_shared<Sound>("Data/Sounds/Roaches_Theme.mp3");
	m_posSound = std::make_shared<Sound>("Data/Sounds/ding-sound-effect_2.mp3");
	m_negSound = std::make_shared<Sound>("Data/Sounds/roblox-death-sound-effect.mp3");
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
		button->SetOnClick([=]() {
			m_posSound->isPlay = true;
			m_negSound->isPlay = true;
			m_Sound->PlaySound();
			});
		m_listButton.push_back(button);

		// Music sound button
		texture = ResourceManagers::GetInstance()->GetTexture("turnoffvolume.png");
		button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE); 

		button->SetSize(120, 120); 
		button->Set2DPosition((SCREEN_WIDTH - button->GetWidth()) / 2 + 192, (SCREEN_HEIDHT - button->GetHeight()) / 2);
		button->SetOnClick([=]() {
			m_posSound->isPlay = false;
			m_negSound->isPlay = false;
			m_Sound->StopSound();
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
	food1 = std::make_shared<FallingObject>(200, 0, 1);
	food1->SetActive(true);
	m_listFood.push_back(food1);

	food2 = std::make_shared<FallingObject>(200, 0, 2);
	food2->SetActive(true);
	m_listFood.push_back(food2);

	m_KeyPress = 0;
	g_point1 = 0;
	g_point2 = 0;

	if (!g_timer.IsStarted()) {
		g_timer.Start();
	}
	g_timer.SetDuration(800);
	food_timer.SetDuration(600);
	t_duration.SetDuration(91700);

	food_timer.Start();
	t_duration.Start();
	inTime = false;

	m_Sound->PlaySound();
}

void GSPlay::SpawnFood()
{
	int index1 = rand() % 30;
	int f_speed = food1->GetFallingSpeed(index1);
	food1 = std::make_shared<FallingObject>(f_speed, index1, 1);

	food1->SetActive(true);
	m_listFood.push_back(food1);
	food1->Spawn(5, (SCREEN_WIDTH - food1->GetWidth()) / 2 - 30, -food1->GetHeight() - 50);

	int index2 = rand() % 30;
	f_speed = food2->GetFallingSpeed(index2);
	food2 = std::make_shared<FallingObject>(f_speed, index2, 2);

	food2->SetActive(true);
	m_listFood.push_back(food2);
	food2->Spawn((SCREEN_WIDTH + food2->GetWidth()) / 2 + 10, SCREEN_WIDTH - food2->GetWidth(), -food2->GetHeight() - 50);
}

void GSPlay::Exit()
{

}

void GSPlay::Pause()
{
	m_Sound->StopSound();

}

void GSPlay::Resume()
{
	m_Sound->PlaySound();
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
void Stop() {}

void GSPlay::Update(float deltaTime)
{
	Vector2 crtPos1 = p1->Get2DPosition();
	Vector2 crtPos2 = p2->Get2DPosition();

	p_near1 = { (int)crtPos1.x + 40, (int)crtPos1.y + 5, p1->GetWidth() - 50, p1->GetHeight() - 60 };
	p_near2 = { (int)crtPos2.x + 40, (int)crtPos2.y + 5, p2->GetWidth() - 50, p2->GetHeight() - 60 };

	p_char1 = { (int)crtPos1.x + 50, (int)crtPos1.y + 80, p1->GetWidth() - 70, p1->GetHeight() - 120 };
	p_char2 = { (int)crtPos2.x + 50, (int)crtPos1.y + 80, p2->GetWidth() - 70, p2->GetHeight() - 120 };

	Uint32 countdown = g_timer.GetTicks();
	/*if (countdown >= g_timer.GetDuration())
	{
		Stop();
	}*/

	if (!isPaused)
	{
		if (countdown >= g_timer.GetDuration())
		{
			inTime = true;
			//temp = t_duration.GetDuration();
		}
		if (inTime) {
			for (auto it : m_listFood) {
				it->Update(deltaTime);
			}
			for (auto food : m_listFood)
			{
				Vector2 crtFoodPosition = food->Get2DPosition();
				item = { (int)crtFoodPosition.x + 20, (int)crtFoodPosition.y + 30, food->GetWidth() - 20, food->GetHeight() - 35 };

				if (Collision::checkCollision(p_near1, item)) p1->ChangeAnimation();
				if (food->IsActive() && Collision::checkCollision(p_char1, item)) {
					if (g_point1 + food->GetPoint(food->GetFoodID()) < 0) g_point1 = 0;
					else {
						g_point1 += food->GetPoint(food->GetFoodID());
					}
					
						/*if (food->GetPoint(food->GetFoodID()) > 0) m_posSound->PlaySound();
						else m_negSound->PlaySound();*/
					
					//p1->ChangeAnimation();
					food->SetActive(false);
				}

				if (Collision::checkCollision(p_near2, item)) p2->ChangeAnimation();
				if (food->IsActive() && Collision::checkCollision(p_char2, item)) {
					if (g_point2 + food->GetPoint(food->GetFoodID()) < 0) g_point2 = 0;
					else {
						g_point2 += food->GetPoint(food->GetFoodID());
					}
					
						/*if (food->GetPoint(food->GetFoodID()) > 0) m_posSound->PlaySound();
						else m_negSound->PlaySound();*/
					
					//p2->ChangeAnimation();
					food->SetActive(false);
				}
			}

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
			else {
				temp = t_duration.GetDuration() - t_duration.GetTicks();
				std::string str3 = std::to_string(temp / 1000);
				m_time->LoadFromRenderText(str3);
				m_time->Update(deltaTime);
			}

			p1->Update(deltaTime);
			p2->Update(deltaTime);

			for (auto it : m_listScore) {
				it->Update(deltaTime);
			}
		}
	}
	else {
		inTime = false;
		g_timer.Start();
		t_duration.SetDuration(temp);
		t_duration.Start();
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
	//m_time->Draw(renderer);
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