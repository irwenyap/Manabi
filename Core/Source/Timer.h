#ifndef TIMER_H
#define TIMER_H

#include <Windows.h>

namespace Core {

	class Timer {
		LARGE_INTEGER frequency;
		LARGE_INTEGER prevTime, currTime;

		double dt;

	public:
		Timer();

		void Start();
		void Update();

		double const& GetDeltaTime() const;

	private:
		double LargeIntToSecs(LARGE_INTEGER const& L) const;
	};

}


#endif // !TIMER_H
