#include "GSGuide.h"

GSGuide::GSGuide() : GameStateBase(StateType::STATE_GUIDE),
guideFrm(nullptr), m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textColor(m_textColor), m_Font(m_Font)
{
}

GSGuide::~GSGuide()
{
}

void GSGuide::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("startbg.jpg");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	//guide frame
	texture = ResourceManagers::GetInstance()->GetTexture("control_htp.png");
	guideFrm = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	guideFrm->SetSize(746, 726);
	guideFrm->Set2DPosition((SCREEN_WIDTH - guideFrm->GetWidth()) / 2, (SCREEN_HEIDHT - guideFrm->GetHeight()) / 2);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("x.png");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(352 / 5, 372 / 5);
	btnClose->Set2DPosition((SCREEN_WIDTH - btnClose->GetWidth()) / 2, (SCREEN_HEIDHT - btnClose->GetHeight()) / 2 + 205);
	btnClose->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(btnClose);

	m_Sound = std::make_shared<Sound>("Data/Sounds/Alarm01.wav");
	m_Sound->PlaySound();
}

void GSGuide::Exit()
{
}

void GSGuide::Pause()
{
	m_Sound->StopSound();
}
void GSGuide::Resume()
{
	m_Sound->PlaySound();
}

void GSGuide::HandleEvents()
{
}

void GSGuide::HandleKeyEvents(SDL_Event& e)
{
}

void GSGuide::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSGuide::HandleMouseMoveEvents(int x, int y)
{
}

void GSGuide::Update(float deltaTime)
{
	float time = 0.0f;
	time += deltaTime;
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

void GSGuide::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	guideFrm->Draw(renderer);

	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
}
