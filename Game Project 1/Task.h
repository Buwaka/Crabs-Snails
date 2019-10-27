#pragma once

class Task
{
public:

	enum Layer {
		background, objects, foreground, effects, total
	};



	Task();
	virtual ~Task();

	virtual void Update(float elaspedSeconds) = 0;
	virtual void Draw(float interpolate, const Rectf window) = 0;

	virtual Layer Type() const = 0;
	virtual bool Complete() const = 0;
};

