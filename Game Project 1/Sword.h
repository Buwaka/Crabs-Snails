#pragma once
#include "Weapon.h"
#include "Enemy.h"
#include <vector>
#include <string>

class Sword : public Weapon
{
public:
	Sword(int tilesize, std::string pathbase, std::string pathattack, TaskManager* taskmanager, EnemyManager* enemymanager);
	~Sword();

	Sword(const Sword& other) = delete;
	Sword& operator=(const Sword& other) = delete;
	Sword(Sword&& other) = delete;
	Sword& operator=(Sword&& other) = delete;

	void Attack(Player* caster, Sutils::Direction direction, const float elapsedSec = 0) override;
	void Draw(Sutils::Direction direction, Point2f startPosition, Point2f position, bool attack, float interpolate = 0.5f) const override;
	bool Update(Player * caster, Vector2f startposition, Vector2f* position, Sutils::Direction direction, const float elapsedSec = 0) override;

private:
	float m_Timer, m_degree, m_lastDegree;
};

