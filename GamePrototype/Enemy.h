#pragma once
#include "Vector2f.h"
#include "Player.h"

class Enemy
{
public:

	enum class HitDirection
	{
		LEFT,
		UP,
		RIGHT,
		DOWN
	};

	Enemy(const Point2f& position, float velocity, float healthRegen , const Rectf& Viewport);

	
	void Draw();
	void Update(float elapsedSec, Player* player);
	void Die();
	void Hit(Player* hit);
	Point2f GetPosition() { return m_Position; };
	Rectf GetCharacterBox() { return m_CharacterBox; };

	bool m_DeleteFlag{ false };

private:
	Point2f m_Position;
	Rectf m_CharacterBox;
	const float m_VelocityMax;
	Vector2f m_Velocity;
	Rectf m_ViewPort;
	HitDirection m_HitDirection;

	const float m_HealthRegain;

	const float m_MovementSpeed{ 2.f };

	float m_AnimationTimer;
	float m_Debounce;
	bool m_DebounceFree;

	const float m_Width{ 64 };
	const float m_Height{ 64 };

	

};

