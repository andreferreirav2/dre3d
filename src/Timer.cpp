// Heavily inspired on GameTimer.cpp by Frank Luna
#include <windows.h>
#include "Timer.h"
#include <iostream>

Timer::Timer()
	: mSecondsPerCount(0.0),
	mDeltaTime(-1.0),
	mBaseTime(0),
	mPausedTime(0),
	mPrevTime(0),
	mCurrTime(0),
	mStopped(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	mSecondsPerCount = 1.0 / (double)countsPerSec;
}

// Returns the total time elapsed since Reset() was called, NOT counting any
// time when the clock is stopped.
float Timer::totalTime() const
{
	// If we are stopped, do not count the time that has passed since we stopped.
	// Moreover, if we previously already had a pause, the distance 
	// mStopTime - mBaseTime includes paused time, which we do not want to count.
	// To correct this, we can subtract the paused time from mStopTime:  
	//
	//                     |<--paused time-->|
	// ----*---------------*-----------------*------------*------------*------> time
	//  mBaseTime       mStopTime        startTime     mStopTime    mCurrTime

	// The distance mCurrTime - mBaseTime includes paused time,
	// which we do not want to count.  To correct this, we can subtract 
	// the paused time from mCurrTime:  
	//
	//  (mCurrTime - mPausedTime) - mBaseTime 
	//
	//                     |<--paused time-->|
	// ----*---------------*-----------------*------------*------> time
	//  mBaseTime       mStopTime        startTime     mCurrTime

	__int64 baseline = mStopped ? mStopTime : mCurrTime;
	return static_cast<float>(((baseline - mPausedTime) - mBaseTime) * mSecondsPerCount);
}

float Timer::deltaTime() const
{
	return static_cast<float>(mDeltaTime);
}

bool Timer::isPaused() const
{
	return mStopped;
}

void Timer::reset()
{
	__int64 currTime = currentTime();

	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped = false;
}

void Timer::start()
{
	__int64 startTime = currentTime();

	// Accumulate the time elapsed between stop and start pairs.
	//
	//                     |<-------d------->|
	// ----*---------------*-----------------*------------> time
	//  mBaseTime       mStopTime        startTime     

	if (mStopped)
	{
		mPausedTime += (startTime - mStopTime);

		mPrevTime = startTime;
		mStopTime = 0;
		mStopped = false;
	}
}

void Timer::stop()
{
	if (!mStopped)
	{
		mStopTime = currentTime();
		mStopped = true;
	}
}

void Timer::tick()
{
	if (mStopped)
	{
		mDeltaTime = 0.0;
		return;
	}

	mCurrTime = currentTime();

	// Time difference between this frame and the previous.
	mDeltaTime = (mCurrTime - mPrevTime) * mSecondsPerCount;

	// Prepare for next frame.
	mPrevTime = mCurrTime;

	// Force nonnegative.  The DXSDK's CDXUTTimer mentions that if the 
	// processor goes into a power save mode or we get shuffled to another
	// processor, then mDeltaTime can be negative.
	if (mDeltaTime < 0.0)
	{
		mDeltaTime = 0.0;
	}

	std::cout << mDeltaTime << std::endl;
}

__int64 Timer::currentTime()
{
	__int64 time;
	QueryPerformanceCounter((LARGE_INTEGER*)&time);
	return time;
}

