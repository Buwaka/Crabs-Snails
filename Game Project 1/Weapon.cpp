#include "stdafx.h"
#include "Weapon.h"

Weapon::Weapon(int tilesize, TaskManager * taskmanager, EnemyManager * enemymanager)
{
	m_Tilesize = tilesize;
	m_pTaskManager = taskmanager;
	m_pEnemyManager = enemymanager;
}

Weapon::~Weapon()
{
}

void Weapon::DrawIcon(Point2f position, float scale)
{
	glPushMatrix();
	{
		glTranslatef(position.x, position.y, 0);

		glScalef(scale, scale, 1);

		m_pSpriteBase->Draw({ 0,0, m_pSpriteBase->GetWidth(), m_pSpriteBase->GetHeight() }, {});
	}
	glPopMatrix();
}

bool Weapon::Complete() const
{
	return m_Complete;
}

std::vector<Rectf> Weapon::GetHitbox() const
{
	return m_Hitbox;
}

int Weapon::GetTilesize() const
{
	return m_Tilesize;
}

int Weapon::GetSpeed() const
{
	return m_Speed;
}

WeaponManager::Weapons Weapon::GetType() const
{
	return m_Type;
}
