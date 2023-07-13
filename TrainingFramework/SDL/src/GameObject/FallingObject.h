#include <BaseObject.h>
#include "TextureManager.h"

class FallingObject : public BaseObject
{
protected:
	Vector2 m_Vec2DPos;
	int     m_iWidth;
	int     m_iHeight;
	float   velocityY;

	float   m_numFrames;
	int     m_currentFrame;
	float   m_frameTime;
	float   m_currentTime;
	int	    m_frameCount;
	int		m_numAction;

	int	    m_spriteColumn;
	float   m_currentTicks;
	int		m_animSpeed;
	Uint32  m_lastUpdate;
	SDL_RendererFlip m_flip;

public:
	FallingObject() : BaseObject(), m_iWidth(0), m_iHeight(0) {}
	FallingObject(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip);
	~FallingObject();
	void Init() override;
	void Draw(SDL_Renderer* renderer) override;

	void Update(float deltatime) override;
	/*
	void Set2DPosition(float x, float y);
	Vector3		Get2DPosition();
	*/
	void SetSize(int width, int height);
	int GetWidth();
	int GetHeight();
	void SetRotation(double angle);
	void SetFlip(SDL_RendererFlip flip);
	void SetVelocityY(float velocity);

	/*
	public:
		FallingObject(int x, int y, int radius);
		void Update();
		void Render(SDL_Renderer* renderer);

	private:
		int posX;
		int posY;
		float velocityY;
		int objectRadius;
	*/
};