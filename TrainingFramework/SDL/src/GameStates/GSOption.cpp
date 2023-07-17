#include "GSOption.h"

GSOption::GSOption() : GameStateBase(StateType::STATE_OPTION),
frm(nullptr), m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textColor(m_textColor), m_Font(m_Font)
{
}

GSOption::~GSOption()
{
}

void GSOption::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("startbg.jpg");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	//option frame
	texture = ResourceManagers::GetInstance()->GetTexture("popupinner-slow.jpg");
	frm = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	frm->SetSize(577, 364);
	frm->Set2DPosition(SCREEN_WIDTH / 2 - 288.5, SCREEN_HEIDHT / 2 - 182);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(80, 80);
	btnClose->Set2DPosition(SCREEN_WIDTH - 90, 10);
	btnClose->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(btnClose);

	m_Sound = std::make_shared<Sound>("Data/Sounds/Alarm01.wav");
	m_Sound->PlaySound();
}

void GSOption::Exit()
{

}

void GSOption::Pause()
{
	m_Sound->StopSound();
}
void GSOption::Resume()
{
	m_Sound->PlaySound();
}

void GSOption::HandleEvents()
{
}

void GSOption::HandleKeyEvents(SDL_Event& e)
{
}

void GSOption::HandleTouchEvents(SDL_Event& e, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSOption::HandleMouseMoveEvents(int x, int y)
{
}

void GSOption::Update(float deltaTime)
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

void GSOption::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	frm->Draw(renderer);
	//m_textGameName->Draw(renderer);
}
