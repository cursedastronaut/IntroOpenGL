#pragma once
#include "draw.h"
#include <imgui/imgui.h>
class App
{
	public:
		App() {};
		void Update(int value);
		float angle = 0.0f;
		int currentExercise = 1;

		GLuint tex[];


		void Update();

		//Loads the textures
		GLuint LoadTexture(const char* filename, GLuint width = 0, GLuint height = 0, bool isAlpha = false);

		//WARNING!!
		//This part was done after the project was finished. It is not meant to be marked.
		GLuint LoadTexturePNG(const char* filename);

};