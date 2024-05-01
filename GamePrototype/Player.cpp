#include "pch.h"
#include "Player.h"
#include "utils.h"
#include <iostream>



Player::Player(const Point2f& position, const float velocity, const Rectf& Viewport):
	m_Position{position},
	m_VelocityMax{velocity},
	m_SecondsLeft{30.f}
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
}

void Player::Update(float elapsedSec)
{


	m_SecondsLeft -= elapsedSec;
	
	
	
	m_Position = Point2f{ m_Position.x + m_Velocity.x, m_Position.y + m_Velocity.y };
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

void Player::Reset(const Point2f& position)
{
	m_SecondsLeft = 30.f;
	m_Position = position;
}

