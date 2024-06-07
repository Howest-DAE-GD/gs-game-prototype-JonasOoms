#include "pch.h"
#include "Enemy.h"
#include "utils.h"
#include <iostream>

Enemy::Enemy(const Point2f& position, float velocity, float healthRegen ,const Rectf& Viewport) :
	m_Position{ position },
	m_VelocityMax{ velocity },
	m_ViewPort{ Viewport },
	m_AnimationTimer{ 0.f },
	m_Debounce{0.f},
	m_DebounceFree{true},
	m_HealthRegain{healthRegen}
{

	int random = rand() % 4;
	m_HitDirection = HitDirection(random);


}

void Enemy::Draw()
{

	const Color4f	end{};
	const Color4f start{};
	



	float h = sinf(m_AnimationTimer*(2*M_PI/0.3f)) + 1.f;

	Point2f startVertex;
	Point2f endVertex;


	switch (m_HitDirection)
	{
		case HitDirection::LEFT:
			startVertex = Point2f{ m_CharacterBox.left, m_CharacterBox.bottom + m_CharacterBox.height };
			endVertex = Point2f{ m_CharacterBox.left, m_CharacterBox.bottom };
		break;
		case HitDirection::DOWN:
			startVertex = Point2f{ m_CharacterBox.left, m_CharacterBox.bottom };
			endVertex = Point2f{ m_CharacterBox.left + m_CharacterBox.width, m_CharacterBox.bottom };
			break;
		case HitDirection::RIGHT:
			startVertex = Point2f{ m_CharacterBox.left + m_CharacterBox.width, m_CharacterBox.bottom };
			endVertex = Point2f{ m_CharacterBox.left + m_CharacterBox.width, m_CharacterBox.bottom + m_CharacterBox.height };
			break;
		case HitDirection::UP:
			startVertex = Point2f{ m_CharacterBox.left + m_CharacterBox.width, m_CharacterBox.bottom + m_CharacterBox.height };
			endVertex = Point2f{ m_CharacterBox.left, m_CharacterBox.bottom + m_CharacterBox.height };
			break;
	}


	utils::FillRect(m_CharacterBox);
	utils::SetColor(Color4f{1,0,0,h});
	utils::DrawLine(startVertex, endVertex, 6);
	utils::SetColor(Color4f{ 1,1,1,1 });

	

}

void Enemy::Update(float elapsedSec, Player* player)
{

	m_AnimationTimer += elapsedSec;

	m_Velocity = Vector2f{ player->GetPosition() - m_Position }.Normalized()*m_VelocityMax;
	
	m_Position = Point2f{ m_Position.x + m_Velocity.x*elapsedSec, m_Position.y + m_Velocity.y*elapsedSec };
	m_CharacterBox = Rectf{ m_Position.x - m_Width / 2, m_Position.y, m_Width, m_Height };

	if (m_Debounce >= 5)
	{
		m_DebounceFree = true;
		m_Debounce = 0;
	}

}


void Enemy::Die()
{
	m_DeleteFlag = true;
}

void Enemy::Hit(Player* hit)
{
	bool correctHit = false;

	switch (hit->GetDirection())
	{
	case Player::SwordDirection::UP:
		if (m_HitDirection == HitDirection::DOWN)
		{
			correctHit = true;
		}
		break;
	case Player::SwordDirection::RIGHT:
		if (m_HitDirection == HitDirection::LEFT)
		{
			correctHit = true;
		}
		break;
	case Player::SwordDirection::DOWN:
		if (m_HitDirection == HitDirection::UP)
		{
			correctHit = true;
		}
		break;
	case Player::SwordDirection::LEFT:
		if (m_HitDirection == HitDirection::RIGHT)
		{
			correctHit = true;
		}
		break;
	}

	if (correctHit)
	{
		hit->AddSeconds(m_HealthRegain);
		Die();
	}
	else
	{
		if (m_DebounceFree)
		{
			hit->RemoveSeconds(3);
			m_DebounceFree = false;
		}
		else
		{
			
		}
	}

}
