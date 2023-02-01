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
    glutInitWindowSize(1024, 576);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Intro - Galaad Martineaux (g.martineaux@student.isartdigital.com)");
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
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluPerspective(60, (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT), 0.001f, 1000);
    
    //Gizmo
    glPushMatrix();
    glTranslatef(0, 0, -6.f);
    glRotatef(angle, 0.0, 1.0f, 0.f);
    draw::drawGizmo();
    glPopMatrix();
    
    
    
    //Cone
    glPushMatrix();
    glTranslatef(1, -1, -3.f);
    glRotatef(angle, 1.0f, 1.0f, 0.f);
    draw::drawCone(5);
    glPopMatrix();

    //Sphere
    glPushMatrix();
    glTranslatef(-1.0, 1.0, -3.f);
    glRotatef(angle, 1.0, 0.0f, 1.0f);
    draw::drawSphere(35,35); //ACTUAL SPHERE DRAWING
    glPopMatrix();


    //Cube
    glPushMatrix();
    glTranslatef(2.0, 2.0, -5.f);
    glRotatef(angle, 1.0, 0.0f, 1.0f);
    draw::drawCube(100, 10, 30); //ACTUAL CUBE DRAWING
    glPopMatrix();

    //Quad
    glPushMatrix();
    glTranslatef(0.0, 2.0, -7.f);
    draw::drawQuad(0.5f); //Actual Quad Drawing
    glPopMatrix();
    
    //Triangle
    glPushMatrix();
    glTranslatef(0, -1.5f, -5.f);
    draw::drawTriangle();
    glPopMatrix();

    //Point Sphere
    glPushMatrix();
    glTranslatef(-1.0, -1.0, -3.f);
    glRotatef(angle, 1.0, 0.0f, 1.0f);
    draw::drawPointSphere(50,50); //Actual Point Sphere Drawing
    glPopMatrix();


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
