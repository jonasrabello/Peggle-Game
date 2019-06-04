#pragma once

#include <iostream>
#include "Window.h"

class Timer {

	private:
		unsigned int currentTick;
		unsigned int prevTick;

	public:
		Timer();
		~Timer();

		void Start();
		void UpdateFrame();
		float getDeltaTime() const;
		unsigned int getSleepTime(const unsigned int fps) const;
};

