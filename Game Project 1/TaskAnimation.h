#pragma once
#include "Task.h"
#include "Texture.h"
class TaskAnimation : public Task
{
public:
	TaskAnimation(std::string path, Rectf* position, int FramesPerUpdate = 1, float end = -1, float start = 0, Task::Layer layer = Task::Layer::objects);
	~TaskAnimation();

	TaskAnimation(const TaskAnimation& other) = delete;
	TaskAnimation& operator=(const TaskAnimation& other) = delete;
	TaskAnimation(TaskAnimation&& other) = delete;
	TaskAnimation& operator=(TaskAnimation&& other) = delete;

	void Update(float elaspedSeconds) override;
	void Draw(float interpolate, const Rectf window) override;

	Layer Type() const override;
	bool Complete() const override;
private:
	float m_Start, m_End, m_Opacity, m_AccumulatedSeconds;
	Texture m_Sprite;
	Rectf* m_Position, m_Tilesize;
	int m_OffsetX, m_OffsetY, m_TotalFrames, m_FramesPerUpdate;
	unsigned int m_CurrentFrame, m_LastFrame;
	bool m_Complete;

	Task::Layer m_Layer = Task::Layer::objects;

	Rectf GetFrame(int frame) const;

};

