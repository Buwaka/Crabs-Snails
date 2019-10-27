#include "stdafx.h"
#include "Bow.h"
#include "TaskAttack.h"
#include "TaskManager.h"
#include "EnemyManager.h"



Bow::Bow(int tilesize, std::string pathbase, std::string pathattack, TaskManager * taskmanager, EnemyManager * enemymanager) :
Weapon {	tilesize, taskmanager, enemymanager}
{

	m_pSpriteBase = std::make_shared<Texture>(pathbase);
	m_pSpriteAttack = std::make_shared<Texture>(pathattack);

	//unique hitbox
	m_Hitbox.push_back(Rectf{ (float)m_Tilesize / 4 , 0, (float)m_Tilesize / 2, (float)m_Tilesize });

	m_Speed = 1;
	m_AnimationLength = 1.0f;
	m_ArrowDistance = (float) m_Tilesize * 5; //3 tiles in distance


	m_Complete = true;
	m_Type = WeaponManager::Weapons::bow;
}

Bow::~Bow()
{
}

void Bow::Attack(Player * caster, Sutils::Direction direction, const float elapsedSec)
{

		m_Complete = false;
		m_pTaskManager->Add(new TaskAttack((Weapon*)this, caster, direction, m_pEnemyManager->GetEnemyPool(), elapsedSec));
		//caster->DisableInput();
		m_Timer = 0;
	

}

void Bow::Draw(Sutils::Direction direction, Point2f startPosition, Point2f position, bool attack, float interpolate) const
{
	float degree, x, y;

	glPushMatrix();
	{

		//translate to position
		if (attack)
		{
			x =  Sutils::lerpS(startPosition.x, position.x, interpolate);
			y =  Sutils::lerpS(startPosition.y, position.y, interpolate);
			glTranslatef(x + ((float)m_Tilesize / 4 * 3), y + ((float)m_Tilesize / 2), 0);
		}
		else
		{
			glTranslatef(position.x + ((float)m_Tilesize / 4 * 3), position.y + ((float)m_Tilesize / 2), 0);
		}


		//rotation
		switch (direction)
		{
		case Sutils::Up: degree = 0;
			break;
		case Sutils::Down: degree = 180;
			break;
		case Sutils::Left: degree = 90;
			break;
		case Sutils::Right: degree = 270;
			break;
		}

		glRotatef(degree, 0, 0, 1);

		//scale
		glScalef(1, 1, 0);

		//center for rotation
		glTranslatef(-(m_pSpriteBase->GetWidth() /2), -(m_pSpriteBase->GetHeight() / 2), 0);



		if (attack)
		{
			m_pSpriteAttack->Draw({ 0,0, m_pSpriteAttack->GetWidth() , m_pSpriteAttack->GetHeight() }, {});
		}
		else
		{
			m_pSpriteBase->Draw({ 0, 0, m_pSpriteBase->GetWidth() , m_pSpriteBase->GetHeight() }, {});
		}
	}
	glPopMatrix();
}

bool Bow::Update(Player * caster, Vector2f startposition, Vector2f* position, Sutils::Direction direction, const float elapsedSec)
{


	//maak update per tile

	switch (direction)
	{
	case Sutils::Down: *position = startposition + Vector2f{ 0, (float)- (m_ArrowDistance * (elapsedSec / m_AnimationLength)) };
		break;
	case Sutils::Left: *position = startposition + Vector2f{ (float)-(m_ArrowDistance * (elapsedSec / m_AnimationLength)),0 };
		break;
	case Sutils::Right: *position = startposition + Vector2f{ (float)(m_ArrowDistance * (elapsedSec / m_AnimationLength)),0 };
		break;
	case Sutils::Up: *position = startposition + Vector2f{ 0,(float)(m_ArrowDistance * (elapsedSec / m_AnimationLength)) };
		break;
	}

	if (elapsedSec >= m_AnimationLength)
	{
		return true;
	}
	return false;
}

std::vector<Rectf> Bow::GetHitbox() const
{
	return m_Hitbox;
}
