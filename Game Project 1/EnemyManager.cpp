#include "stdafx.h"
#include "EnemyManager.h"

#include "Slug.h"
#include "Crab.h"

#define CalcualtePerUpdate 4


EnemyManager::EnemyManager(Map * stage, Player * player, int tilesize)
{
	m_pMap = stage;
	m_pPlayer = player;
	m_tilesize = tilesize;

	m_EnemyDataBase.reserve(EnemyType::size);

	//slug
	m_EnemyDataBase[crab] = new Crab({0,0}, "resources/crab.png", this, m_tilesize);
	m_EnemyDataBase[slug] = new Slug({ 0,0 }, "resources/slug.png", "resources/slugtrail.png", this, m_tilesize);
}

EnemyManager::~EnemyManager()
{
	for (auto enemy : m_Enemies)
	{

		delete enemy;

	}

	for (auto enemy : m_EnemyDataBase)
	{

		delete enemy.second;

	}
}

void EnemyManager::Draw(const float interpolate) const
{
	for (auto enemy : m_Enemies)
	{
		enemy->Draw(interpolate);
	}
}

void EnemyManager::Update(const float elapsedSec)
{
	int count{}, i{};

	for (auto enemy : m_Enemies)
	{
		bool calc = false;
		if (i >= m_Counter && count < CalcualtePerUpdate)
		{
			calc = true;
			count++;
		}
		enemy->Update(elapsedSec, m_pMap, m_pPlayer, calc);
		i++;
	}
	m_Counter = (m_Counter + CalcualtePerUpdate) % m_Enemies.size();
}

void EnemyManager::Add(Enemy* enemy)
{
	m_Enemies.push_back(enemy);
}

void EnemyManager::CreateEnemy(EnemyType type, Point2f destination)
{
	Enemy* temp = m_EnemyDataBase[type]->Clone();
	temp->SetPosition(destination);
	m_Enemies.push_back(temp);
}

Grid EnemyManager::GetEnemyMap()
{
	Grid temp(m_pMap->GetGrid().GetGridWidth(), m_pMap->GetGrid().GetGridHeight(), m_pMap->m_TileSizeX);
	for (Enemy* var : m_Enemies)
	{
		Vector2f pos = var->GetPosition();
		temp.SetValue((int)pos.x, (int)pos.y, false);
	}

	return temp;
}

std::vector<Enemy*>* EnemyManager::GetEnemyPool()
{
	return &m_Enemies;
}

void EnemyManager::Clean()
{
	for (size_t i = 0; i < m_Enemies.size(); i++)
	{
		if (m_Enemies[i]->Complete())
		{
			delete m_Enemies[i];
			m_Enemies.erase(m_Enemies.begin() + i);
		}
	}
}
