#pragma once
#include "Texture.h"
#include "Vector2f.h"
#include "utils.h"
#include "Map.h"
#include "WeaponManager.h"

#include <vector>
#include <memory>

class TaskManager; //forward declaratie
class SoundManager;


class Player
{
public:

	Player();
	~Player();
	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;
	Player(Player&& other) = delete;
	Player& operator=(Player&& other) = delete;

	void Init(std::string pathSprite, int tilesize, Point2f startposition, TaskManager* taskmanager, WeaponManager* weaponmanager, SoundManager* soundmanager, const Window* window);
	void Draw(const float interpolate, bool fixedView = false) const;
	void Update(Map* stage, float elapsedSec);
	void Attack(Sutils::Direction direction);
	void Attack();
	void Hit(Sutils::Direction direction);
	void SetState(Sutils::Direction direction);
	void Translate(Vector2f vector);
	void Move(Sutils::Direction direct);
	void SetPosition(Vector2f position);
	void ChangeWeapon(int direction);
	void ChangeWeapon(WeaponManager::Weapons weapon);
	Weapon* GetWeapon() const;
	int GetHealth() const;
	int GetMaxHealth() const;
	void DisableInput();
	void EnableInput();
	bool IsDisabled() const;
	void Hide();
	void Show();
	Vector2f GetPosition() const;
	Vector2f GetSpriteCenter() const;
	Sutils::Direction GetDirection() const;


	int m_Width, m_Height, m_Tilesize;

private:
	bool m_Disabled, m_Visible, m_Invincable, m_IsHit;
	float m_InvincabilityTime, m_AccumulatedSeconds;

	std::shared_ptr<Texture> m_pSpirte;
	std::vector<std::vector<Rectf>> m_Frames;
	Sutils::Direction m_CurrentDirection;
	int m_MaxFrames, m_frame{};


	Vector2f m_Position{}, m_LastPosition{}, m_movement{};
	Weapon* m_pWeapon;


	const Window * m_pWindow;
	Rectf m_Camera;
	TaskManager* m_pTaskManager;
	WeaponManager* m_pWeaponManager;
	SoundManager* m_pSoundManager;

	int m_Health, m_MaxHealth;


	void CheckInput(const float elapsedSec);

};

