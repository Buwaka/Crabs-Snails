#pragma once
#include "Vector2f.h"
class Camera
{
public:
	Camera();
	~Camera();
	Camera(const Camera& other) = delete;
	Camera& operator=(const Camera& other) = delete;
	Camera(Camera&& other) = delete;
	Camera& operator=(Camera&& other) = delete;

	void Init(const Window* window, Vector2f startposition, float scale, Rectf Mapdimension);
	void Update(Vector2f movement);
	void Update(Point2f position);
	Rectf GetViewPort() const;
	Vector2f GetViewPortPoint() const;
	Rectf GetInterpolatedViewPortRectf(const float interpolate) const;
	Point2f GetInterpolatedViewPortPoin2f(const float interpolate) const;
	void Translate(Vector2f movement);
	void SetPosition(Point2f pos);
	Vector2f GetMousePositionInWorld(const SDL_MouseButtonEvent& e);

private:
	Vector2f m_Position;
	Rectf m_MapDimension, m_ViewPort{}, m_LastViewPort{};
	float m_scale;
	const Window * m_pWindow;

	void CalculateViewPort();
};

