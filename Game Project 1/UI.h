#pragma once

class Player;

class UI
{
public:
	UI(const Window* window, Player* player, int tilesize);
	~UI();
	UI(const UI& other) = delete;
	UI& operator=(const UI& other) = delete;
	UI(UI&& other) = delete;
	UI& operator=(UI&& other) = delete;

	void Draw(const int score) const;

private:
	const Window * m_pWindow;
	Player* m_pPlayer;
	int m_Tilesize;
	TTF_Font *m_Scorefont;
};

