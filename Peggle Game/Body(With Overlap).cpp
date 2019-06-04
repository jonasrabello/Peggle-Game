#include "Body.h"

#include <stdio.h>
#include <iostream>

const float COEFREST = 0.9f;

Body::Body(bool dynamic) {
	Position.Load(0.0f, 0.0f, 0.0f);
	Velocity.Load(0.0f, 0.0f, 0.0f);
	Acceleration.Load(0.0f, 0.0f, 0.0f);
	isDynamic = dynamic;
	isInside = true;		// Set the body object inside the screen
	numberPegHit = 0;		// number of the peg that was collided
}

Body::~Body() {

}

void Body::SetPosition(Vec3 position) {
	Position = position;
};
void Body::SetVelocity(Vec3 velocity) {
	Velocity = velocity;
};

void Body::SetTexture(Texture* texture) {
	BodyTexture = texture;
}

void Body::SetAcceleration(Vec3 acceleration) {

	Acceleration.Load(acceleration.x, acceleration.y, acceleration.z);
}

void Body::SetIsInside() {
	isInside = true;
}

void Body::SetIsOutside() {
	isInside = false;
	std::cout << "Setting out" << std::endl;
}

Vec3 Body::GetPosition() {
	return Position;
}

Vec3 Body::GetVelocity() {
	return Velocity;
}

bool Body::GetIsInside() {
	return isInside;
}

int Body::GetNumberPegHit() {
	return numberPegHit;
}

std::vector<bool> Body::ResolveCollision(std::vector<Body*> BodyList, Matrix4 projectionMatrix, Vec3 ballAccelaretion, std::vector<bool> movePeg, int notPegs) {

	// Try to find the ball (this) has collided with the pegs (BodyList)
	// The loop start in 1 because, 0 is the background, and notPegs are objects that are not pegs
	for (int i = 1; i < BodyList.size() - notPegs; i++) {	 // Check Resolve Collision for all pegs that is inside in screen

		if (!BodyList.at(i)->GetIsInside() && movePeg[i - 1]) {  // If the peg is not inside the screen,  but it still moving
			movePeg[i - 1] = false;
		}
		else {

			if (!movePeg[i - 1]) {			// Just check the collision if the peg is not in movement

				if (this->CheckCollision(i, BodyList, projectionMatrix)) {

					if (this->Acceleration.y == 0.0f) {
						this->Acceleration = ballAccelaretion;
					}

					this->numberPegHit++;		// Add one more peg hit

					// Take the distance between peg and ball
					Vec3 Normal = BodyList.at(i)->GetPosition() - this->Position;
					// Calculate the magnitude
					float Magnitude = sqrt((Normal.x*Normal.x) + (Normal.y*Normal.y) + (Normal.z*Normal.z));
					// Calculate vetor unit
					Vec3 UnityNormal = Normal / Magnitude;
					// v1ni = v1i . ^n
					float V1NormalIni = this->Dot(UnityNormal);
					// v2ni = v2i . ^n
					float V2NormalIni = BodyList.at(i)->Dot(UnityNormal);
					// v2nf = v1ni(1 + E) / 2
					float V2NormalFin = V1NormalIni * (1 + COEFREST) / 2;
					// v1nf = v1n1 + v2nf
					float V1NormalFin = V1NormalIni - V2NormalFin;
					// deltav1n = v1nf - v1ni
					float DeltaV1Normal = V1NormalFin - V1NormalIni;
					// deltav2n = v2nf - v2ni
					float DeltaV2Normal = V2NormalFin - V2NormalIni;
					// v1f = v1i + deltav1 ^n
					Vec3 V1Fin = this->Velocity + (DeltaV1Normal * UnityNormal);
					// v2f = v2i + deltav2 ^n
					Vec3 V2Fin = BodyList.at(i)->GetVelocity() + (DeltaV2Normal * UnityNormal);

					// Update Ball velocity
					this->Velocity = V1Fin;

					// Update peg velocity
					BodyList.at(i)->SetVelocity(V2Fin);

					movePeg[i - 1] = true;  // Set peg as collision to move

					return movePeg;
				}
			}  // here
		}		
	}

	return movePeg;
}

bool Body::CheckCollision(int peg, std::vector<Body*> BodyList, Matrix4 projectionMatrix) {
	
	// Check the collision between the peg and the ball

	Texture* pegTexture = BodyList.at(peg)->GetTexture();  // Take the texture of image with the width
	
	// because pegTexture->width is in pixels, all calculation is in pixel to check the collision
	
	float totalRadii = float( (pegTexture->width / 2) + (this->BodyTexture->width / 2) );

	Vec3 Direction = BodyList.at(peg)->GetPixelPosition(projectionMatrix) - this->GetPixelPosition(projectionMatrix);
	
	float Maginetude = sqrt((Direction.x*Direction.x) + (Direction.y*Direction.y) + (Direction.z*Direction.z));

	int unit = 1;

	
	//float totalRadii = float( ( (pegTexture->width / 2) / 5 ) + ( (this->BodyTexture->width / 2) / 5) );

	//Vec3 Direction = BodyList.at(peg)->GetPosition() - this->GetPosition();

	//float Maginetude = sqrt((Direction.x*Direction.x) + (Direction.y*Direction.y) + (Direction.z*Direction.z));

	//int unit = 5;

	//Vec3 UnityVector = Direction / Maginetude;  // Get directon of velocity

	if (Maginetude <= totalRadii) {

		//float overLap = totalRadii - Maginetude;

		//if (overLap > 0.0f) {

		//	this->Position += ( ( -1 * overLap / 2) * UnityVector ) / unit;

		//	Vec3 pegPosition = BodyList.at(peg)->GetPosition();

		//	pegPosition += ( ( overLap / 2)  * UnityVector ) / unit;

		//	BodyList.at(peg)->SetPosition(pegPosition);
		//}

		return true;
	}

	return false;
}

Vec3 Body::GetPixelPosition(Matrix4 projectionMatrix) {
	return projectionMatrix * Position;
}

void Body::Update(const float time) {

	if (time && isDynamic) {  // Do not calculate the position of background and other not dynamic bodies

		Velocity += Acceleration * time;

		Position += (Velocity * time) + 0.5f * Acceleration * time * time;
	}
}

Texture* Body::GetTexture() {
	return BodyTexture;
}

SDL_Rect Body::GetRect(Matrix4 projectionMatrix, Vec2 windowSizePixel ,int ball) {

	Rect.h = BodyTexture->height;
	Rect.w = BodyTexture->width;

	Vec3 screenCoords = projectionMatrix * Position;

	Rect.x = screenCoords.x;
	Rect.y = screenCoords.y;

	//Check if the peg or ball is inside of the window
	if (Rect.x < 0 || Rect.x > windowSizePixel.x) {
		isInside = false;
		if (ball == 61) {
			std::cout << "Set outside on x" << std::endl;
		}
	}

	if (Rect.y > windowSizePixel.y) {
		isInside = false;
		if (ball == 61) {
			std::cout << "Set outside on y" << std::endl;
		}
	}

	return Rect;
}

float Body::Dot(const Vec3 v) {
	return v.x*this->Velocity.x + v.y*this->Velocity.y + v.z*this->Velocity.z;
}