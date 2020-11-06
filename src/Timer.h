#pragma once
class Timer
{
public:
	Timer();

	float totalTime() const;
	float deltaTime() const;
	bool isPaused() const;

	void reset();
	void start();
	void stop();
	void tick();

private:
	__int64 currentTime();
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime;
	__int64 mPausedTime;
	__int64 mStopTime;
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool mStopped;
};

