#pragma once
#include "pch.h"
#include "Vector2f.h"
#include "SoundEffect.h"

enum class PlayerState;

class Player
{
public:

	enum class SwordDirection
	{
		NONE, UP,DOWN,LEFT,RIGHT
	};

	Player(const Point2f& position, const float velocity, const Rectf& Viewport);

	void ProcessMotion(const SDL_KeyboardEvent& e);
	void Release(const SDL_KeyboardEvent& e);
	void Draw();
	void Update(float elapsedSec);

	float GetSecondsLeft() { return m_SecondsLeft; };
	void AddSeconds(float seconds);
	void RemoveSeconds(float seconds);
	Point2f GetPosition() { return m_Position; };
	SwordDirection GetDirection() { return m_SwordDirection; };
	Rectf GetCharacterBox() { return m_CharacterBox; };

	void Reset(const Point2f& position);

private:
	Point2f m_Position;
	float m_SecondsLeft;
	Rectf m_CharacterBox;
	const float m_VelocityMax;
	Vector2f m_Velocity;
	bool m_IsMoving{ false };
	Rectf m_ViewPort;

	SwordDirection m_SwordDirection;

	const float m_MovementSpeed{ 5.f };

	const float m_Width{ 64 };
	const float m_Height{ 64 };

	SoundEffect* m_DeathSound;

	void DrawSword();


};


