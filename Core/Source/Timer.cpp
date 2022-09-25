#include "Timer.h"

namespace Core {

	Timer::Timer() 
		: dt(0.0) {
		prevTime = currTime = {};
		QueryPerformanceFrequency(&frequency);
	}

	void Timer::Start() {
		QueryPerformanceCounter(&prevTime);
	}

	void Timer::Update()
	{
		LARGE_INTEGER delta;
		QueryPerformanceCounter(&currTime);

		delta.QuadPart = currTime.QuadPart - prevTime.QuadPart;

		prevTime = currTime;

		dt = LargeIntToSecs(delta);
	}

	double const& Timer::GetDeltaTime() const
	{
		return dt;
	}

	double Timer::LargeIntToSecs(LARGE_INTEGER const& L) const
	{
		return static_cast<double>(L.QuadPart) / static_cast<double>(frequency.QuadPart);
	}

}