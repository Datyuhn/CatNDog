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
	auto texture = ResourceManagers::GetInstance()->GetTexture("Untitled.png");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	//option frame
	texture = ResourceManagers::GetInstance()->GetTexture("frame-wood.png");
	frm = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	frm->SetSize(868, 646);
	frm->Set2DPosition((SCREEN_WIDTH - frm->GetWidth()) / 2, (SCREEN_HEIDHT - frm->GetHeight()) / 2);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("x.png");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(352 / 5, 372 / 5);
	btnClose->Set2DPosition((SCREEN_WIDTH - btnClose->GetWidth()) / 2, (SCREEN_HEIDHT - btnClose->GetHeight()) / 2 + 180);
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
	frm->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
}
