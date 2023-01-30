#include "draw.h"

// Draw triangle with vertices at (-0.5, -0.5), (0.5, -0.5), (0.0, 0.5)
void draw::drawTriangle()
{
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glColor3f(1, 0, 0);
    glVertex3f(0.5f, -0.5f, 0.0f);
    glColor3f(1, 0, 0);
    glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();
}

// Draw quad centered (halfSize = 0.5)
void draw::drawQuad(float halfSize)
{
    glBegin(GL_TRIANGLES);
    glColor3f(0, 1, 0);
    glVertex3f(halfSize, halfSize, 1.0f);
    glColor3f(0, 1, 0);
    glVertex3f(halfSize, -halfSize, 1.0f);
    glColor3f(0, 1, 0);
    glVertex3f(-halfSize, halfSize, 1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0, 1, 0);
    glVertex3f(-halfSize, -halfSize, 1.0f);
    glColor3f(0, 1, 0);
    glVertex3f(-halfSize, halfSize, 1.0f);
    glColor3f(0, 1, 0);
    glVertex3f(halfSize, -halfSize, 1.0f);
    glEnd();
}

// Draw a cube (res = number of subdivision on each axes)
void draw::drawCube(float resolutionX, float resolutionY, float resolutionZ)
{
    //Facing the camera
    float startX = -0.5f; float startY = -0.5f;
    float useX = startX; float useY = startY;
    for (int y = 0; y != resolutionY; y++)
    {
        for (int x = 0; x != resolutionX; x++)
        {
            glBegin(GL_QUADS);
                    glColor3f(0, 1, 0);
                glVertex3f(useX, useY, 1.0f);
                    glColor3f(0, 1, 0);
                glVertex3f(useX + 1.f / resolutionX, useY, 1.0f);
                    glColor3f(0, 1, 0);
                glVertex3f(useX + 1.f/ resolutionX, useY + 1.f/ resolutionY, 1.0f);
                    glColor3f(0, 1, 0);
                glVertex3f(useX, useY + 1.f / resolutionY, 1.0f);
                    
            glEnd();
            useX += 1.f / resolutionX;
        }
        useY += 1 / resolutionY;
        useX = startX;
    }
    
    
}

// Draw sphere (longitudes, lattitudes)
void draw::drawSphere(int longitudeResolution, int latitudeResolution);

// Draw a sphere with points
void draw::drawPointSphere(int longitudeResolution, int latitudeResolution);

// Draw cone primitive (res = )
void draw::drawCone(int res);

// Draw gizmo (3 axes from 0.0 to 1.0 of different color)
void draw::drawGizmo();