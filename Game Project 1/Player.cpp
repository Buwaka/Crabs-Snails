#include "stdafx.h"
#include "Player.h"
#include <algorithm>
#include "utils.h"
#include "WeaponManager.h"
#include "SoundManager.h"
#include "Weapon.h"






Player::Player()
{
}

Player::~Player()
{
	//delete m_pSpirte;
}

void Player::Init(std::string pathSprite, int tilesize, Point2f startposition, TaskManager* taskmanager, WeaponManager* weaponmanager, SoundManager* soundmanager, const Window* window)
{
	m_pWeaponManager = weaponmanager;
	m_pTaskManager = taskmanager;
	m_pSoundManager = soundmanager;

	m_pWindow = window;
	m_pSpirte = std::make_shared<Texture>(pathSprite);
	m_Width = (int)m_pSpirte->GetWidth();
	m_Height = (int)m_pSpirte->GetHeight();
	m_CurrentDirection = Sutils::Direction::Down;
	m_pWeapon = m_pWeaponManager->GetDefaultWeapon();

	m_MaxFrames = (int)std::floor((float)m_Width / tilesize); 
	m_Tilesize = tilesize;
	m_Disabled = false;
	m_Visible = true;
	m_Invincable = false;
	m_IsHit = false;
	m_InvincabilityTime = 1.5f;
	m_MaxHealth = m_Health = 10;

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

void Player::Draw(const float interpolate, bool fixedView) const
{
	if (m_Visible)
	{

		if (fixedView)
		{
			float leftLerp = Sutils::lerpS(m_LastPosition.x, m_Position.x, interpolate);
			float bottomLerp = Sutils::lerpS(m_LastPosition.y, m_Position.y, interpolate);
			m_pSpirte->Draw(Rectf{ leftLerp, bottomLerp, (float)m_Tilesize, (float)m_Tilesize }, m_Frames[m_CurrentDirection][m_frame]);
		}
		else
		{
			float leftLerp = Sutils::lerpS(m_LastPosition.x, m_Position.x, interpolate);
			float bottomLerp = Sutils::lerpS(m_LastPosition.y, m_Position.y, interpolate);

			if (!m_Disabled)
			{
				m_pWeapon->Draw(m_CurrentDirection, { leftLerp ,bottomLerp }, { leftLerp ,bottomLerp }, false);
			}


			m_pSpirte->Draw(Rectf{ leftLerp, bottomLerp, (float)m_Tilesize, (float)m_Tilesize }, m_Frames[m_CurrentDirection][m_frame]);

		}

		//debug stuff, hitpoint
		//utils::SetColor(Color4f{ 1.f,0.f,0.f,1.f });
		//utils::DrawPoint(GetSpriteCenter().ToPoint2f(), 5.0f);	


		//m_pSpirte->Draw(Rectf{ m_pWindow->width / 2,  m_pWindow->height / 2, (float)m_Tilesize, (float)m_Tilesize }, m_Frames[m_CurrentState][m_frame]);
	}

}

void Player::Update(Map* stage, const float elapsedSec)
{
	m_LastPosition = m_Position;

	if (m_IsHit)
	{
		m_Visible = !m_Visible;
		m_AccumulatedSeconds += elapsedSec;
		if (m_AccumulatedSeconds >= m_InvincabilityTime)
		{
			m_IsHit = false;
			m_Invincable = false;
			m_Visible = true;
			m_Disabled = false;
			m_AccumulatedSeconds = 0;
		}
	}


	if (!m_Disabled)
	{
		CheckInput(elapsedSec);
	}

	//to prevent frame from continuieng in idle
	if (m_movement.x != 0 || m_movement.y != 0)
	{
		if (!m_IsHit)
		{
			m_frame = (m_frame + 1) % m_MaxFrames;
		}
		if (!stage->IsCollission(GetPosition(), m_movement))
		{
			Translate(m_movement);
		}
		m_movement = {};
	}

	if (m_IsHit)
	{
		//m_Disabled = false;
	}
	
}

void Player::Attack(Sutils::Direction direction)
{
	if (!m_Disabled)
	{
		m_pWeapon->Attack(this, direction, 0.01f);
		
		switch (m_pWeapon->GetType())
		{
		case WeaponManager::sword: 
			m_pSoundManager->PlaySound(SoundManager::sword);
			break;
		case WeaponManager::bow:
			m_pSoundManager->PlaySound(SoundManager::bow);
			break;
		}

		m_movement = {};
		//m_Disabled = true;
	}

}

void Player::Attack()
{
	Attack(m_CurrentDirection);
}

void Player::Hit(Sutils::Direction direction)
{
	if (!m_Invincable)
	{
		m_Disabled = true;
		m_Invincable = true;
		m_IsHit = true;
		m_Health--;
		Move(direction);
		m_pSoundManager->PlaySound(SoundManager::punch);
	}
}

Vector2f Player::GetSpriteCenter() const
{
	return Vector2f{ m_Position.x + (m_Tilesize / 2), m_Position.y + (m_Tilesize / 2) };
}

Sutils::Direction Player::GetDirection() const
{
	return m_CurrentDirection;
}

void Player::SetState(Sutils::Direction direction)
{
	if (direction != m_CurrentDirection)
	{
		m_frame = 0;
	}
	m_CurrentDirection = direction;
	
}

void Player::Translate(Vector2f vector)
{
	m_Position += vector;
}

void Player::Move(Sutils::Direction direct)
{
	switch (direct)
	{
	case Sutils::Up: m_movement.y += m_Tilesize;
	
		break;
	case Sutils::Down: m_movement.y -= m_Tilesize;
	
		break;
	case Sutils::Left: m_movement.x -= m_Tilesize;
	
		break;
	case Sutils::Right: m_movement.x += m_Tilesize;
		
		break;
	}

	if (!m_IsHit)
	{
		SetState(direct);
	}

}

void Player::SetPosition(Vector2f position)
{
	m_Position = position;
	m_LastPosition = position;
}

void Player::ChangeWeapon(int direction)
{
	int newtype = std::abs(m_pWeapon->GetType() + direction) % WeaponManager::Weapons::size;
	m_pWeapon = m_pWeaponManager->GetWeapon((WeaponManager::Weapons) newtype);
}

void Player::ChangeWeapon(WeaponManager::Weapons weapon)
{
	m_pWeapon = m_pWeaponManager->GetWeapon(weapon);
}

Weapon* Player::GetWeapon() const
{
	return m_pWeapon;
}

int Player::GetHealth() const
{
	return m_Health;
}

int Player::GetMaxHealth() const
{
	return m_MaxHealth;
}

void Player::CheckInput(const float elapsedSec)
{
	
	const Uint8 *pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_RIGHT])
	{
		//std::cout << "Right arrow key is down\n";
		m_movement += Vector2f{ (float)m_Tilesize, 0 };
		SetState(Sutils::Right);
	}
	else if (pStates[SDL_SCANCODE_LEFT])
	{
		//std::cout << "Left arrow keys is down\n";
		m_movement += Vector2f{ (float)-m_Tilesize, 0 };
		SetState(Sutils::Left);
	}
	else if (pStates[SDL_SCANCODE_UP])
	{
		//std::cout << "up arrow keys is down\n";
		m_movement += Vector2f{ 0, (float)m_Tilesize };
		SetState(Sutils::Up);
	}
	else if (pStates[SDL_SCANCODE_DOWN])
	{
		//std::cout << "down arrow keys is down\n";
		m_movement += Vector2f{ 0, (float)-m_Tilesize };
		SetState(Sutils::Down);
	}
}

void Player::DisableInput()
{
	m_Disabled = true;
}

void Player::EnableInput()
{
	m_Disabled = false;
}

bool Player::IsDisabled() const
{
	return m_IsHit || m_Disabled;
}

void Player::Hide()
{
	m_Visible = false;
}

void Player::Show()
{
	m_Visible = true;
}

Vector2f Player::GetPosition() const
{
	return m_Position;
}

