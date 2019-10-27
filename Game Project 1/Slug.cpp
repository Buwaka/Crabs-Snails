#include "stdafx.h"
#include "Slug.h"
#include "Pathfinding.h"
#include "Player.h"
#include "EnemyManager.h"



Slug::Slug(Vector2f  position, std::shared_ptr<Texture> sprite, std::shared_ptr<Texture> trail, EnemyManager* manager, int tilesize, float speed, int power)
{
	m_pEnemyManager = manager;
	m_LastPosition = m_DrawPosition = m_Position = position;
	m_Speed = speed;
	m_Power = power;
	m_Tilesize = tilesize;
	m_sprite = sprite;
	m_trail = trail;
	m_Movement = {};
	m_AccumulatedSeconds = 0;
	m_InvincabilityTime = 1.0f;

	m_CurrentState = Sutils::Direction::Up;
	m_Frame = 0;
	m_MaxFrames = (int) std::floor(m_sprite->GetWidth() / m_Tilesize);

	m_TrailFrames.resize(Sutils::Direction::size);
	m_TrailFrames[Sutils::Direction::Down] = Rectf{ 0, 0, (float)m_Tilesize, (float)m_Tilesize };
	m_TrailFrames[Sutils::Direction::Left] = Rectf{ 0, 32, (float)m_Tilesize, (float)m_Tilesize };
	m_TrailFrames[Sutils::Direction::Right] = Rectf{ 0, 64, (float)m_Tilesize, (float)m_Tilesize };
	m_TrailFrames[Sutils::Direction::Up] = Rectf{ 0, 96, (float)m_Tilesize, (float)m_Tilesize };

	m_Frames.resize(Sutils::Direction::size);
	for (int i = 0; i < Sutils::Direction::size; i++)
	{
		m_Frames[i].resize(m_MaxFrames);
		for (int j = 0; j < m_MaxFrames; j++)
		{
			m_Frames[i][j] = Rectf{ (float)j * m_Tilesize, float((i + 1) * m_Tilesize), (float)m_Tilesize, (float)m_Tilesize };
		}
	}

}

Slug::Slug(Vector2f  position, std::string pathtosprite, std::string pathtotrail, EnemyManager* manager, int tilesize, float speed, int power)
{
	m_pEnemyManager = manager;
	m_LastPosition = m_DrawPosition = m_Position = position;
	m_Speed = speed;
	m_Power = power;
	m_Tilesize = tilesize;
	m_sprite = std::make_shared<Texture>(pathtosprite);
	m_trail = std::make_shared<Texture>(pathtotrail);
	m_AccumulatedSeconds = 0;
	m_InvincabilityTime = 1.0f;
	m_MaxHealth = m_Health = 3;

	m_CurrentState = Sutils::Direction::Up;
	m_Frame = 0;
	m_MaxFrames = (int)std::floor(m_sprite->GetWidth() / m_Tilesize);

	m_TrailFrames.resize(Sutils::Direction::size);
	m_TrailFrames[Sutils::Direction::Down] = Rectf{ 0, 0, (float)m_Tilesize, (float)m_Tilesize };
	m_TrailFrames[Sutils::Direction::Left] = Rectf{ 0, 32, (float)m_Tilesize, (float)m_Tilesize };
	m_TrailFrames[Sutils::Direction::Right] = Rectf{ 0, 64,(float)m_Tilesize, (float)m_Tilesize };
	m_TrailFrames[Sutils::Direction::Up] = Rectf{ 0, 96, (float)m_Tilesize, (float)m_Tilesize };

	m_Frames.resize(Sutils::Direction::size);
	for (int i = 0; i < Sutils::Direction::size; i++)
	{
		m_Frames[i].resize(m_MaxFrames);
		for (int j = 0; j < m_MaxFrames; j++)
		{
			m_Frames[i][j] = Rectf{ (float)j * m_Tilesize, float((i + 1) * m_Tilesize), (float)m_Tilesize, (float)m_Tilesize };
		}
	}
}

