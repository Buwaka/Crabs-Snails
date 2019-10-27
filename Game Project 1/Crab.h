#pragma once
#include "Enemy.h"
#include <string>
#include <vector>
#include "utils.h"
#include "Map.h"

class Crab : public Enemy
{
public:
	Crab(Vector2f position, std::string pathtosprite, EnemyManager* manager, int tilesize = 32, float speed = 1, int power = 1);
	Crab(Vector2f position, std::shared_ptr<Texture> sprite, EnemyManager* manager, int tilesize = 32, float speed = 1, int power = 1);
	~Crab();
	Crab(const Crab& other); // copy constructor
	Crab(Crab&& other); // move constructor
	Crab& operator=(const Crab& other); // copy assignment
	Crab& operator=(Crab&& other); // move assignment


	void Update(const float elapsedseconds, Map* stage, Player* target, bool recalculate = true) override;
	void Draw(const float interpolate) override;
	void Hit(Sutils::Direction direction); //if hit by player do stagger or blowback etc
	void Attack(Player* caster) override;
	void Move(Sutils::Direction direction);
	void SetState(Sutils::Direction state);
	void InitRoutine(std::vector<Vector2f> route, Map& stage);
	Vector2f GetSpriteCenter() const;
	Enemy * Clone() override;

private:
	void Translate(Vector2f movement);

	float m_AccumulatedSeconds;
	std::vector<Sutils::Direction> m_Routine;
	float m_InvincabilityTime;
	int m_CurrentStep;
	//Vector2I m_StartPosition; // for routine
};

