#pragma once
class Script
{
public:

	enum ScriptType
	{
		Move, Size
	};

	Script();
	virtual ~Script();

	virtual void Check(float elapsedSeconds) = 0;
	virtual bool Complete() = 0;
	virtual void Clean() = 0;

	ScriptType Type() const;

private:
	ScriptType m_Type;
};

