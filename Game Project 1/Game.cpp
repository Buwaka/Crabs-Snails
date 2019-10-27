#include "stdafx.h"
#include "Game.h"

#include "TaskFade.h"
#include "TaskAnimation.h"
#include "Grid.h"
#include "PathFinding.h"
#include "Slug.h"
#include "ScriptMove.h"

#include <time.h>



#define tilesize 32
#define scale 2.0f

float g_Scale = 2.0f;

Game::Game( const Window& window ) 
	:m_Window{ window }
	,m_Taskmanager(&m_Window)
	,m_WeaponManager{ tilesize, &m_Taskmanager, &m_EnemyManager }
	, m_EnemyManager{&m_CurrentMap, &m_Player, tilesize }
	, m_UI{&m_Window,&m_Player, tilesize}
	, m_Gameplay{tilesize, &m_Player, &m_CurrentMap, &m_EnemyManager}
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

//test
Rectf temp = { 100,100,100,100 };

void Game::Initialize( ) 
{
	srand((unsigned int)time(NULL));

	m_Player.Init("resources/testsprite.png", 32, {0,0},&m_Taskmanager, &m_WeaponManager, &m_SoundManager, &m_Window);

	m_CurrentMap.Init("resources/teststage.png", "resources/teststage_collission.png", 32, 32, &m_Window);

	//maze voor pathfinding
	/*m_CurrentMap.Init("resources/maze.png", "resources/maze.png", 32, 32, &m_Window);
	m_Scriptmanager.Add(new ScriptMove(&m_Player, {1568,1568}, m_CurrentMap.GetGrid()));*/
	


	m_Viewport.Init(&m_Window, {0,0}, g_Scale, m_CurrentMap.GetDimension());

	//test

	m_Taskmanager.Add(new TaskFade(1.5, Color4f{ 0.f,0.f,0.f,1.f }));
	
	m_SoundManager.PlayMusic(&m_CurrentMap);
}

void Game::Cleanup( )
{






}

bool Game::Update( float elapsedSec )
{
	//run scripts in queue
	m_Scriptmanager.Update(elapsedSec);

	//Gameplay Update
	m_Gameplay.Update();

	//update enemy behavior
	m_EnemyManager.Update(elapsedSec);

	//update tasks
	m_Taskmanager.Update(elapsedSec);

	//player update
	m_Player.Update(&m_CurrentMap, elapsedSec);

	//viewport/camera update
	m_Viewport.Update(m_Player.GetPosition().ToPoint2f());

	//stage update
	m_CurrentMap.Update();


	//cleanup
	m_Scriptmanager.Clean();
	m_EnemyManager.Clean();
	m_Taskmanager.Clean();


	if (m_Gameplay.Complete())
	{
		m_SoundManager.StopAll();
		return true;
	}


	return false;
}

void Game::Draw(const float interpolate) const
{
	ClearBackground( );

	Point2f interpolated = m_Viewport.GetInterpolatedViewPortPoin2f(interpolate);

	//split into background, player, objects, foreground, effects

	//new matrix
	glPushMatrix();
	{
		//reverse translate Map to player position
		glScalef(g_Scale, g_Scale, 0);
		glTranslatef(-interpolated.x, -interpolated.y, 0);


		m_CurrentMap.Draw();

		//background tasks
		m_Taskmanager.Draw(Task::background, interpolate);

		//objects
		//object tasks
		m_Taskmanager.Draw(Task::objects, interpolate);

		//player
		m_Player.Draw(interpolate);

		//enemies
		m_EnemyManager.Draw(interpolate);

		//foreground
		//foreground tasks
		m_Taskmanager.Draw(Task::foreground, interpolate);
	}
	//pop matrix
	glPopMatrix();

	//effects
	//effects tasks
	m_Taskmanager.Draw(Task::effects, interpolate);

	//UI
	m_UI.Draw(m_Gameplay.Highscore());

}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;

	switch (e.keysym.sym)
	{
	case SDLK_EQUALS:
	case SDLK_VOLUMEUP: m_SoundManager.IncreaseVolume();
		break;

	case SDLK_MINUS:
	case SDLK_VOLUMEDOWN:m_SoundManager.DecreaseVolume();
		break;

	case SDLK_SPACE: m_Player.Attack();
		break;
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	static float angle;
	static Sutils::Direction direct;

	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:

		angle = Sutils::Angle( Vector2f{ (float)e.x, m_Window.height - e.y } / scale - (m_Player.GetSpriteCenter() - m_Viewport.GetViewPortPoint())) * 180 / (float) M_PI;
		if (angle > 315 || angle <= 45)
		{
			direct = Sutils::Direction::Right;
		}
		else if (angle > 45 && angle <= 135)
		{
			direct = Sutils::Direction::Up;
		}
		else if (angle > 135 && angle <= 225)
		{
			direct = Sutils::Direction::Left;
		}
		else if (angle > 225 && angle <= 315)
		{
			direct = Sutils::Direction::Down;
		}
		//std::cout << (int)std::round(angle) << std::endl;
		m_Player.Attack(direct);

		break;
	case SDL_BUTTON_RIGHT:
		//std::cout << " right button " << std::endl;
		break;
	case SDL_BUTTON_MIDDLE:
		//std::cout << " middle button " << std::endl;
		break;
	}


	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	static Vector2f dest;


	//std::cout << "MOUSEBUTTONUP event: ";
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:

		break;
	case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
		dest = m_Viewport.GetMousePositionInWorld(e);
		m_Scriptmanager.Stop(Script::Move);
		m_Scriptmanager.Add(new ScriptMove(&m_Player, dest.ToPoint2f(), m_CurrentMap.GetGrid()));
		//std::cout << dest;


		
		break;
	case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
		//m_EnemyManager.CreateEnemy(EnemyManager::EnemyType::slug);
		//m_Gameplay.Update();
		break;
	}
}

void Game::ProcessMouseWheelEvent(const SDL_MouseWheelEvent & e)
{
	if (e.y > 0)
	{
		m_Player.ChangeWeapon(1);
	}
	else if (e.y < 0)
	{
		m_Player.ChangeWeapon(-1);
	}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.4f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
