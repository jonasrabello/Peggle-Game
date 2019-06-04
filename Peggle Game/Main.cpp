#include <stdio.h>
#include <iostream>
#include "GameSceneManager.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float  SCREEN_X_UNIT = 160.0f;
const float  SCREEN_Y_UNIT = 120.0f;
const char *title = "Peggle Game";

//Uint32  handleTimer(Uint32 interval, void *param);  /// Prototyping

int main(int argc, char* args[]) {	/// Standard C-style entry point, you need to use it

	GameSceneManager* game = new GameSceneManager();

	if (game->OnCreate(title, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_X_UNIT, SCREEN_Y_UNIT)) {
		game->Run();
	} else {
		delete game;
		game = nullptr;
	}

	return 0;
}