#include "Timer.h"

namespace Core {

	Timer::Timer() 
		: dt(0.0) 
		, et(0.0) {
		startTime = prevTime = currTime = {};
		QueryPerformanceFrequency(&frequency);
	}

	void Timer::Start() {
		QueryPerformanceCounter(&prevTime);
		prevTime = startTime;
	}

	void Timer::Update()
	{
		LARGE_INTEGER delta, elapsed;
		QueryPerformanceCounter(&currTime);

		delta.QuadPart = currTime.QuadPart - prevTime.QuadPart;
		elapsed.QuadPart = currTime.QuadPart - startTime.QuadPart;

		prevTime = currTime;

		dt = LargeIntToSecs(delta);
		et = LargeIntToSecs(elapsed);
	}

	double const& Timer::GetDeltaTime() const
	{
		return dt;
	}

	double const& Timer::GetElapsedTime() const {
		return et;
	}

	double Timer::LargeIntToSecs(LARGE_INTEGER const& L) const
	{
		return static_cast<double>(L.QuadPart) / static_cast<double>(frequency.QuadPart);
	}

}