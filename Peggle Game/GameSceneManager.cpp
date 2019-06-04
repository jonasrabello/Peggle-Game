#include "GameSceneManager.h"

GameSceneManager::GameSceneManager() {

}


GameSceneManager::~GameSceneManager() {

}

bool GameSceneManager::OnCreate(const char *title_, int width_, int height_, float  xUnit, float  yUnit) {

	isRuning = true;

	window = new Window();

	if (!this->window->onCreate(title_, width_, height_)) {		//create a window	
		std::cout << "Window can't be made" << std::endl;
		OnDestroy();
		return false;
	}
	else {

		game = new Game(window->GetSDL_Window(), window->GetSDL_Renderer(), xUnit, yUnit);		//Bind the window to game
		
		if (!game->OnCreate()) {
			std::cout << "Game can't be made" << std::endl;
			OnDestroy();
			return false;
		}
		else {

			timer = new Timer();										// Create the timer
			if (timer == nullptr) {
				OnDestroy();
				return false;
			}
		}
	}

	return true;
}

void GameSceneManager::OnDestroy() {
	if (window) delete window;
	window = nullptr;
	if (game) delete game;
	game = nullptr;
	if (timer) delete timer;
	timer = nullptr;	
}

void GameSceneManager::Run() {

	timer->Start();

	SDL_Event event;	

	while (isRuning) {

		SDL_PollEvent(&event);							    // Check the last keyboard that was pressed

		if (event.type == SDL_KEYDOWN) {					// Stop the program if keyboard ESC is pressed
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				isRuning = false;
			}
		}

		game->HandleEvent(&event);							// Get the position of the mouse and the button up		

		game->UpdateBallVelocity();							// Update velocity with the direction of the mouse click

		timer->UpdateFrame();								// Update the timer according with SDL_GetTicks

		game->Update(timer->getDeltaTime());				// Gets time is seconds

		window->Clear();									// Clear window to be redender be present again
		game->Render();										// Shows the ball and the pegs
		window->Draw();										// Render the bodies

		SDL_Delay(timer->getSleepTime(60));					// Keep the event loop running at a sane rate
	}
}
