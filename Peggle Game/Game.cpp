#include "Game.h"

Game::Game(SDL_Window* window_, SDL_Renderer* renderer_, float xUnit, float yUnit) {
	
	int windowWidth;	
	int windowHeight;

	window = window_;
	renderer = renderer_;

	SDL_GetWindowSize(window, &windowWidth, &windowHeight);				// Get Window size in pixels
	windowPixelSize.Load((float) windowWidth, (float) windowHeight);	// Set Window size in pixels
	windowSize.Load(xUnit, yUnit, 1.0f);								// Set windows size in units
	
	// Create projection matrix that will convert units in pixels
	projectionMatrix = MMath::viewportNDC(windowWidth, windowHeight) * 
		               MMath::orthographic(0.0f, windowSize.x, 0.0f, windowSize.y, 0.0f, windowSize.z);

	mousePosition.Load(0.0f, 0.0f, 0.0f);
	buttonDown = false;
	buttonUp = false;
	startPlay = false;
	ballStartPosition.Load(77.2f, 120.0f, 0.0f);
	ballStartVelocity.Load(120.0f, 120.0f, 0.0f);
	ballStartGravity.Load(0.0f, -9.81f, 0.0f);
	numberBall = 10;
	ballIndex = 0;	
	winIndex = 0;
	looseIndex = 0;
	pegQuantity = 0;
	lastLinePeg = 0;
	notPegs = 0;		// number of objects that is not pegs, ball, winner, gameover
}

Game::~Game() {

	OnDestroy();
}

bool Game::OnCreate() {

	int index = 0;
	int imageIndex = 0;
	int x = 0;
	int y = 0;

	std::vector<std::string> peg;
	std::string pegName = "";

	// Create the background
	BodyList.push_back(new Body(false));		// false means it is not dynamic body
	BodyList.at(0)->SetTexture(new Texture("Imagens/PeggleBackground.png", renderer));
	BodyList.at(0)->SetPosition(Vec3(0.0f, 120.0f, 0.0f));

	// Create a vector of name pegs to put ramdomly in the body
	for (int i = 0; i < 15; i++) {
		index = i + 1;
		pegName = "Imagens/peg" + std::to_string(index);
		peg.push_back(pegName);
	}
	
	// Create 60 pegs with randomly image
	index = 0;
	for (int i = 0; i < 5; i++) {												// 5 lines	
		y = 10 * i + 20;
		if (lastLinePeg == 0) {													// take the last position of the pegs
			lastLinePeg = y - 14;
		}
		for (int j = 0; j < 12; j++) {											// 12 columns
			index++;
			if (i%2 == 0) {
				x = 10 * j + 25;
			}
			else {
				x = 10 * j + 20;
			}
			BodyList.push_back(new Body(true));
			imageIndex = rand() % 14 + 0;										// Choose 1 image
			pegName = peg[imageIndex] + ".png";									// Set texture with choosen image 
			BodyList.at(index)->SetTexture(new Texture(pegName, renderer));	    // Set texture
			movePeg.push_back(false);											// Do not move
			BodyList.at(index)->SetPosition(Vec3(float(x), float(y), 0.0f));	// Position
			BodyList.at(index)->SetAcceleration(Vec3(0.0f, -9.81f, 0.0f));		// gravity
			pegQuantity++;														// calculate the quantity of the pegs
		}
	}

	// Create the ball
	ballIndex = pegQuantity+1;
	BodyList.push_back(new Body(true));
	BodyList.at(ballIndex)->SetTexture(new Texture("Imagens/ball.png", renderer));
	BodyList.at(ballIndex)->SetIsOutside();		// The ball will be set inside in render function
	notPegs++;									// Add one to not peg body counter

	// Create the win
	winIndex = pegQuantity + 2;
	BodyList.push_back(new Body(true));
	BodyList.at(winIndex)->SetTexture(new Texture("Imagens/winner.png", renderer));
	BodyList.at(winIndex)->SetPosition(Vec3(34.0f, 110.0f, 0.0f));
	BodyList.at(winIndex)->SetIsOutside();		// Is outside does not render yet
	notPegs++;									// Add one to not peg body counter
	// Create the loose
	looseIndex = pegQuantity + 3;
	BodyList.push_back(new Body(true));
	BodyList.at(looseIndex)->SetTexture(new Texture("Imagens/gameover.png", renderer));
	BodyList.at(looseIndex)->SetPosition(Vec3(24.4f, 110.0f, 0.0f));
	BodyList.at(looseIndex)->SetIsOutside();	// Is outside does not render yet
	notPegs++;									// Add one to not peg body counter

	return true;
}
void Game::OnDestroy() {

	for (int i = 0; i < BodyList.size(); i++) {

		auto it = std::find(BodyList.begin(), BodyList.end(), BodyList.at(i));

		// if it contains the index of found body
		if (it != BodyList.end()) {
			BodyList.erase(it);
		}
	}
}

