#pragma once
#include <vector>
#include <memory>
#include "Texture.h"
#include "utils.h"
#include "Enemy.h"
#include "Player.h"
#include "WeaponManager.h"


class TaskManager;
class EnemyManager;

class Weapon
{
public:
	Weapon(int tilesize, TaskManager* taskmanager, EnemyManager* enemymanager);
	virtual ~Weapon();

	virtual void Attack(Player* caster, Sutils::Direction direction, const float elapsedSec = 0) = 0;
	virtual void Draw(Sutils::Direction direction, Point2f startPosition, Point2f position, bool attack, float interpolate = 0.5f) const = 0;
	virtual void DrawIcon(Point2f position, float scale);
	virtual bool Update(Player * caster, Vector2f startposition, Vector2f* position, Sutils::Direction direction, const float elapsedSec = 0) = 0;
	virtual bool Complete() const;
	virtual std::vector<Rectf> GetHitbox() const;
	int GetTilesize() const;
	int GetSpeed() const;
	WeaponManager::Weapons GetType() const;

protected:
	std::vector<Rectf> m_Hitbox;
	std::shared_ptr<Texture> m_pSpriteBase, m_pSpriteAttack;
	int m_Speed; //in percentage
	int m_Tilesize;
	bool m_Complete;
	float m_AnimationLength;
	WeaponManager::Weapons m_Type;

	TaskManager* m_pTaskManager; //om task toe te voegen
	EnemyManager* m_pEnemyManager;
};

