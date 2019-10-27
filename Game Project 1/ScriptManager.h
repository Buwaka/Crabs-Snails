#pragma once
#include "Script.h"
#include <deque>

class ScriptManager
{
public:

	ScriptManager();
	~ScriptManager();
	ScriptManager(const ScriptManager& other) = delete;
	ScriptManager& operator=(const ScriptManager& other) = delete;
	ScriptManager(ScriptManager&& other) = delete;
	ScriptManager& operator=(ScriptManager&& other) = delete;

	void Update(const float elapsedSec);
	void Add(Script* script, bool priority = false);
	void Stop(Script::ScriptType type);

	void Clean();



private:
	std::deque <Script*> m_Scripts;
};

