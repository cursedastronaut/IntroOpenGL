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
		bool isCameraSpeeding = false;
		//Camera position
		float cameraX = 2.5f; float cameraY = -0.5f; float cameraZ = 7.f;

		GLuint tex;

		GLuint LoadTexture();
};