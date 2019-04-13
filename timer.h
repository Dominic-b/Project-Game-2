#pragma once
#include "stdafx.h"

class Timer {
	std::chrono::high_resolution_clock::time_point time1;
	std::chrono::high_resolution_clock::time_point time2;
	std::chrono::high_resolution_clock::time_point time3;

public:
	//for fps counter
	int fps;//frames per second
	int lastSecond;//to measure framerate
	double deltaTime;//the time between each frame


	double checkTime();
	void checkDeltaTime();
	void reset();
	Timer();
};