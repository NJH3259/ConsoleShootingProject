#pragma once

#include <Level/Level.h>
#include <Util/Timer.h>

class TestLevel : public Craft::Level
{
public:
	TestLevel();
	~TestLevel() = default;

	inline int GetCurrentScore() const { return score; }

private:
	virtual void OnInitialized();

private:
	Timer timeLimit;
	int score;
};

