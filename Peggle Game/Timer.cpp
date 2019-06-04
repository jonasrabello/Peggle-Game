#include "Timer.h"

Timer::Timer() :prevTick(0), currentTick(0) {}

Timer::~Timer() {

}

void Timer::Start() {
	prevTick = SDL_GetTicks();
	currentTick = SDL_GetTicks();
}

void Timer::UpdateFrame() {
	prevTick = currentTick;
	currentTick = SDL_GetTicks();
}

float Timer::getDeltaTime() const {
	return (float(currentTick - prevTick)) / 1000.0f;	//get difference in time in seconds
}

unsigned int Timer::getSleepTime(const unsigned int fps) const {
	
	unsigned int milliSecsPerFrame = 1000 / fps; 
	
	if (milliSecsPerFrame == 0) {
		return 0;
	}
		
	unsigned int sleepTime = milliSecsPerFrame - (SDL_GetTicks() - currentTick);

	if (sleepTime > milliSecsPerFrame) {
		return milliSecsPerFrame;
	}

	return sleepTime;
}