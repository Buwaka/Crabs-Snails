#pragma once
#include "Weapon.h"
class Bow :	public Weapon
{
public:
	Bow(int tilesize, std::string pathbase, std::string pathattack, TaskManager* taskmanager, EnemyManager* enemymanager);
	~Bow();

	Bow(const Bow& other) = delete;
	Bow& operator=(const Bow& other) = delete;
	Bow(Bow&& other) = delete;
	Bow& operator=(Bow&& other) = delete;

	void Attack(Player* caster, Sutils::Direction direction, const float elapsedSec = 0) override;
	void Draw(Sutils::Direction direction, Point2f startPosition, Point2f position, bool attack, float interpolate = 0.5f) const override;
	bool Update(Player * caster, Vector2f startposition,Vector2f* position, Sutils::Direction direction, const float elapsedSec = 0);
	std::vector<Rectf> GetHitbox() const override;

private:
	float m_ArrowDistance, m_AnimationLength, m_Timer;

};

