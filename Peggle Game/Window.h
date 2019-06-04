#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

class Window {

	private:
		struct 	SDL_Window* window;  
		struct  SDL_Surface* screenSurface;
		SDL_Renderer* renderer;
		const char *title;

	public:
		Window();
		~Window();
		bool onCreate(const char *title, int width_, int height_);
		void onDestroy();		
		void Update(const float time);
		void Clear();
		void Draw();
		void Render(SDL_Rect card);
		SDL_Window* GetSDL_Window();
		SDL_Renderer* GetSDL_Renderer();	
};
