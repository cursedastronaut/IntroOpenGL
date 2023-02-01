// Live-Intro-OpenGL-Prep.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>

#include "src/draw.h"

float angle = 0.0;
void display();
void update(int value) {
    angle += 2.f;
    if (angle > 360) {
        angle -= 360;
    }

    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA); 
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("DPRK Forever <3");
    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0, 0, 0, 1);
    //draw::drawTriangle();
    //draw::drawCube(6, 3, 1);
    //reshape(2, 2);
    glLoadIdentity();
    gluPerspective(60, 1, 0.001f, 1000);
    glRotatef(angle, 1.0, 0.0f, 1.0f);
    glTranslatef(-1.0, 1.0, -3.f);
    draw::drawSphere(50,50);

    glTranslatef(1.0, 1.0, -3.f);
    draw::drawCube(100, 10, 30);
    //draw::drawQuad(0.5f);
    //draw::drawPointSphere(50,50);
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
