#pragma once
#include "GL/freeglut.h"
#include "app.h"
#define PI 3.141592f
typedef struct float3 {
    float x, y, z;
};
typedef struct float2 {
    float x, y;
};
namespace draw
{
    

    // Draw triangle with vertices at (-0.5, -0.5), (0.5, -0.5), (0.0, 0.5)
    void drawTriangle();
	
    // Draw quad centered (halfSize = 0.5)
    void drawQuad(float halfSize = 0.5f);
	
    // Draw a cube (res = number of subdivision on each axes)
    void drawCube(float resolutionX, float resolutionY, float resolutionZ);

    // Draw sphere (longitudes, lattitudes)
    void drawSphere(int longitudeResolution, int latitudeResolution, int kind = GL_QUAD_STRIP);
	
    // Draw a sphere with points
    void drawPointSphere(int longitudeResolution, int latitudeResolution);
	
    // Draw cone primitive (res = )
    void drawCone(int res);
	
    // Draw gizmo (3 axes from 0.0 to 1.0 of different color)
    void drawGizmo();

    //Draw Maze
    void drawMaze(GLuint tex);

    void drawQuad3D(float3 inPos, float3 endPos, float3 color, GLuint tex, bool isTexture = true);

    //WARNING!!
    //This part was done after the project was finished. It is not meant to be marked.
    void drawGun(float3 inPos, float3 endPos, float3 color, GLuint tex, bool isTexture = true);
    void drawCubeNoRes(float3 inPos, float3 endPos, float3 color, GLuint tex, bool isTexture = true);
};

