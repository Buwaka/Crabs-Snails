#include "stdafx.h"
#include "ScriptManager.h"


ScriptManager::ScriptManager()
{
}


ScriptManager::~ScriptManager()
{
	for (Script* script : m_Scripts)
	{
		delete script;
	}
}

void ScriptManager::Update(const float elapsedSec)
{
	for (Script* script : m_Scripts)
	{
		script->Check(elapsedSec);
	}
}

void ScriptManager::Clean()
{
	for (size_t i = 0; i < m_Scripts.size(); i++)
	{
		if (m_Scripts[i]->Complete())
		{
			delete m_Scripts[i];
			m_Scripts.erase(m_Scripts.begin() + i);
		}
	}
}

void ScriptManager::Stop(Script::ScriptType type)
{
	for (size_t i = 0; i < m_Scripts.size(); i++)
	{
		if (m_Scripts[i]->Type() == type)
		{
			delete m_Scripts[i];
			m_Scripts.erase(m_Scripts.begin() + i);
		}
	}
}

void ScriptManager::Add(Script* script, bool priority)
{
	if (priority)
	{
		m_Scripts.push_front(script);
	}
	else
	{
		m_Scripts.push_back(script);
	}
}

