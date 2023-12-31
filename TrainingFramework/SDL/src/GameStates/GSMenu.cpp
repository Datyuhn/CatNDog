#include "GSMenu.h"

GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr), m_textColor(m_textColor), m_Font(m_Font)
{
}

GSMenu::~GSMenu()
{
}

void GSMenu::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Untitled.png");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("play1-removebg-preview.png");
	std::shared_ptr<MouseButton> btnPlay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);

	btnPlay->SetSize(317, 90);
	btnPlay->Set2DPosition((SCREEN_WIDTH - btnPlay->GetWidth()) / 2, (SCREEN_HEIDHT - btnPlay->GetHeight()) / 2-20);
	btnPlay->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(btnPlay);

	// how to play button
	texture = ResourceManagers::GetInstance()->GetTexture("htp-removebg-preview.png");
	std::shared_ptr<MouseButton> btnGuide = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);

	btnGuide->SetSize(317, 90);
	btnGuide->Set2DPosition((SCREEN_WIDTH - btnGuide->GetWidth()) / 2, (SCREEN_HEIDHT - btnGuide->GetHeight()) / 2 + 70);
	btnGuide->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_GUIDE);
		});
	m_listButton.push_back(btnGuide);

	// option button
	texture = ResourceManagers::GetInstance()->GetTexture("option-removebg-preview.png");
	std::shared_ptr<MouseButton> btnOption = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);

	btnOption->SetSize(317, 90);
	btnOption->Set2DPosition((SCREEN_WIDTH - btnPlay->GetWidth()) / 2, (SCREEN_HEIDHT - btnPlay->GetHeight()) / 2 + 160);
	btnOption->SetOnClick([]() {
		//GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OPTION);
		});
	m_listButton.push_back(btnOption);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("exit-removebg-preview.png");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(317, 90);
	btnClose->Set2DPosition((SCREEN_WIDTH - btnPlay->GetWidth()) / 2, (SCREEN_HEIDHT - btnPlay->GetHeight()) / 2 + 250);
	btnClose->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(btnClose);


	//Setting game
	
//	texture = ResourceManagers::GetInstance()->GetTexture("btn_settings.tga");
//	std::shared_ptr<MouseButton> btnOption = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
//	btnOption->SetSize(100, 100);
//	btnOption->Set2DPosition((SCREEN_WIDTH - btnOption->GetWidth()) / 2, SCREEN_HEIDHT / 2 + 70);
//	btnOption->SetOnClick([]() {
//		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OPTION);
//		});
//	m_listButton.push_back(btnOption);

	// Game title
	// Set Font
	m_textColor = { 189,119,86 };
	m_textGameName = std::make_shared<Text>("Data/BADABB__.ttf", m_textColor);
	m_textGameName->SetSize(350, 85);
	m_textGameName->Set2DPosition((SCREEN_WIDTH - m_textGameName->GetWidth())/2, SCREEN_HEIDHT / 2 - 260);
	m_textGameName->LoadFromRenderText("Feed me");

	m_Sound = std::make_shared<Sound>("Data/Sounds/Intro_OGGY.mp3");
	m_Sound->PlaySound();
}

void GSMenu::Exit()
{
	ResourceManagers::FreeInstance();
}

void GSMenu::Pause()
{
	m_Sound->StopSound();
}

void GSMenu::Resume()
{
	m_Sound->PlaySound();
}

void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(SDL_Event& e)
{
}

void GSMenu::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button ->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}
void GSMenu::Update(float deltaTime)
{
	float time = 0.0f;
	time += deltaTime;
	//printf("DeltaTime = %f", deltaTime);
	if (time >= 1.5f)
	{
		time = 0.0f;
	}
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	m_textGameName->Draw(renderer);
}
