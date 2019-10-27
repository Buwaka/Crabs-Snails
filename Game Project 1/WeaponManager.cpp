#include "stdafx.h"
#include "WeaponManager.h"
#include "TaskManager.h"
#include "EnemyManager.h"

#include "Sword.h"
#include "Bow.h"

WeaponManager::WeaponManager(int tilesize, TaskManager * taskmanager, EnemyManager * enemymanager)
{
	m_Tilesize = tilesize;
	m_pTaskmanager = taskmanager;
	m_pEnemyManager = enemymanager;

	m_pWeapons.resize(Weapons::size);

	//Sword
	m_pWeapons[sword] = new Sword(m_Tilesize, "resources/sword.png", "resources/sword_attack.png", m_pTaskmanager, m_pEnemyManager);

	//Bow
	m_pWeapons[bow] = new Bow(m_Tilesize, "resources/bow.png", "resources/arrow.png", m_pTaskmanager, m_pEnemyManager);
}

WeaponManager::~WeaponManager()
{
	for (Weapon* weapon : m_pWeapons)
	{
		delete weapon;
	}
}

Weapon * WeaponManager::GetWeapon(Weapons type) const
{
	return m_pWeapons[type];
}

Weapon * WeaponManager::GetDefaultWeapon() const
{
	return m_pWeapons[sword];
}
