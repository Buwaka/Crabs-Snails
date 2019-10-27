#include "stdafx.h"
#include "TaskAttack.h"
#include <algorithm>


#define debug  false


TaskAttack::TaskAttack(Weapon* weapon, Player* caster, Sutils::Direction direction, std::vector<Enemy*>* enemypool, const float elapsedSec)
{
	m_pPlayer = caster;
	m_pWeapon = weapon;
	m_StartPosition = m_LastPosition = m_Position = caster->GetPosition().ToPoint2f();
	m_Direction = direction;
	m_pEnemypool = enemypool;
	m_AccumulatedSeconds = elapsedSec;
	m_LastElapsedSeconds = elapsedSec;
	m_Complete = false;


	/*std::vector<Rectf> temphit = m_pWeapon->GetHitbox();
	auto maxhitbox = [](Rectf& left, Rectf& right) -> bool
	{
		return std::max(left.width, left.height) < std::max(right.width, right.height);
	};

	auto max = std::max_element(temphit.begin(), temphit.end(), maxhitbox);

	int tile = m_pWeapon->GetTilesize();
	m_Length = (float(std::max(max->width, max->height) + tile) / tile) * (1 / ((float)m_pWeapon->GetSpeed() / 100));*/

	

}

TaskAttack::~TaskAttack()
{

}

void TaskAttack::Update(float elaspedSeconds)
{
		bool hit = false;
		m_AccumulatedSeconds += elaspedSeconds;
		m_LastElapsedSeconds = elaspedSeconds;

		m_LastPosition = m_Position;
		m_Complete = m_pWeapon->Update(m_pPlayer,m_StartPosition, &m_Position, m_Direction, m_AccumulatedSeconds);


		//translate hitbox to caster position
		std::vector<Rectf> translatedHitbox = m_pWeapon->GetHitbox();

		auto translate = [this](Rectf i) -> Rectf
		{
			Rectf temp;
			switch (m_Direction)
			{
			case Sutils::Up:    temp = { m_Position.x + i.left, m_Position.y + i.bottom, i.width, i.height };
								break;
			case Sutils::Down:  temp = { m_Position.x + i.left, m_Position.y - i.bottom, i.width, i.height };
								break;
			case Sutils::Left:  temp = { m_Position.x - i.bottom, m_Position.y + i.left, i.height, i.width };
								break;
			case Sutils::Right: temp = { m_Position.x + i.bottom, m_Position.y + i.left, i.height, i.width };
								break;
			}
			return  temp;
		};

		std::transform(translatedHitbox.begin(), translatedHitbox.end(), translatedHitbox.begin(), translate);


		//hit detection
		for (Enemy* enemy : *m_pEnemypool)
		{
			size_t i = 0;

			while (i < translatedHitbox.size() && !hit)
			{
				//hit als variabel om te voorkomen dat de enemy meerdere keren wordt geraakt in dezelfde update
				hit = utils::IsOverlapping(enemy->GetEnemyRect(), translatedHitbox[i]);
				if (hit)
				{
					enemy->Hit(m_Direction);
				}
				i++;
			}
			hit = false;

		}
	

}

void TaskAttack::Draw(float interpolate, const Rectf window)
{
	if (debug)
	{
		utils::SetColor(Color4f{ 1.0f,0,1.0f,1.0f });
		std::vector<Rectf> temp = m_pWeapon->GetHitbox();
		for (Rectf i : temp)
		{
			switch (m_Direction)
			{
			case Sutils::Up:    utils::FillRect({ m_Position.x + i.left, m_Position.y + i.bottom, i.width, i.height });
				break;
			case Sutils::Down:  utils::FillRect({ m_Position.x + i.left, m_Position.y - i.bottom, i.width, i.height });
				break;
			case Sutils::Left:  utils::FillRect({ m_Position.x - i.bottom, m_Position.y + i.left, i.height, i.width });
				break;
			case Sutils::Right: utils::FillRect({ m_Position.x + i.bottom, m_Position.y + i.left, i.height, i.width });
				break;
			}
		}
	}

   	m_pWeapon->Draw(m_Direction, m_LastPosition.ToPoint2f(), m_Position.ToPoint2f(), true, interpolate);

}

Task::Layer TaskAttack::Type() const
{
	return m_Layer;
}

bool TaskAttack::Complete() const
{
	return m_Complete;
}
