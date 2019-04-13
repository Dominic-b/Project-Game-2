#include "stdafx.h"

double Timer::checkTime() {
	time2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(time2 - time1);
	return time_span.count();
}

void Timer::checkDeltaTime() {
	deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - time3).count();
	time3 = std::chrono::high_resolution_clock::now();
}

void Timer::reset() {
	time1 = std::chrono::high_resolution_clock::now();
	time2 = std::chrono::high_resolution_clock::now();
	time3 = std::chrono::high_resolution_clock::now();
	lastSecond = 0;
}

Timer::Timer() {
	time1 = std::chrono::high_resolution_clock::now();
	time2 = std::chrono::high_resolution_clock::now();
	time3 = std::chrono::high_resolution_clock::now();
	lastSecond = 0;
}