#include "FrameTimer.h"
using namespace std::chrono;
FrameTimer::FrameTimer()
	:
	last(steady_clock::now())
{
}

float FrameTimer::Mark()
{
	steady_clock::time_point now = steady_clock::now();
	duration<float> duration = now - last;
	last = now;
	return duration.count();
}
