#pragma once
#include "freeglut/GL/freeglut.h"
namespace draw
{
    // Draw triangle with vertices at (-0.5, -0.5), (0.5, -0.5), (0.0, 0.5)
    void drawTriangle();
	
    // Draw quad centered (halfSize = 0.5)
    void drawQuad(float halfSize = 0.5f);
	
    // Draw a cube (res = number of subdivision on each axes)
    void drawCube(float resolutionX, float resolutionY, float resolutionZ);

    // Draw sphere (longitudes, lattitudes)
    void drawSphere(int longitudeResolution, int latitudeResolution);
	
    // Draw a sphere with points
    void drawPointSphere(int longitudeResolution, int latitudeResolution);
	
    // Draw cone primitive (res = )
    void drawCone(int res);
	
    // Draw gizmo (3 axes from 0.0 to 1.0 of different color)
    void drawGizmo();
};

