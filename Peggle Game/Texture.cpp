#include "Texture.h"

Texture::Texture() {
	height = 0;
	width = 0;
	renderer = 0;
	texture = NULL;
}

Texture::Texture(std::string path, SDL_Renderer* newRenderer) {

	height = 0;
	width = 0;
	renderer = 0;
	texture = NULL;

	onCreate(path, newRenderer);
}

Texture::~Texture() {
	onDestroy();
}

void Texture::Render(SDL_Rect* rect) {

	//Render texture to screen
	SDL_RenderCopyEx(renderer, texture, NULL, rect, NULL, NULL, SDL_RendererFlip());
}


void Texture::onCreate(std::string path, SDL_Renderer* newRenderer) {

	// Destroy previous texture		
	onDestroy();

	SDL_Surface* image = IMG_Load(path.c_str());
	if (image == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}

	// Color key image
	//SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 0xFF, 0xFF, 0xFF));

	// Assign the new renderer if provided and destroy the old one
	if (newRenderer) {
		renderer = newRenderer;	
	}

	//Create texture from surface pixels
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (texture == NULL)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	// Image dimension
	height = image->h;
	width = image->w;
	
	//Get rid of old loaded surface
	SDL_FreeSurface(image);
}

void Texture::onDestroy() {

	if (texture) {
		SDL_DestroyTexture(texture);
		texture = NULL;
		height = 0;
		width = 0;
	}

	if (renderer) {
		SDL_DestroyRenderer(renderer);
			renderer = NULL;
	}
}

