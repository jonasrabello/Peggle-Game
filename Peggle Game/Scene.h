#pragma once
class Scene {
	public:
		virtual bool OnCreate() = 0;  // = 0 make it abstract
		virtual void OnDestroy() = 0;
		virtual void Update(const float time) = 0;
		virtual void Render() = 0;
		virtual void GravityForce(int planet, int star) = 0;
};

