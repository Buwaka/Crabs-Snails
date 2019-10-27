#pragma once

//#include "TaskManager.h"
//#include "ScriptManager.h"
//#include "EnemyManager.h"
#include <vector>

class EnemyManager;
class TaskManager;
class Weapon;

class WeaponManager
{
public:

	enum Weapons
	{
		sword, bow, size
	};


	WeaponManager(int tilesize, TaskManager* taskmanager, EnemyManager* enemymanager);
	~WeaponManager();

	WeaponManager(const WeaponManager& other) = delete;
	WeaponManager& operator=(const WeaponManager& other) = delete;
	WeaponManager(WeaponManager&& other) = delete;
	WeaponManager& operator=(WeaponManager&& other) = delete;

	Weapon* GetWeapon(Weapons type) const;
	Weapon* GetDefaultWeapon() const;

private:
	std::vector<Weapon*> m_pWeapons;
	int m_Tilesize;
	TaskManager* m_pTaskmanager;
	EnemyManager* m_pEnemyManager;

};

