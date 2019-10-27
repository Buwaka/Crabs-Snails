#include "stdafx.h"
#include "ScriptMove.h"



ScriptMove::ScriptMove(Player * player, std::vector<Sutils::Direction>& directions)
{
	m_pPlayer = player;
	m_Complete = false;
	m_Step = 0;


	m_Directions = std::vector<Sutils::Direction>{ directions };

}

ScriptMove::ScriptMove(Player * player, Point2f destination, Grid map)
{
	m_pPlayer = player;
	m_Complete = false;
	m_Step = 0;


	m_Directions = Astar(map, m_pPlayer->GetPosition(), destination);
	if (m_Directions.empty())
	{
		m_Complete = true;
	}

	//delete m_pDirections;
}

ScriptMove::~ScriptMove()
{

	m_pPlayer->EnableInput();


}

void ScriptMove::Check(float elapsedSeconds)
{
	CheckInput();
	if (!m_Complete && !m_pPlayer->IsDisabled())
	{

		m_pPlayer->Move(m_Directions[m_Step]);
		m_Step++;
		if (m_Step >= (int) m_Directions.size())
		{
			m_Complete = true;
		}

	}
}

bool ScriptMove::Complete()
{
	return m_Complete;
}

void ScriptMove::Clean()
{

	/*if (m_pDirections != nullptr)
	{
		delete m_pDirections;
	}*/
}

void ScriptMove::CheckInput()
{
	const Uint8 *pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_RIGHT] || pStates[SDL_SCANCODE_LEFT] || pStates[SDL_SCANCODE_UP] || pStates[SDL_SCANCODE_DOWN])
	{
		m_Complete = true;
	}
}