Slug::~Slug()
{

}

Slug::Slug(const Slug & other)
{
	m_AccumulatedSeconds = 0;
	m_Routine = {};
	m_InvincabilityTime = 0;
	m_CurrentStep = 0;

	m_DistanceToTarget = 0; //heuristic
	m_Movement = {};
	m_DrawPosition = other.m_DrawPosition;
	m_Position = other.m_Position;
	m_LastPosition = other.m_LastPosition; // Drawposition is for draw and interaction, position is for update and movement
	m_sprite = other.m_sprite;
	m_trail = other.m_trail;
	m_Frames = other.m_Frames;
	m_TrailFrames = other.m_TrailFrames;
	m_Tilesize = other.m_Tilesize;
	m_CurrentState = other.m_CurrentState;
	m_Frame = 0;
	m_MaxFrames = other.m_MaxFrames;
	m_pEnemyManager = other.m_pEnemyManager;

	m_Speed = other.m_Speed; //in tiles/update
	m_Power = other.m_Power;
	m_Health = other.m_Health;
	m_MaxHealth = other.m_MaxHealth;

	m_IsHit = false;
	m_Visible = true;
}

Slug & Slug::operator=(const Slug & other)
{
	m_AccumulatedSeconds = 0;
	m_Routine = {};
	m_InvincabilityTime = 0;
	m_CurrentStep = 0;

	m_DistanceToTarget = 0; //heuristic
	m_Movement = {};
	m_DrawPosition = other.m_DrawPosition;
	m_Position = other.m_Position;
	m_LastPosition = other.m_LastPosition; // Drawposition is for draw and interaction, position is for update and movement
	m_sprite = other.m_sprite;
	m_trail = other.m_trail;
	m_Frames = other.m_Frames;
	m_TrailFrames = other.m_TrailFrames;
	m_Tilesize = other.m_Tilesize;
	m_CurrentState = other.m_CurrentState;
	m_Frame = 0;
	m_MaxFrames = other.m_MaxFrames;
	m_pEnemyManager = other.m_pEnemyManager;

	m_Speed = other.m_Speed; //in tiles/update
	m_Power = other.m_Power;
	m_Health = other.m_Health;
	m_MaxHealth = other.m_MaxHealth;

	m_IsHit = false;
	m_Visible = true;
	return *this;
}

/*Slug & Slug::operator=(Slug && other)
{
	if (this != &other) // prevent self-move
	{
		*this = other;
	}
	return *this;
}*/

void Slug::Update(const float elapsedseconds, Map* stage, Player* target, bool recalculate)
{
	m_LastPosition = m_Position;

	if (m_Position == target->GetPosition())
	{
		target->Hit(m_CurrentState);
	}

	if (m_IsHit)
	{
		m_Visible = !m_Visible;
		m_AccumulatedSeconds += elapsedseconds;
		if (m_AccumulatedSeconds >= m_InvincabilityTime)
		{
			m_IsHit = false;
			m_Visible = true;
			m_AccumulatedSeconds = 0;
		}
	}
	else
	{
		if (!m_Routine.empty())
		{
			Move(m_Routine[m_CurrentStep]);
		}
		m_CurrentStep++;

		if (recalculate)
		{
			int random = rand() % (int)Sutils::Heuristic::Heuristicsize;
			m_Routine = Astar(stage->GetGrid(), m_Position, target->GetPosition(), (Sutils::Heuristic) random);
			//m_Routine = Dijkstra(stage->GetGrid(), m_Position, target->GetPosition());

			m_CurrentStep = 0;
		}


		if (m_CurrentStep >= (int) m_Routine.size())
		{
		//	Sutils::ReverseRoute(&m_Routine);
			m_CurrentStep = 0;
		}
	}

	if (m_Movement.x != 0 || m_Movement.y != 0)
	{
		m_Frame = (m_Frame + 1) % m_MaxFrames;
		Grid temp = m_pEnemyManager->GetEnemyMap();
		if (!stage->IsCollission(GetSpriteCenter(), m_Movement, &temp))
		{
			Translate(m_Movement);
		}
		m_Movement = {};
	}




}

