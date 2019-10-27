#include "stdafx.h"
#include "TaskManager.h"


TaskManager::TaskManager(const Window* window)
{
	m_pWindow = window;
}


TaskManager::~TaskManager()
{
	for (Task* task : m_Tasks)
	{
		delete task;
	}
}

Rectf TaskManager::GetWindowDimension() const
{
	return Rectf(0, 0, m_pWindow->width, m_pWindow->height);
}

void TaskManager::Draw(Task::Layer type, const float interpolate) const
{
	int i = 5;
	if (m_Tasks.size() > 1)
	{
		i = 5;
	}


	for (Task* task : m_Tasks)
	{
		if (task->Type() == type)
			task->Draw(interpolate, GetWindowDimension()); 
	}
}

void TaskManager::Update(const float elapsedSec)
{
	for (Task* task : m_Tasks)
	{
		task->Update(elapsedSec);
	}
	Clean();
}

void TaskManager::Add(Task * task, bool priority)
{
	if (priority)
		m_Tasks.push_front(task);
	else
		m_Tasks.push_back(task);
}

int TaskManager::Size() const
{
	return(int)m_Tasks.size();
}

void TaskManager::Clean()
{
	//clean tasks
	for (size_t i = 0; i < m_Tasks.size(); i++)
	{
		if (m_Tasks[i]->Complete())
		{
			delete m_Tasks[i];
			m_Tasks.erase(m_Tasks.begin() + i);
		}
	}
}


