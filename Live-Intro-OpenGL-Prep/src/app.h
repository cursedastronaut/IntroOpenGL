#pragma once
#include "draw.h"
class App
{
	public:
		App() {};
		void Update(int value);
		float angle = 0.0f;
		float cameraAngleH = 135;
		float cameraAngleV = 0;
		bool orthoRendering = 0;
		//Camera position
		float cameraX = 0; float cameraY = 0; float cameraZ = -1.f;

		void LoadTexture();
};