#ifndef Body_H
#define BODY_H

#include <vector>
#include "SDL.h"
#include "Matrix.h"
#include "Window.h"
#include "MMath.h"
#include "Texture.h"

using namespace MATH;

class Body	{
	private:		
		Vec3 Position;
		Vec3 Velocity;
		Vec3 Acceleration;
		SDL_Rect Rect;
		Texture* BodyTexture;
		bool isInside;
		bool isDynamic;
		int numberPegHit;		
	public:
		Body(bool dynamic);
		~Body();
		void SetPosition(Vec3 position);
		void SetVelocity(Vec3 velocity);
		void SetTexture(Texture* texture);
		void SetAcceleration(Vec3 acceleration);
		void SetIsInside();
		void SetIsOutside();
		Vec3 GetPosition();
		Vec3 GetVelocity();
		bool GetIsInside();
		int GetNumberPegHit();
		std::vector<bool> ResolveCollision(std::vector<Body*> BodyList, Matrix4 projectionMatrix, Vec3 ballAccelaretion ,std::vector<bool>, int notPegs);
		bool CheckCollision(int peg, std::vector<Body*> BodyList, Matrix4 projectionMatrix);
		void Update(const float time);		
		SDL_Rect GetRect(Matrix4 projectionMatrix, Vec2 windowSizePixel);
		Vec3 GetPixelPosition(Matrix4 projectionMatrix);
		Texture* GetTexture();		
		float Dot(const Vec3 v);
};

#endif // !Body_H