void Slug::Draw(const float interpolate)
{
	m_DrawPosition.x = Sutils::lerpS(m_LastPosition.x, m_Position.x, interpolate);
	m_DrawPosition.y = Sutils::lerpS(m_LastPosition.y, m_Position.y, interpolate);
	if (m_Visible)
	{
		m_trail->Draw(Rectf{ m_LastPosition.x, m_LastPosition.y, (float)m_Tilesize, (float)m_Tilesize }, m_TrailFrames[m_LastState]);
		m_trail->Draw(Rectf{ m_DrawPosition.x, m_DrawPosition.y, (float)m_Tilesize, (float)m_Tilesize }, m_TrailFrames[m_LastState]);
		m_sprite->Draw(Rectf{ m_DrawPosition.x, m_DrawPosition.y, (float)m_Tilesize, (float)m_Tilesize }, m_Frames[m_CurrentState][m_Frame]);

		DrawHealthBar();
	}

}

void Slug::Hit(Sutils::Direction direction)
{
	if (!m_IsHit)
	{
		Move(direction);

		//std::cout << "Hit!!!!!!" << std::endl;
		m_IsHit = true;
		m_Health--;
	}

}

void Slug::Attack(Player* caster)
{

}

void Slug::Move(Sutils::Direction direction)
{
	switch (direction)
	{
	case Sutils::Up: m_Movement.y += m_Tilesize;
		SetState(Sutils::Direction::Up);
		break;
	case Sutils::Down: m_Movement.y -= m_Tilesize;
		SetState(Sutils::Direction::Down);
		break;
	case Sutils::Left: m_Movement.x -= m_Tilesize;
		SetState(Sutils::Direction::Left);
		break;
	case Sutils::Right: m_Movement.x += m_Tilesize;
		SetState(Sutils::Direction::Right);
		break;
	}
}

void Slug::SetState(Sutils::Direction state)
{

	if (state != m_CurrentState)
	{
		m_Frame = 0;
	}
	m_LastState = m_CurrentState;
	m_CurrentState = state;

	
}

void Slug::Translate(Vector2f movement)
{
	m_Position += movement;
}

Vector2f Slug::GetSpriteCenter() const
{
	return Vector2f{ m_Position.x + (m_Tilesize / 2), m_Position.y + (m_Tilesize / 2) };
}

Enemy * Slug::Clone()
{
	return new Slug(*this);
}

void Slug::InitRoutine(std::vector<Vector2f> route, Map& stage)
{
	
	if (route.size() > 0)
	{
		std::vector<Sutils::Direction> start = Astar(stage.GetGrid(), m_Position, route.front());
		m_Routine.reserve(start.size());
		m_Routine.insert(m_Routine.end(), start.begin(), start.end());

		for (size_t i = 1; i < route.size(); i++)
		{
			std::vector<Sutils::Direction> temp = Astar(stage.GetGrid(), route[i - 1], route[i]);

			m_Routine.reserve(m_Routine.size() + temp.size());
			m_Routine.insert(m_Routine.end(), temp.begin(), temp.end());
		}
	}


	//debug stuff
	/*std::vector<Sutils::Direction> To = Astar(stage.GetGrid(), { 864 ,864 }, { 864, 256 });
	std::vector<Sutils::Direction> back = Astar(stage.GetGrid(), { 864, 256 }, { 864, 864 });
	//std::reverse(back.begin(), back.end());
	
	m_Routine.reserve(To.size() + back.size());
	m_Routine.insert(m_Routine.end(), To.begin(), To.end());
	m_Routine.insert(m_Routine.end(), back.begin(), back.end());*/
}
