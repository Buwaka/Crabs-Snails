#include "stdafx.h"
#include "Camera.h"
#include <algorithm>
#include "utils.h"





Camera::Camera() 
{

}

Camera::~Camera()
{

}

void Camera::Init(const Window * window, Vector2f startposition, float scale, Rectf Mapdimension)
{
	m_pWindow = window;
	m_Position = startposition;
	m_MapDimension = Mapdimension;
	m_scale = scale;
	CalculateViewPort();
	m_LastViewPort = m_ViewPort;
}

void Camera::Update(Vector2f movement)
{
	m_LastViewPort = m_ViewPort;
	Translate(movement);
	CalculateViewPort();
}

void Camera::Update(Point2f position)
{
	m_LastViewPort = m_ViewPort;
	SetPosition(position);
	CalculateViewPort();
}

Rectf Camera::GetViewPort() const
{
	return m_ViewPort;
}

Vector2f Camera::GetViewPortPoint() const
{
	return Vector2f{ m_ViewPort.left, m_ViewPort.bottom };
}

Rectf Camera::GetInterpolatedViewPortRectf(const float interpolate) const
{
	float left, bottom, width, height;
	bottom = Sutils::lerpS(m_LastViewPort.bottom, m_ViewPort.bottom, interpolate);
	left   = Sutils::lerpS(m_LastViewPort.left  , m_ViewPort.left  , interpolate);
	width  = Sutils::lerpS(m_LastViewPort.width , m_ViewPort.width , interpolate);
	height = Sutils::lerpS(m_LastViewPort.height, m_ViewPort.height, interpolate);
	return Rectf(left, bottom, width, height);
}

Point2f Camera::GetInterpolatedViewPortPoin2f(const float interpolate) const
{
	float left, bottom;
	bottom = Sutils::lerpS(m_LastViewPort.bottom, m_ViewPort.bottom, interpolate);
	left = Sutils::lerpS(m_LastViewPort.left, m_ViewPort.left, interpolate);
	return Point2f(left, bottom);
}

void Camera::Translate(Vector2f movement)
{
	m_Position += movement;
}

void Camera::SetPosition(Point2f pos)
{
	m_Position = pos;
}

Vector2f Camera::GetMousePositionInWorld(const SDL_MouseButtonEvent & e)
{
	float left   =  std::min(std::max(0.f, m_ViewPort.left  + (e.x / m_scale)) , m_MapDimension.width);
	float bottom =  std::min(std::max(0.f, m_ViewPort.bottom  + ((m_pWindow->height - e.y) / m_scale)), m_MapDimension.height);

	return Vector2f(left, bottom);
}

void Camera::CalculateViewPort()
{
	float left   =  std::min(std::max(0.f,       m_Position.x - (m_pWindow->width / m_scale / 2))			      , m_MapDimension.width - (m_pWindow->width / m_scale));
	float bottom =  std::min(std::max(0.f,       (m_Position.y - (m_pWindow->height / m_scale / 2)))			     , m_MapDimension.height - (m_pWindow->height / m_scale));
	//float width  =	std::min(std::max(0.f, m_MapDimension.width  - (m_Position.x - (m_pWindow->width  / 2))) , m_pWindow->width);
	//float height =	std::min(std::max(0.f, m_MapDimension.height - (m_Position.y - (m_pWindow->height / 2))), m_pWindow->height);

	m_ViewPort = Rectf{ left, bottom, m_pWindow->width / m_scale, m_pWindow->height / m_scale };
	//m_ViewPort = Rectf{ m_Position.x - (m_pWindow->width / 2), (m_Position.y - (m_pWindow->height / 2)), m_pWindow->width, m_pWindow->height };
}
