#pragma once
#include "draw.h"
class App
{
	public:
		App() {};
		void Update(int value);
		float angle = 0.0f;
		float cameraAngle = 135;
		bool orthoRendering = 0;
		float fx = 0; float fy = 0; float fz = -1.f;
};