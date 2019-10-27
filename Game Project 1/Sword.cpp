#include "stdafx.h"
#include "Sword.h"
#include "utils.h"
#include <algorithm>
#include "TaskAttack.h"
#include "TaskManager.h"
#include "EnemyManager.h"


Sword::Sword(int tilesize, std::string pathbase, std::string pathattack, TaskManager* taskmanager, EnemyManager* enemymanager) :
	Weapon{tilesize, taskmanager, enemymanager }
{

	m_pSpriteBase = std::make_shared<Texture>(pathbase);
	m_pSpriteAttack = std::make_shared<Texture>(pathattack);
	m_degree = m_lastDegree = 0;
	m_Speed = 10;

	//unique hitbox
	m_Hitbox.push_back( Rectf{(float) -m_Tilesize, (float)m_Tilesize, (float)m_Tilesize * 3, (float)m_Tilesize });
	m_Hitbox.push_back(Rectf{0, 0, (float)m_Tilesize, (float)m_Tilesize });

	//attacktime, 3 tiles van hitbox + 1 tile overlap
	m_AnimationLength = 4.0f / m_Speed;

	m_Type = WeaponManager::Weapons::sword;
	
}

Sword::~Sword()
{
}

void Sword::Attack(Player* caster, Sutils::Direction direction, const float elapsedSec)
{
	
	m_pTaskManager->Add(new TaskAttack((Weapon*)this, caster, direction, m_pEnemyManager->GetEnemyPool(), elapsedSec));
	m_Complete = false;
	// -30 graden voor swing
	m_degree = m_lastDegree = -30.0f;
	caster->DisableInput();
}

void Sword::Draw(Sutils::Direction direction, Point2f startPosition, Point2f position, bool attack, float interpolate ) const
{
	float scale = (attack)? 2.0f : 1.0f;
	float t_degree;
	glPushMatrix();
	{
		//translate to position
		glTranslatef(position.x + ((float)m_Tilesize / 2), position.y + ((float)m_Tilesize / 3), 0);
		
		//rotation
		switch (direction)
		{
		case Sutils::Up: t_degree = 0;
			break;
		case Sutils::Down: t_degree = 180;
			break;
		case Sutils::Left: t_degree = 90;
			break;
		case Sutils::Right: t_degree = 270;
			break;
		}

		if (attack)
		{
			t_degree += Sutils::lerpS(m_lastDegree, m_degree, interpolate);
		}

		glRotatef(t_degree, 0, 0, 1);

		//scale
		glScalef(scale, scale, 0);

		//center for rotation
		glTranslatef(-(m_pSpriteBase->GetWidth() /  10 * 3), 0, 0);

		if (attack)
		{
			m_pSpriteAttack->Draw({ 0, 0, m_pSpriteAttack->GetWidth() , m_pSpriteAttack->GetHeight() }, {});
		}
		else
		{
			m_pSpriteBase->Draw({ 0, 0, m_pSpriteBase->GetWidth() , m_pSpriteBase->GetHeight() }, {});
		}

	}
	glPopMatrix();

}

bool Sword::Update(Player * caster, Vector2f startposition, Vector2f * position, Sutils::Direction direction, const float elapsedSec)
{
	m_lastDegree = m_degree;
	m_degree = (120.0f * (elapsedSec / m_AnimationLength)) - 30.0f; //swing for attack

	if (elapsedSec > m_AnimationLength)
	{
		caster->EnableInput();
		return true;
	}
	return false;
}




