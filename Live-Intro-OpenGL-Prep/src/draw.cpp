#include "draw.h"
#include <math.h>
#define PI 3.141592f

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

void drawResQuad(float resolutionX, float resolutionY)
{
    float startX = -0.5f; float startY = -0.5f;
    float useX = startX; float useY = startY;
    for (int y = 0; y != resolutionY; y++)
    {
        for (int x = 0; x != resolutionX; x++)
        {
            glBegin(GL_QUADS);
            glColor3f(((x + y) % 2) + 0.5f, 0, 0);
            glVertex3f(useX, useY, 0.5f);
            glColor3f(((x + y) % 2) + 0.5f, 0, 0);
            glVertex3f(useX + 1.f / resolutionX, useY, 0.5f);
            glColor3f(((x + y) % 2) + 0.5f, 0, 0);
            glVertex3f(useX + 1.f / resolutionX, useY + 1.f / resolutionY, 0.5f);
            glColor3f(((x + y) % 2) + 0.5f, 0, 0);
            glVertex3f(useX, useY + 1.f / resolutionY, 0.5f);

            glEnd();
            useX += 1.f / resolutionX;
        }
        useY += 1 / resolutionY;
        useX = startX;
    }
}

// Draw a cube (res = number of subdivision on each axes)
void draw::drawCube(float resolutionX, float resolutionY, float resolutionZ)
{
    //drawResQuad(resolutionX, resolutionY, resolutionZ);
    for (int i = 0; i < 2; i++)
    {
        glRotatef(i*90+90, 0, 1, 0);
        drawResQuad(resolutionX, resolutionY);
    }
    for (int i = 0; i < 4; i++)
    {
        glRotatef(i * 90, 0, 1, 0);
        drawResQuad(resolutionZ, resolutionY);
    }
    for (int i = 0; i < 2; i++)
    {
        glRotatef(i * 90 + 90, 1, 0, 0);
        drawResQuad(resolutionZ, resolutionY);
    }
}

// Draw sphere (longitudes, lattitudes)
void draw::drawSphere(int longitudeResolution, int latitudeResolution, int kind)
{
    int i, j;
    float radius = 0.5f;
    float color = 1.f;
    float color2 = 0.f;
    for(i = 0; i <= latitudeResolution; i++) {
        float latitude = PI * (-0.5 + (float) (i - 1) / latitudeResolution);
        float z0  = sin(latitude);
        float zr0 =  cos(latitude);

        float latitude1 = PI * (-0.5 + (float) i / latitudeResolution);
        float z1 = sin(latitude1);
        float zr1 = cos(latitude1);
        
        glBegin(kind);
        for(j = 0; j <= longitudeResolution; j++) {
            float longitude = 2 * PI * (float) (j - 1) / longitudeResolution;
            float x = cos(longitude);
            float y = sin(longitude);

            glNormal3f(x * zr0, y * zr0, z0);
            glColor3f(color2, 0, color);
            glVertex3f(radius * x * zr0, radius * y * zr0, radius * z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glColor3f(color2, 0, color);
            glVertex3f(radius * x * zr1, radius * y * zr1, radius * z1);
            if (color == 1.f)
            {
                color = 0.f;
                color2 = 1.f;
            }
            else
            {
                color = 1.f;
                color2 = 0.f;
            }
        }
        glEnd();
        
    }
}

// Draw a sphere with points
void draw::drawPointSphere(int longitudeResolution, int latitudeResolution)
{
    drawSphere(longitudeResolution, latitudeResolution, GL_POINTS);
}

// Draw cone primitive (res = )
void draw::drawCone(int res);

// Draw gizmo (3 axes from 0.0 to 1.0 of different color)
void draw::drawGizmo();