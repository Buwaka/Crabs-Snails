#pragma once

class EnemyManager;
class TaskManager;
class Player;
class Map;

class DeusExMachina
{
public:
	DeusExMachina(int tilesize, Player* player, Map* map, EnemyManager* EnemyManager);
	~DeusExMachina();
	DeusExMachina(const DeusExMachina& other) = delete;
	DeusExMachina& operator=(const DeusExMachina& other) = delete;
	DeusExMachina(DeusExMachina&& other) = delete;
	DeusExMachina& operator=(DeusExMachina&& other) = delete;

	void Update();
	void AddRandomEnemy();
	int Highscore() const;
	bool Complete() const;

private:
	int m_count, m_Highscore;
	EnemyManager* m_pEnemyManager;
	TaskManager* m_pTaskManager;
	Map* m_pMap;
	Player* m_pPlayer;
	bool m_Complete;
	int m_Tilesize;


};

