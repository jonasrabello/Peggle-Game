#include "Window.h"
#include <stdio.h>
#include <iostream>
#include <SDL.h>
//#include <SDL_image.h>

Window::Window() {

}

Window::~Window() {
	onDestroy();
};

void Window::Render(SDL_Rect card) {

}

SDL_Window * Window::GetSDL_Window()
{
	return window;
}

SDL_Renderer* Window::GetSDL_Renderer() {
	return renderer;
}

void Window::Update(const float time) {
	

}

bool Window::onCreate(const char *title, int width_, int height_) {

	screenSurface = nullptr;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		//printf("SDL_Error: %s\n", SDL_GetError());
		std::cout << "SDL_Error:" << SDL_GetError() << std::endl;
		return false;
	}

	// Create the window
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width_, height_, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << "SDL_Error:" << SDL_GetError() << std::endl;
		return false;
	}

	// Create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		std::cout << "SDL_Error:" << SDL_GetError() << std::endl;
		return false;
	}

	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	screenSurface = SDL_GetWindowSurface(window);
	if (screenSurface == nullptr) {
		std::cout << "SDL_Error:" << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Window::onDestroy() {

	/// Kill the window
	if (window) {						// the same -> (window != nullptr)
		SDL_DestroyWindow(window);
	}

	// Kill screen surface
	if (screenSurface) {				// the same -> (screenSurface != nullptr)
		SDL_FreeSurface(screenSurface);
	}

	///Exit the SDL subsystems
	SDL_Quit();
	IMG_Quit();

	exit(0);
}

void Window::Clear() {
	SDL_RenderClear(renderer);
}

void Window::Draw() {
	SDL_RenderPresent(renderer);
}
