#pragma once

#include <iostream>
#include <stdio.h>
#include "Window.h"
#include "Timer.h"
#include "Scene.h"
#include "Game.h"
#include <SDL.h>

class GameSceneManager {
	private:
		bool isRuning;
		Window* window;
		Timer* timer;
		Game* game;
	public:
		GameSceneManager();
		~GameSceneManager();

		bool OnCreate(const char *title_, int width_, int height_, float  xUnit, float  yUnit);
		void OnDestroy();

		void Run();
};

