#include "stdafx.h"
#include "UI.h"
#include "utils.h"
#include "Player.h"
#include "Weapon.h"



UI::UI(const Window* window, Player* player, int tilesize)
{
	m_pWindow = window;
	m_Tilesize = tilesize;
	m_pPlayer = player;

	m_Scorefont = TTF_OpenFont("resources/framd.ttf", 24);
}


UI::~UI()
{
	TTF_CloseFont(m_Scorefont);
}

void UI::Draw(const int score) const
{

	const int healthbarMargin = 4;

	//outer rect
	utils::SetColor(Color4f{ 0.9f,0.9f,0.9f,1.0f });
	utils::FillRect((float)m_Tilesize, m_pWindow->height - (2.5f * (float)m_Tilesize), m_pWindow->width / 4, (float)m_Tilesize);

	//inner rect
	utils::SetColor(Color4f{1.f,0.f,0.f,1.0f });
	utils::FillRect((float)(m_Tilesize + healthbarMargin), m_pWindow->height - (2.5f * (float) m_Tilesize) + (float)healthbarMargin,
		((m_pWindow->width / 4) - ((float)healthbarMargin * 2)) * ((float)m_pPlayer->GetHealth() / m_pPlayer->GetMaxHealth()), (float)m_Tilesize - ((float)healthbarMargin * 2));

	//current weapon
	Point2f weaponpos = { m_pWindow->width - (2 * m_Tilesize), m_pWindow->height - (2 * m_Tilesize) };
	//outer box
	utils::SetColor(Color4f{ 0.396f,0.263f,0.129f,1.0f });
	utils::FillRect(weaponpos, m_Tilesize * 1.5f, m_Tilesize * 1.5f);
	//weapon itself
	m_pPlayer->GetWeapon()->DrawIcon(weaponpos, 1.5f);

	
	//Highscore
	std::string text = "Score: ";
	text.append(std::to_string(score));

	Texture scr(text, m_Scorefont, Color4f{ 0.f,0.f,0.f,1.f });
	scr.Draw({ m_pWindow->width / 2, (m_pWindow->height / 16 * 15) - (scr.GetWidth() / 2), scr.GetWidth(), scr.GetHeight() }, {});
	
}