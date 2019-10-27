#include "stdafx.h"
#include "TaskAnimation.h"
#include "utils.h"


TaskAnimation::TaskAnimation(std::string path, Rectf* position, int FramesPerUpdate, float end, float start, Task::Layer layer) :
	m_Sprite{ path },
	m_Position{ position },
	m_Tilesize{ 0,0, position->width, position->height },
	m_End{ end },
	m_Start{ start },
	m_FramesPerUpdate{ FramesPerUpdate },
	m_Layer{layer}
{
	m_OffsetX = 0;
	m_OffsetY = 0;
	m_CurrentFrame = 0;
	m_LastFrame = 0;
	m_AccumulatedSeconds = 0;
	m_Complete = false;

	float totalTileX = (m_Tilesize.width + m_OffsetX);
	float totalTileY = (m_Tilesize.height + m_OffsetY);
	int columns = (int) std::floor(m_Sprite.GetWidth() / totalTileX);
	int rows = (int) std::floor(m_Sprite.GetHeight() / totalTileY);
	m_TotalFrames = rows * columns;


}


TaskAnimation::~TaskAnimation()
{
}

void TaskAnimation::Update(float elaspedSeconds)
{
	m_LastFrame = m_CurrentFrame;
	m_CurrentFrame += m_FramesPerUpdate;
	m_AccumulatedSeconds += elaspedSeconds;

	if (m_AccumulatedSeconds > m_End && m_End != -1)
	{
		m_Complete = true;
	}
}


void TaskAnimation::Draw(float interpolate, const Rectf window)
{
	if (m_AccumulatedSeconds > m_Start)
	{
		int frame = int(std::ceil(Sutils::lerpS(m_LastFrame, m_CurrentFrame, interpolate))) % m_TotalFrames;

		m_Sprite.Draw(*m_Position, GetFrame(frame));
	}

}

Task::Layer TaskAnimation::Type() const
{
	return Layer();
}

bool TaskAnimation::Complete() const
{
	return m_Complete;
}

Rectf TaskAnimation::GetFrame(int frame) const
{
	float totalTileX = (m_Tilesize.width + m_OffsetX);
	float totalTileY = (m_Tilesize.height + m_OffsetY);
	int columns = (int)std::floor(m_Sprite.GetWidth() / totalTileX);
	int rows = (int)std::floor(m_Sprite.GetHeight() / totalTileY);
	int total = rows * columns;

	float y = std::floorf((float) frame / columns) * totalTileY;
	float x = (frame % columns) * totalTileX;

	return Rectf(x,y, m_Tilesize.width, m_Tilesize.height);
}
