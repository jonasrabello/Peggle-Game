#pragma once

#include <iostream>
#include <string>
#include "SDL.h"
#include "Matrix.h"
#include "Window.h"
#include "MMath.h"
#include "Body.h"
#include <vector>

using namespace MATH;

class Game {
	private:
		SDL_Window* window;
		std::vector<Body*> BodyList;
		Vec2 windowPixelSize;
		Vec3 windowSize;
		Matrix4 projectionMatrix;
		SDL_Surface* screenSurface;
		SDL_Renderer* renderer;
		std::vector<bool> movePeg;
		int ballIndex;		
		int winIndex;
		int looseIndex;
		Vec3 ballStartPosition;
		Vec3 ballStartVelocity;
		Vec3 ballStartGravity;
		Vec3 mousePosition;
		bool buttonDown;
		bool buttonUp;
		bool startPlay;
		int numberBall;
		int pegQuantity;
		int lastLinePeg;
		int notPegs;
	public:
		Game(SDL_Window* window_, SDL_Renderer* renderer_, float  xUnit, float  yUnit);
		~Game();
		bool OnCreate();
		void OnDestroy();
		void Update(const float time);
		void Render();
		void HandleEvent(SDL_Event* e);		//Handles mouse event
		void UpdateBallVelocity();
		Vec3 GetMousePosition();
		bool GetButtonUp();
		bool GetStartPlay();
		int GetNumberBall();
};