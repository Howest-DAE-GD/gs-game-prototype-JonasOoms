#pragma once
#include "pch.h"
#include "Vector2f.h"
#include "SoundEffect.h"

enum class PlayerState;

class Player
{
public:
	Player(const Point2f& position, const float velocity, const Rectf& Viewport);

	void ProcessMotion(const SDL_KeyboardEvent& e);
	void Release(const SDL_KeyboardEvent& e);
	void Draw();
	void Update(float elapsedSec);

	float GetSecondsLeft() { return m_SecondsLeft; };

	void Reset(const Point2f& position);

private:
	Point2f m_Position;
	float m_SecondsLeft;
	Rectf m_CharacterBox;
	const float m_VelocityMax;
	Vector2f m_Velocity;
	bool m_IsMoving{ false };
	Rectf m_ViewPort;

	const float m_MovementSpeed{ 5.f };

	const float m_Width{ 36 };
	const float m_Height{ 36 };

	SoundEffect* m_DeathSound;



};


