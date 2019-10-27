#pragma once
#include <vector>
#include "Enemy.h"
#include <unordered_map>

class Map;
class Player;

class EnemyManager
{
public:

	enum EnemyType
	{
		crab, slug, size
	};


	EnemyManager(Map* stage, Player* player, int tilesize = 32);
	~EnemyManager();

	EnemyManager(const EnemyManager& other) = delete;
	EnemyManager& operator=(const EnemyManager& other) = delete;
	EnemyManager(EnemyManager&& other) = delete;
	EnemyManager& operator=(EnemyManager&& other) = delete;


	void Draw(const float interpolate) const;
	void Update(const float elapsedSec);
	void Add(Enemy* enemy);
	void CreateEnemy(EnemyType type, Point2f destination = {0,0});
	Grid GetEnemyMap();

	std::vector<Enemy*>* GetEnemyPool();

	void Clean();



private:
	Map* m_pMap;
	Player* m_pPlayer;
	int m_tilesize;
	std::unordered_map <EnemyType, Enemy*> m_EnemyDataBase;
	std::vector<Enemy*> m_Enemies;

	int m_Counter{};
};

