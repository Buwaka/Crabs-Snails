#pragma once
#include "Task.h"
#include <deque>

class TaskManager
{
public:
	TaskManager(const Window* window );
	~TaskManager();

	TaskManager(const TaskManager& other) = delete;
	TaskManager& operator=(const TaskManager& other) = delete;
	TaskManager(TaskManager&& other) = delete;
	TaskManager& operator=(TaskManager&& other) = delete;


	Rectf GetWindowDimension() const;

	void Draw(Task::Layer type, const float interpolate) const;
	void Update(const float elapsedSec);
	void Add(Task* task, bool priority = false);
	int Size() const;
	void Clean();



private:
	const Window * m_pWindow;
	std::deque <Task*> m_Tasks;


};

