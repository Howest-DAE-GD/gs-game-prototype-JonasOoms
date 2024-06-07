#include "pch.h"
#include "Player.h"
#include "utils.h"
#include <iostream>
#include <vector>


Player::Player(const Point2f& position, const float velocity, const Rectf& Viewport) :
	m_Position{ position },
	m_MovementSpeed{ velocity },
	m_SecondsLeft{ 30.f },
	m_VelocityMax{ velocity }
{
	m_CharacterBox = Rectf{m_Position.x - m_Width / 2, m_Position.y, m_Width, m_Height };
	m_Velocity = Vector2f{ 0,0 };

	m_ViewPort = Viewport;

	m_DeathSound = new SoundEffect("Bell.wav");
	m_DeathSound->SetVolume(4);
}

void Player::ProcessMotion(const SDL_KeyboardEvent& e)
{
		switch (e.keysym.sym)
		{
		case SDLK_w:
			m_Velocity.y = m_MovementSpeed;
			m_IsMoving = true;
			break;
		case SDLK_a:
			m_Velocity.x = -m_MovementSpeed;
			m_IsMoving = true;
			break;
		case SDLK_d:
			m_Velocity.x = m_MovementSpeed;
			m_IsMoving = true;
			break;
		case SDLK_s:
			m_Velocity.y = -m_MovementSpeed;
			m_IsMoving = true;
			break;
		case SDLK_UP:
			m_SwordDirection = SwordDirection::UP;
			break;
		case SDLK_LEFT:
			m_SwordDirection = SwordDirection::LEFT;
			break;
		case SDLK_RIGHT:
			m_SwordDirection = SwordDirection::RIGHT;
			break;
		case SDLK_DOWN:
			m_SwordDirection = SwordDirection::DOWN;
			break;
		}
}

void Player::Release(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_w:
		m_Velocity.y = 0;
		m_IsMoving = false;
		break;
	case SDLK_a:
		m_Velocity.x = 0;
		m_IsMoving = false;
		break;
	case SDLK_d:
		m_Velocity.x = 0;
		m_IsMoving = false;
		break;
	case SDLK_s:
		m_Velocity.y = 0.f;
		m_IsMoving = false;
		break;
	}
}

void Player::Draw()
{
	Color4f color = Color4f{ 1.f,1.f,1.f,m_SecondsLeft / 30.f };
	utils::SetColor(color);
	utils::FillRect(m_CharacterBox);
	DrawSword();
}

void Player::Update(float elapsedSec)
{


	m_SecondsLeft -= elapsedSec;
	
	
	
	m_Position = Point2f{ m_Position.x + m_Velocity.x*elapsedSec, m_Position.y + m_Velocity.y*elapsedSec };
	m_CharacterBox = Rectf{ m_Position.x - m_Width / 2, m_Position.y, m_Width, m_Height };
	
	if (m_SecondsLeft <= 0.f)
	{
		m_DeathSound->Play(0);
	}

	if (m_Position.x >= m_ViewPort.width + 30)
	{
		m_Position.x = -20;
	}

	if (m_Position.x <= -30)
	{
		m_Position.x = m_ViewPort.width + 20;
	}

	if (m_Position.y >= m_ViewPort.height + 30)
	{
		m_Position.y = -20;
	}

	if (m_Position.y <= -30)
	{
		m_Position.y = m_ViewPort.height + 20;
	}

}

void Player::AddSeconds(float seconds)
{
	if (m_SecondsLeft + seconds < 30)
	{
		m_SecondsLeft += seconds;
	}
	else
	{
		m_SecondsLeft = 30;
	}
}

void Player::RemoveSeconds(float seconds)
{
	if (m_SecondsLeft - seconds > 0)
	{
		m_SecondsLeft -= seconds;
	}
	else
	{
		m_SecondsLeft = 0;
	}
}

void Player::Reset(const Point2f& position)
{
	m_SecondsLeft = 30.f;
	m_Position = position;
}

void Player::DrawSword()
{
	
	Point2f down;
	Point2f up;
	Point2f point;

	switch (m_SwordDirection)
	{
		case SwordDirection::UP:
			down = Point2f{ m_CharacterBox.left, m_CharacterBox.bottom + m_CharacterBox.height + m_CharacterBox.height*0.10f };
			up = Point2f{ m_CharacterBox.left + m_CharacterBox.width, m_CharacterBox.bottom + m_CharacterBox.height + m_CharacterBox.height*0.10f };
			point = Point2f{ m_CharacterBox.left + m_CharacterBox.width * 0.50f, m_CharacterBox.bottom + m_CharacterBox.height + m_CharacterBox.height*0.5f };
			break;
		case SwordDirection::DOWN:
			down = Point2f{ m_CharacterBox.left, m_CharacterBox.bottom - m_CharacterBox.height * 0.10f };
			up = Point2f{ m_CharacterBox.left + m_CharacterBox.width, m_CharacterBox.bottom - m_CharacterBox.height * 0.10f };
			point = Point2f{ m_CharacterBox.left + m_CharacterBox.width * 0.50f, m_CharacterBox.bottom - m_CharacterBox.height * 0.5f };
			break;
		case SwordDirection::LEFT:
			down = Point2f{ m_CharacterBox.left - m_CharacterBox.width * 0.10f, m_CharacterBox.bottom };
			up = Point2f{ m_CharacterBox.left - m_CharacterBox.width * 0.10f, m_CharacterBox.bottom + m_CharacterBox.height };
			point = Point2f{ m_CharacterBox.left - m_CharacterBox.width * 0.10f - m_CharacterBox.width * 0.50f, m_CharacterBox.bottom + m_CharacterBox.height * 0.5f };
			break;
		case SwordDirection::RIGHT:
			down = Point2f{ m_CharacterBox.left + m_CharacterBox.width + m_CharacterBox.width * 0.10f, m_CharacterBox.bottom };
			up = Point2f{ m_CharacterBox.left + m_CharacterBox.width + m_CharacterBox.width * 0.10f, m_CharacterBox.bottom + m_CharacterBox.height };
			point = Point2f{ m_CharacterBox.left + m_CharacterBox.width + m_CharacterBox.width * 0.10f + m_CharacterBox.width * 0.50f, m_CharacterBox.bottom + m_CharacterBox.height * 0.5f };
			break;
	}

	std::vector<Point2f> Polygon;
	/*Point2f down = Point2f{ m_CharacterBox.left + m_CharacterBox.width + m_CharacterBox.width * 0.10f, m_CharacterBox.bottom };
	Point2f up = Point2f{ m_CharacterBox.left + m_CharacterBox.width + m_CharacterBox.width * 0.10f, m_CharacterBox.bottom + m_CharacterBox.height };
	Point2f point = Point2f{ m_CharacterBox.left + m_CharacterBox.width + m_CharacterBox.width * 0.10f + m_CharacterBox.width * 0.50f, m_CharacterBox.bottom + m_CharacterBox.height * 0.5f };*/
	Polygon.emplace_back(down);
	Polygon.emplace_back(up);
	Polygon.emplace_back(point);


	glPushMatrix();
	{
		utils::FillPolygon(Polygon);
	}
	glPopMatrix();

}

