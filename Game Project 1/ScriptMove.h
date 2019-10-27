#pragma once
#include "Script.h"
#include "Player.h"
#include <vector>
#include <memory>
#include "utils.h"
#include "Pathfinding.h"

class ScriptMove :	public Script
{
public:
	ScriptMove(Player* player, std::vector<Sutils::Direction>& directions);
	ScriptMove(Player* player, Point2f destination, Grid map);
	virtual ~ScriptMove();

	ScriptMove(const ScriptMove& other) = delete;
	ScriptMove& operator=(const ScriptMove& other) = delete;
	ScriptMove(ScriptMove&& other) = delete;
	ScriptMove& operator=(ScriptMove&& other) = delete;

	void Check(float elapsedSeconds) override;
	bool Complete() override;

	void Clean() override;

private:
	Player* m_pPlayer;
	std::vector<Sutils::Direction> m_Directions;
	void CheckInput();
	bool m_Complete;
	int m_Step;

};

