#pragma once
#include "draw.h"
class App
{
	public:
		App() {};
		void Update(int value);
		float angle = 0.0f;
		

		GLuint tex[];

		//Loads the textures
		GLuint LoadTexture(const char* filename, GLuint width = 0, GLuint height = 0);
};