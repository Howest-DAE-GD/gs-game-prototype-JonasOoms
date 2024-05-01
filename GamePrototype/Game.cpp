#include "pch.h"
#include "Game.h"
#include "utils.h"
#include "SoundEffect.h"
#include "Texture.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_Introscreen = new IntroScreen(GetViewPort());
	m_pPlayer = new Player(Point2f{ GetViewPort().width / 2, GetViewPort().height / 2 }, 30, GetViewPort());
}

void Game::Cleanup( )
{
	delete m_pPlayer;
}

void Game::Update( float elapsedSec )
{
	//m_pPlayer->Update(elapsedSec);
	if (m_GameState == GameState::INTRO)
	{
		m_Introscreen->Update(elapsedSec);
		if (m_Introscreen->GetDone())
		{
			m_GameState = GameState::PLAY;
		}
	}
	else if (m_GameState == GameState::PLAY)
	{
		m_FadeInTimer += elapsedSec;
		m_pPlayer->Update(elapsedSec);

		if (m_pPlayer->GetSecondsLeft() <= 0)
		{
			m_GameState = GameState::DEAD;
		}

	}
}

void Game::Draw( ) const
{
	ClearBackground();

	if (m_GameState == GameState::INTRO)
	{
		m_Introscreen->Draw();
	}
	else if (m_GameState == GameState::PLAY)
	{
		utils::SetColor(Color4f{ 0, 0, 0, m_FadeInTimer / 3.f });
		utils::FillRect(GetViewPort());
		utils::SetColor(Color4f{ 1,1,1,1 });
		m_pPlayer->Draw();

		Texture* Text = new Texture(("You have " + std::to_string(int(m_pPlayer->GetSecondsLeft())) + " seconds left."), "BlithedaleSerif-Regular.otf", 20, Color4f{1,1,1,1});
		Text->Draw(Point2f{ 30, 30 });
		delete Text;
		

	}
	else
	{
		DrawDeathScreen();
	}

	//m_pPlayer->Draw();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_pPlayer->ProcessMotion(e);
	
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	m_pPlayer->Release(e);
	if (e.keysym.sym == SDLK_SPACE)
	{
		if (m_GameState == GameState::INTRO)
		{
			if (!m_HasSkipped)
			{
				m_Introscreen->Skip();
				m_HasSkipped = true;
			}
		}
		else if (m_GameState == GameState::DEAD)
		{
			m_GameState = GameState::INTRO;
			m_Introscreen->Skip();
			m_pPlayer->Reset(Point2f{ GetViewPort().width / 2, GetViewPort().height / 2 });
			
		}

		
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//pew pew
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor(m_Background.r,m_Background.g,m_Background.b,m_Background.a);
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::DrawDeathScreen() const
{
	Texture* Text = new Texture("You have been forgotten.", "BlithedaleSerif-Regular.otf", 20, Color4f{ 1,1,1,1 });
	Texture* Text1 = new Texture("Press SPACE to restart.", "BlithedaleSerif-Regular.otf", 20, Color4f{ 1,1,1,1 });
	Text->Draw(Point2f{ GetViewPort().width / 2 - Text->GetWidth() / 2 ,GetViewPort().height / 2 - Text->GetHeight() / 2});
	Text1->Draw(Point2f{ GetViewPort().width / 2 - Text1->GetWidth() / 2 ,GetViewPort().height / 2 - Text1->GetHeight() / 2 - 40});
	delete Text;
	delete Text1;
}