void Game::Update(const float time) {
	
	if (BodyList.at(ballIndex)->GetIsInside() && startPlay) {	// If the ball is inside the screen check collision		
		movePeg = (BodyList.at(ballIndex)->ResolveCollision(BodyList, projectionMatrix, ballStartGravity, movePeg, notPegs));
		BodyList.at(ballIndex)->Update(time);
	}

	for (int i = 0; i < movePeg.size(); i++) {			
		if (movePeg[i] && BodyList.at(i + 1)->GetIsInside()) {  // Check after collision which peg must move and
			BodyList.at(i+1)->Update(time);					    // if the peg is inside the screen
		}	
	}
}

void Game::Render() {

	if (numberBall > 0) {													// numberBall = 0 game is over or win

		if (!BodyList.at(ballIndex)->GetIsInside()) {						// Recover the ball after the ball leaves the screen
			startPlay = false;												// Stop the game until mouse click again
			BodyList.at(ballIndex)->SetPosition(ballStartPosition);			// Set start position
			BodyList.at(ballIndex)->SetVelocity(ballStartVelocity);			// Set start velocity
			BodyList.at(ballIndex)->SetAcceleration(Vec3(0.0f, 0.0f, 0.0f));// Make accelaration 0, until collision with peg
			BodyList.at(ballIndex)->SetIsInside();							// Set ball inside the screen
		}
	}
	else if(!BodyList.at(ballIndex)->GetIsInside())  {						// No more balls to shoot
		if (BodyList.at(ballIndex)->GetNumberPegHit() < pegQuantity) {
			BodyList.at(looseIndex)->SetIsInside();
		}
		else {			
			BodyList.at(winIndex)->SetIsInside();
		}
	}

	// Set the ball outside to start again if the ball passes the last line peg
	if (BodyList.at(ballIndex)->GetIsInside()) {
		Vec3 ballPosition = BodyList.at(ballIndex)->GetPosition();
		if (ballPosition.y <= float(lastLinePeg)) {  // after the all pegs position		
			BodyList.at(ballIndex)->SetIsOutside();  // take the of the screen
		}
	}

	for (int i = 0; i < BodyList.size(); i++) {							// Render all the bodies

		if (BodyList.at(i)->GetIsInside()) {							// if the body is inside the screen
			SDL_Rect rect = BodyList.at(i)->GetRect(projectionMatrix, windowPixelSize);	 // take the position to put in the screen			
			BodyList.at(i)->GetTexture()->Render(&rect);				// Show the image on screen
		}
	}
}

void Game::UpdateBallVelocity() {
			
	if (buttonDown && buttonUp) {		// Complete mouse click

		Vec3 Direction = GetMousePosition() - ballStartPosition;
		float Maginetude = sqrt((Direction.x*Direction.x) + (Direction.y*Direction.y) + (Direction.z*Direction.z));
		Vec3 UnityVector = Direction / Maginetude;  // Get directon of velocity
		Vec3 BallVelocity = ballStartVelocity;
		BodyList.at(ballIndex)->SetVelocity(Vec3(BallVelocity.x * UnityVector.x, BallVelocity.y * UnityVector.y, BallVelocity.z * UnityVector.z));

		startPlay = true;		// Start the ball
		buttonDown = false;		// Deactivate button down
		buttonUp = false;		// Make buttonUp off to use click the mouse again
		numberBall--;			// Decrease the number of ball by 1
	}
}

Vec3 Game::GetMousePosition() {

	// Transform mouse position in pixel to unit	
	Vec3 pixelToUnit;		
	pixelToUnit.Load(windowPixelSize.x / windowSize.x, windowPixelSize.y / windowSize.y, 0.0f);  // caculates the unit of mouse
	Vec3 mousePositionUnit;
	mousePositionUnit.Load(mousePosition.x / pixelToUnit.x, mousePosition.y / pixelToUnit.y, 0.0f);
	mousePositionUnit.y = windowSize.y - mousePositionUnit.y;  // invertion axis Y, 0 in screen starts on top
	return (mousePositionUnit);
}

bool Game::GetButtonUp() {
	return buttonUp;
}

bool Game::GetStartPlay() {
	return startPlay;
}

int Game::GetNumberBall() {
	return numberBall;
}

void Game::HandleEvent(SDL_Event* e) {

	mousePosition.x = 0;
	mousePosition.y = 0;

	//Check if the ball is the star position. If not, then do not activate the button mouse
	if (BodyList.at(ballIndex)->GetIsInside()) {
		
		// Check if the ball is the star position. If not, then do not activate the button mouse
		Vec3 ballPosition = BodyList.at(ballIndex)->GetPosition();
		
		if (ballPosition.x == ballStartPosition.x && ballPosition.y == ballStartPosition.y) {

			//If mouse event happened
			if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
								
				//Get mouse position
				int x, y;
				SDL_GetMouseState(&x, &y);
				mousePosition.x = x;
				mousePosition.y = y;
				
				switch (e->type) {

					case SDL_MOUSEBUTTONDOWN:
						buttonDown = true;
						break;

					case SDL_MOUSEBUTTONUP:
						buttonUp = true;
						break;
				}
			}
		}
	}
}