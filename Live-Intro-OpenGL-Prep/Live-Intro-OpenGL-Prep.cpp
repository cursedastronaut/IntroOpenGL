// Live-Intro-OpenGL-Prep.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glut.h>
#include <imgui/imgui_impl_opengl2.h>
#include "src/app.h"
#include "src/camera.h"
#include "src/lights.h"


//Global creation of the class App.
App* app = new App();
//Global creation of the class Camera.
Camera* cam = new Camera();
//Global creation of the class Lights
Light* light = new Light({0,1.5f,-2}, GL_LIGHT1);

//Telling main() that display() exists despite being declared after.
void display();

//Handles different app values. Cannot be called when inside of app for obscure reasons.
void update(int value) {
	app->angle += 2.f;
	if (app->angle > 360)
		app->angle -= 360.f;

	cam->Update();
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

//Main function.
int main(int argc, char* argv[])
{
	//Initialisation
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Intro - Galaad Martineaux (g.martineaux@student.isartdigital.com)");


	glutDisplayFunc(display);
	glutTimerFunc(25, update, 0);
	glEnable(GL_TEXTURE_2D);
	app->tex[0] = app->LoadTexture("binary.pbm");
	app->tex[1] = app->LoadTexture("marwan.bmp", 504, 504);
	app->tex[2] = app->LoadTexturePNG("gun3.png");

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplGLUT_Init();
	ImGui_ImplGLUT_InstallFuncs();
	ImGui_ImplOpenGL2_Init();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontDefault();
	io.Fonts->Build();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();

	glutMainLoop();
	return 0;
}

//Displays stuff
void display() {

	glBindTexture(GL_TEXTURE_2D, 0);
	//Clears everything
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);
	glClearColor(1, 0.2, 0.5f, 1);
	
	
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	

	
	//Checks what rendering method to use. Both functions uses dynamically changing values (screen height and width) to avoid the scene being
	//distored when the window is resized.
	cam->Update();

	

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	cam->LookAt();
	

	//Light1
	light->Update();
	app->Update();

	

	

	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	draw::drawGun({-0.2f, -1.0f - cam->offset - 0.2f, 0},
		{ 0.2f, -0.4f - cam->offset - 0.2f, 0 }, {1,1,1}, app->tex[2], true);
	
	ImGui_ImplGLUT_NewFrame();
	ImGui_ImplOpenGL2_NewFrame();
	ImGui::Begin("Debug Informations");
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	ImGui::EndFrame();

	glFlush();
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
