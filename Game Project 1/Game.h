#pragma once

#include "Vector2f.h"

#include "Player.h"
#include "Camera.h"
#include "Map.h"
#include "Enemy.h"
#include "UI.h"
#include "DeusExMachina.h"

#include "TaskManager.h"
#include "EnemyManager.h"
#include "WeaponManager.h"
#include "ScriptManager.h"
#include "SoundManager.h"

#include <vector>
#include <deque>

class Game
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	bool Update( float elapsedSec );
	void Draw(const float interpolate) const;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseWheelEvent(const SDL_MouseWheelEvent& e);

private:
	// DATA MEMBERS
	const Window m_Window;
	Player m_Player;
	Camera m_Viewport;
	Map m_CurrentMap;
	UI m_UI;
	DeusExMachina m_Gameplay;



	TaskManager m_Taskmanager;
	WeaponManager m_WeaponManager;
	EnemyManager m_EnemyManager;
	ScriptManager m_Scriptmanager;
	SoundManager m_SoundManager;



	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;
};