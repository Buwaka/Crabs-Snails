#pragma once
#include "Vector2f.h"
#include "Texture.h"
#include "Map.h"
#include <vector>
#include <memory>

class Player;
class EnemyManager;

class Enemy
{
public:


	Enemy();
	virtual ~Enemy();

	virtual void Update(const float elapsedseconds, Map* stage, Player* target, bool recalculate = true) = 0;
	virtual void Draw(const float interpolate) = 0;
	virtual void Hit(Sutils::Direction direction) = 0;
	virtual void Attack(Player* caster) = 0;
	virtual Enemy* Clone() = 0;

	virtual Vector2f GetPosition() const;
	virtual void SetPosition(Point2f destination);

	void DrawHealthBar() const;

	bool Complete();

	Rectf GetEnemyRect() const;
	Rectf GetEnemyHitbox() const;
	int GetHealth() const;
	

protected:
	Vector2f m_Target;
	int m_DistanceToTarget; //heuristic
	Vector2f m_Movement;
	Vector2f m_DrawPosition, m_Position, m_LastPosition; // Drawposition is for draw and interaction, position is for update and movement
	std::shared_ptr<Texture> m_sprite;
	int m_Tilesize;
	Sutils::Direction m_CurrentState;
	std::vector<std::vector<Rectf>> m_Frames;
	int m_Frame, m_MaxFrames;
	EnemyManager* m_pEnemyManager;

	float m_Speed; //in tiles/update
	int m_Power;
	int m_Health, m_MaxHealth;

	bool m_IsHit;
	bool m_Visible;
};

