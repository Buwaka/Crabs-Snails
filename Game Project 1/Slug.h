#pragma once
#include "Enemy.h"
#include <string>
#include <vector>
#include "utils.h"
#include "Map.h"

class Slug : public Enemy
{
public:
	Slug(Vector2f position, std::string pathtosprite, std::string pathtotrail, EnemyManager* manager, int tilesize = 32, float speed = 1, int power = 1);
	Slug(Vector2f position, std::shared_ptr<Texture> sprite, std::shared_ptr<Texture> trail, EnemyManager* manager, int tilesize = 32, float speed = 1, int power = 1);
	~Slug();
	Slug(const Slug& other); // copy constructor
	Slug(Slug&& other) = delete; // move constructor
	Slug& operator=(const Slug& other); // copy assignment
	Slug& operator=(Slug&& other) = delete; // move assignment


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

	std::shared_ptr<Texture> m_trail;
	std::vector<Rectf> m_TrailFrames;
	float m_AccumulatedSeconds;
	std::vector<Sutils::Direction> m_Routine;
	float m_InvincabilityTime;
	int m_CurrentStep;
	Sutils::Direction m_LastState;
	//Vector2I m_StartPosition; // for routine
};

