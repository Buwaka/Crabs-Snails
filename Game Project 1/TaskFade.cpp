#include "stdafx.h"
#include "TaskFade.h"
#include <algorithm>
#include "utils.h"



TaskFade::TaskFade(float end, Color4f endColor, float start, Color4f startColor)
{
	m_StartTexture = nullptr;
	m_EndTexture = nullptr;

	m_End = end;
	if (endColor.a > 0.f)
		m_EndColor = std::make_shared<Color4f>(endColor);
	else
		m_EndColor = nullptr;

	m_Start = start;
	if (startColor.a > 0.f)
		m_StartColor = std::make_shared<Color4f>(startColor);
	else
		m_StartColor = nullptr;

}

TaskFade::~TaskFade()
{

}

void TaskFade::Update(float elaspedSeconds)
{
	m_lastseconds = m_AccumulatedSeconds;
	m_AccumulatedSeconds += elaspedSeconds;
}

void TaskFade::Draw(float interpolate, const Rectf window)
{
	float progress = std::max(0.f, Sutils::lerpS(m_lastseconds, m_AccumulatedSeconds, interpolate) - m_Start) / m_End;

	//start
	if (m_StartTexture != nullptr)
	{
		glColor4f(1.0f, 1.0f, 1.0f, progress);
		m_StartTexture->Draw(window, Rectf{});
	}
	else if (m_StartColor != nullptr)
	{
		glColor4f(m_StartColor->r, m_StartColor->g, m_StartColor->b, m_StartColor->a * progress);
		utils::FillRect(window);
	}


	//end
	if (m_EndTexture != nullptr)
	{
		glColor4f(1.0f, 1.0f, 1.0f, (1 - progress));
		m_EndTexture->Draw(window, Rectf{});
	}
	else if (m_EndColor != nullptr)
	{
		glColor4f(m_EndColor->r, m_EndColor->g, m_EndColor->b, m_EndColor->a * (1 - progress));
		utils::FillRect(window);
	}

	if (progress >= 1.f)
	{
		m_Complete = true;
	}

}

Task::Layer TaskFade::Type() const
{
	return type;
}

bool TaskFade::Complete() const
{
	return m_Complete;
}


