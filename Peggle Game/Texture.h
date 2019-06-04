#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class Texture {
	
	public:

		Uint32 height;
		Uint32 width;
		SDL_Renderer* renderer;
		SDL_Texture* texture;

		Texture();
		Texture(std::string path, SDL_Renderer* newRenderer);
		~Texture();

		void  onCreate(std::string path, SDL_Renderer* newRenderer);
		void onDestroy();
		void Render(SDL_Rect* rect);
};

