// Live-Intro-OpenGL-Prep.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "src/app.h"
#define WIN_HEIGHT 576
#define WIN_WIDTH 1024


//Global creation of the class App.
App* app = new App();

//Telling main() that display() exists despite being declared after.
void display();

//Handles different app values. Cannot be called when inside of app for obscure reasons.
void update(int value) {
	app->angle += 2.f;
	if (app->angle > 360)
		app->angle -= 360.f;

	if (app->cameraAngleH == 0)
		app->cameraAngleH = 360.f;
	else if (app->cameraAngleH > 360.f)
		app->cameraAngleH -= 360.f;
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

//Handles rendering mode switching, and the Camera Angle.
void keyboard(unsigned char key, int x, int y) {
	float speed = 0.01f;
	if (app->isCameraSpeeding)
		speed = 0.1f;
	switch (key)
	{
	case 56: app->orthoRendering = false; break;
	case 57: app->orthoRendering = true; break;
	case 110: app->cameraAngleH++; break;
	case 109: app->cameraAngleH--; break;

	case 's': 
		app->cameraX -= (cosf(app->cameraAngleH * (PI / 180.f)) + sinf(app->cameraAngleH * (PI / 180.f))) * speed;
		app->cameraZ -= (cosf(app->cameraAngleH * (PI / 180.f)) - sinf(app->cameraAngleH * (PI / 180.f))) * speed;
		break;
	case 'z':
		app->cameraX += (cosf(app->cameraAngleH * (PI / 180.f)) + sinf(app->cameraAngleH * (PI / 180.f))) * speed;
		app->cameraZ += (cosf(app->cameraAngleH * (PI / 180.f)) - sinf(app->cameraAngleH * (PI / 180.f))) * speed;
		break;
	case 'q':
		app->cameraX += (cosf((app->cameraAngleH + 90) * (PI / 180.f)) + sinf((app->cameraAngleH + 90) * (PI / 180.f))) * speed;
		app->cameraZ += (cosf((app->cameraAngleH + 90) * (PI / 180.f)) - sinf((app->cameraAngleH + 90) * (PI / 180.f))) * speed;
		break;
	case 'd':
		app->cameraX += (cosf((app->cameraAngleH - 90) * (PI / 180.f)) + sinf((app->cameraAngleH - 90) * (PI / 180.f))) * speed;
		app->cameraZ += (cosf((app->cameraAngleH - 90) * (PI / 180.f)) - sinf((app->cameraAngleH - 90) * (PI / 180.f))) * speed;
		break;
	case 'i':
		app->cameraAngleV++;

	case 'k':
		app->cameraAngleV--;
	}
	app->isCameraSpeeding = false;
}

//Handles Camera Positionning.
void keyboard2(int key, int x, int y)
{
	switch (key)
	{
	case 100: app->cameraX -= 0.1f; break;
	case 101: app->cameraY += 0.1f; break;
	case 102: app->cameraX += 0.1f; break;
	case 103: app->cameraY -= 0.1f; break;
	case 'p': app->isCameraSpeeding = true; break;
	}
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
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard2);
	glutTimerFunc(25, update, 0);
	glEnable(GL_TEXTURE_2D);
	app->tex = app->LoadTexture();
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
	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glClearColor(1, 0.2, 0.5f, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//Checks what rendering method to use. Both functions uses dynamically changing values (screen height and width) to avoid the scene being
	//distored when the window is resized.
	if (!app->orthoRendering)
	{
		gluPerspective(60, (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT), 0.001f, 1000);
		
	}
	else
		glOrtho(-(float)glutGet(GLUT_WINDOW_WIDTH) / WIN_WIDTH * 3.f - app->cameraX, //TODO: Remove 1024 and 576 and simply put the original height and width.
			(float)glutGet(GLUT_WINDOW_WIDTH) / WIN_WIDTH * 3.f - app->cameraX,
			-(float)glutGet(GLUT_WINDOW_HEIGHT) / WIN_HEIGHT * 3.f - app->cameraY,
			(float)glutGet(GLUT_WINDOW_HEIGHT) / WIN_HEIGHT * 3.f - app->cameraY,
			0.001f, 1000);
	gluLookAt(app->cameraX, app->cameraY, app->cameraZ, //Position of the camera
		app->cameraX + cosf(app->cameraAngleH * (PI / 180.f)) + sinf(app->cameraAngleH * (PI / 180.f)), //Looking at X
		app->cameraY, //Looking at Y
		app->cameraZ + cosf(app->cameraAngleH * (PI / 180.f)) - sinf(app->cameraAngleH * (PI / 180.f)), //Looking at Z
		0, 1, 0);
	GLfloat params1[3] = { 1, 1, 1 };
	GLfloat params2 = 128;
	GLfloat params3 = 0;
	glLightfv(GL_LIGHT0, GL_DIFFUSE,				params1);
	glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT,			&params2);
	glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION,	&params3);
	//Gizmo
	glPushMatrix();
	glTranslatef(0, 0, -6.f);
	// glRotatef(app->angle, 0.0, 1.0f, 0.f);
	draw::drawGizmo();
	glPopMatrix();



	//Cone
	glPushMatrix();
	glTranslatef(1, -1, -3.f);
	glRotatef(app->angle, 1.0f, 1.0f, 0.f);
	draw::drawCone(5);
	glPopMatrix();

	//Sphere
	glPushMatrix();
	glTranslatef(-1.0, 1.0, -3.f);
	glRotatef(app->angle, 1.0, 0.0f, 1.0f);
	draw::drawSphere(35, 35); //ACTUAL SPHERE DRAWING
	glPopMatrix();


	//Cube
	glPushMatrix();
	glTranslatef(2.0, 2.0, -5.f);
	glRotatef(app->angle, 1.0, 0.0f, 1.0f);
	draw::drawCube(10, 10, 30); //ACTUAL CUBE DRAWING
	glPopMatrix();


	//Quad
	//2D Shapes aren't rotating for visual clarity reasons.
	glBindTexture(GL_TEXTURE_2D, app->tex);
	glPushMatrix();
	glTranslatef(0.0, 2.0, -7.f);
	draw::drawQuad(0.5f); //Actual Quad Drawing
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);

	//Triangle
	//2D Shapes aren't rotating for visual clarity reasons.
	glPushMatrix();
	glTranslatef(0, -1.5f, -5.f);
	draw::drawTriangle();
	glPopMatrix();

	//Point Sphere
	glPushMatrix();
	glTranslatef(-1.0, -1.0, -3.f);
	glRotatef(app->angle, 1.0, 0.0f, 1.0f);
	draw::drawPointSphere(50, 50); //Actual Point Sphere Drawing
	glPopMatrix();

	draw::drawMaze(app->tex);

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
