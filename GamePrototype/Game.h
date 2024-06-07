#pragma once
#include "BaseGame.h"
#include "Player.h"
#include "IntroScreen.h"
#include "Enemy.h"
#include <vector>

enum class GameState
{
	INTRO,
	PLAY,
	DEAD
};

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:



	float m_Second;
	GameState m_GameState{ GameState::INTRO };
	
	Player* m_pPlayer{};
	Enemy* m_pEnemy{};

	std::vector<Enemy*> enemies;

	int m_Wave{-1};
	float m_WaveDownTimer{ 0.f };
	bool m_WaveDownBool{ false };

	bool m_HasSkipped{ false };
	float m_FadeInTimer{ 0.f };
	float m_DeathScreenTimer{ 0.f };

	IntroScreen* m_Introscreen{};

	Color4f m_Background = Color4f{ 0.0f,0.0f,0.0f,1.0f };

	// FUNCTIONS
	void SpawnCornerMemories();
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
	void DrawDeathScreen() const;
	void DrawWaveScreen() const;
};