#include "pch.h"
#include "Game.h"
#include "utils.h"
#include "SoundEffect.h"
#include "Texture.h"
#include "WaveManager.h"
#include <iostream>



Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}


void Game::SpawnCornerMemories()
{
	
	int enemyCount = (int) round(4 * pow(1.18, m_Wave));

	float enemyBaseSpeed = 60.f * enemyCount/4;

	float timeRegain = std::max(1.f, 5.f / (m_Wave));

	for (int i{}; i < enemyCount; i++)
	{

		float randomDev = enemyBaseSpeed * 0.1f * (rand() % 100) / 10;

		bool horizontal = rand() % 2;
		int left = rand() % 2;

		Point2f position{};

		if (horizontal)
		{
			position = Point2f{ float(rand() % int(GetViewPort().width)), left*GetViewPort().height};
		} 
		else
		{
			position = Point2f{ left*GetViewPort().width, float(rand() % int(GetViewPort().height))};
		}

		enemies.emplace_back(new Enemy(position, enemyBaseSpeed + randomDev, timeRegain, GetViewPort()));
	}

	

}

void Game::Initialize( )
{
	m_Introscreen = new IntroScreen(GetViewPort());
	m_pPlayer = new Player(Point2f{ GetViewPort().width / 2, GetViewPort().height / 2 }, 500.f, GetViewPort());
	//SDL_SetWindowFullscreen(this->GetBaseWindow(), SDL_WINDOW_FULLSCREEN);
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
		
		if (m_WaveDownBool)
		{
			if (m_WaveDownTimer >= 3.f)
			{
				m_WaveDownBool = false;
				m_WaveDownTimer = 0.f;
				SpawnCornerMemories();
			}
			else
			{
				m_WaveDownTimer += elapsedSec;
			}
		}
		else {
			m_pPlayer->Update(elapsedSec);
		}

		
		if (enemies.size() == 0)
		{
			if (!m_WaveDownTimer)
			{
				++m_Wave;
				m_WaveDownBool = true;
			}

		}
	
		

		for (int i =0; i < enemies.size(); ++i)
		{
			Enemy* enemy = enemies[i];

			if (!enemy->m_DeleteFlag)
			{
				enemy->Update(elapsedSec, m_pPlayer);

				if (utils::IsOverlapping(enemy->GetCharacterBox(), m_pPlayer->GetCharacterBox()))
				{
					enemy->Hit(m_pPlayer);
				}

			} 
			else
			{
				delete enemy;
				enemy = nullptr;
				enemies.erase(enemies.begin() + i);
			}
		}

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
		
		if (m_WaveDownBool)
		{
			DrawWaveScreen();
		}

		for (Enemy* enemy : enemies)
		{
			enemy->Draw();
		}

		m_pPlayer->Draw();

		Texture* Text = new Texture(("You have " + std::to_string(int(m_pPlayer->GetSecondsLeft())) + " seconds left."), "BlithedaleSerif-Regular.otf", 30, Color4f{1,1,1,1});
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
	Texture* Text = new Texture("You have been forgotten.", "BlithedaleSerif-Regular.otf", 40, Color4f{ 1,1,1,1 });
	Texture* Text1 = new Texture("Press SPACE to restart.", "BlithedaleSerif-Regular.otf", 40, Color4f{ 1,1,1,1 });
	Text->Draw(Point2f{ GetViewPort().width / 2 - Text->GetWidth() / 2 ,GetViewPort().height / 2 - Text->GetHeight() / 2});
	Text1->Draw(Point2f{ GetViewPort().width / 2 - Text1->GetWidth() / 2 ,GetViewPort().height / 2 - Text1->GetHeight() / 2 - 40});
	delete Text;
	delete Text1;
}

void Game::DrawWaveScreen() const
{
	Texture* Text = new Texture("Wave " + std::to_string(m_Wave+1), "BlithedaleSerif-Regular.otf", 40, Color4f{1,1,1,1});
	Text->Draw(Point2f{ GetViewPort().width / 2 - Text->GetWidth() / 2 ,GetViewPort().height / 2 - Text->GetHeight() / 2 });
	delete Text;
}
