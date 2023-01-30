// Live-Intro-OpenGL-Prep.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "freeglut/GL/freeglut.h"

void display();

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA); 
    glutInitWindowSize(480, 360);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("DPRK Forever <3");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

void display() {
    glBegin(GL_TRIANGLES); 
    glColor3f(1, 1, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor3f(1, 0, 0);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0, 1, 1);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor3f(1, 0, 1);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glColor3f(0, 0, 1);
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor3f(1, 0, 0);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0, 0, 1);
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor3f(1, 0, 1);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glColor3f(0, 1, 1);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glEnd();

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
