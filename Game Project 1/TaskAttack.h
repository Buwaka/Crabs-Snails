#pragma once
#include "Task.h"
#include "Weapon.h"
#include "utils.h"
#include "Enemy.h"
#include "Player.h"
#include <memory>


class TaskAttack : public Task
{
public:
	TaskAttack(Weapon* weapon, Player* caster, Sutils::Direction direction, std::vector<Enemy*>* enemypool, const float elapsedSec);
	~TaskAttack();

	TaskAttack(const TaskAttack& other) = delete;
	TaskAttack& operator=(const TaskAttack& other) = delete;
	TaskAttack(TaskAttack&& other) = delete;
	TaskAttack& operator=(TaskAttack&& other) = delete;

	void Update(float elaspedSeconds);
	void Draw(float interpolate, const Rectf window);

	Task::Layer Type() const;
	bool Complete() const;

protected:
	Weapon* m_pWeapon;
	Player* m_pPlayer;
	std::vector<Enemy*>* m_pEnemypool;
	Vector2f m_StartPosition, m_Position, m_LastPosition;
	Sutils::Direction m_Direction;

	Task::Layer m_Layer = Task::Layer::objects;
	bool m_Complete;
	float m_AccumulatedSeconds, m_LastElapsedSeconds;
	float m_Length;
};

