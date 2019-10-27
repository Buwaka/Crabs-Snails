#include "stdafx.h"
#include "DeusExMachina.h"
#include "EnemyManager.h"
#include "TaskManager.h"
#include "Player.h"
#include "Map.h"
#include "TaskFade.h"

#include <time.h>


DeusExMachina::DeusExMachina(int tilesize, Player * player, Map * map, EnemyManager * EnemyManager)
{
	m_pPlayer = player;
	m_pEnemyManager = EnemyManager;
	m_pMap = map;
	m_Tilesize = tilesize;

	m_count = 1;
	m_Highscore = 0;
	m_Complete = false;
}

DeusExMachina::~DeusExMachina()
{
}

void DeusExMachina::Update()
{

	int totalEnemies = (int) m_pEnemyManager->GetEnemyPool()->size();

	if (totalEnemies < m_count)
	{
		m_Highscore += m_count - totalEnemies;
		m_count = totalEnemies;
	}

	if (totalEnemies == 0)
	{

		for (int i = 0; i < m_Highscore; i++)
		{
			AddRandomEnemy();
			m_count++;
		}

	}

	if (m_pPlayer->GetHealth() <= 0)
	{
		//end game
		m_Complete = true;
	}
}

void DeusExMachina::AddRandomEnemy()
{
	
	bool isOK = false;

	while (!isOK)
	{
		int x =  Sutils::clamp((int)std::round(float(rand() % m_pMap->m_Width) / m_Tilesize) * m_Tilesize, 0, m_pMap->m_Width - m_Tilesize);
		int y =  Sutils::clamp((int)std::round(float(rand() % m_pMap->m_Height) / m_Tilesize) * m_Tilesize, 0, m_pMap->m_Height - m_Tilesize);

		if (m_pMap->GetGrid().Getvalue(x, y))
		{
			isOK = true;
			m_pEnemyManager->CreateEnemy((EnemyManager::EnemyType)(rand() % EnemyManager::EnemyType::size), {(float) x, (float)y });
		}
	}

}

int DeusExMachina::Highscore() const
{
	return m_Highscore - 1;
}

bool DeusExMachina::Complete() const
{
	return m_Complete;
}
