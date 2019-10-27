#pragma once
#include "Task.h"
#include "Texture.h"
#include <memory>
class TaskFade : public Task
{
public:
	TaskFade(float end, Color4f endColor, float start = 0, Color4f startColor = {0,0,0,0});
	~TaskFade();

	TaskFade(const TaskFade& other) = delete;
	TaskFade& operator=(const TaskFade& other) = delete;
	TaskFade(TaskFade&& other) = delete;
	TaskFade& operator=(TaskFade&& other) = delete;

	void Update(float elaspedSeconds) override;
	void Draw(float interpolate, const Rectf window) override;

	Layer Type() const override;
	bool Complete() const override;

private:
	float m_Start{}, m_End{}, m_AccumulatedSeconds{}, m_lastseconds{};
	std::shared_ptr<Texture> m_StartTexture, m_EndTexture;
	std::shared_ptr<Color4f> m_StartColor, m_EndColor;
	bool m_Complete = false;

	const Layer type = Layer::effects;

};

