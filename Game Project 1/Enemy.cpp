#include "stdafx.h"
#include "Enemy.h"
#include "utils.h"


Enemy::Enemy()
{
	m_Health = 1;
	m_IsHit = false;
	m_Visible = true;
}


Enemy::~Enemy()
{
}

Vector2f Enemy::GetPosition() const
{
	return m_Position;
}

void Enemy::SetPosition(Point2f destination)
{
	m_DrawPosition = m_Position = m_LastPosition = destination;
}

void Enemy::DrawHealthBar() const
{
	const int healthbarMargin = 1;

	//outer rect
	utils::SetColor(Color4f{ 0.9f,0.9f,0.9f,1.0f });
	utils::FillRect(m_DrawPosition.x + ((float)m_Tilesize / 2), m_DrawPosition.y - ((float)m_Tilesize / 4), ((float)m_Tilesize / 2), ((float)m_Tilesize / 5));

	//inner rect
	utils::SetColor(Color4f{ 1.f,0.f,0.f,1.0f });
	utils::FillRect(m_DrawPosition.x + ((float)m_Tilesize / 2) + healthbarMargin, m_DrawPosition.y - ((float)m_Tilesize / 4) + healthbarMargin,
		(((float)m_Tilesize / 2) - (healthbarMargin * 2)) *  ((float)m_Health / m_MaxHealth), ((float)m_Tilesize / 5) - (healthbarMargin * 2));
}

bool Enemy::Complete()
{
	return (m_Health <= 0);
}

Rectf Enemy::GetEnemyRect() const
{
	return Rectf(m_Position.x, m_Position.y, m_sprite->GetWidth() / m_MaxFrames, m_sprite->GetHeight() / Sutils::Direction::size);
}

Rectf Enemy::GetEnemyHitbox() const
{
	return Rectf(m_DrawPosition.x, m_DrawPosition.y, m_sprite->GetWidth() / m_MaxFrames, m_sprite->GetHeight() / Sutils::Direction::size);
}

int Enemy::GetHealth() const
{
	return m_Health;
}




