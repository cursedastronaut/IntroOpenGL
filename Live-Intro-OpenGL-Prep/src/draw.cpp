#include "draw.h"
#include <math.h>
typedef struct float3 {
	float x, y, z;
};
typedef struct float2 {
	float x, y;
};

// Draw triangle with vertices at (-0.5, -0.5), (0.5, -0.5), (0.0, 0.5)
void draw::drawTriangle()
{
	glColor3f(1, 1, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glEnd();
}

// Draw quad centered (halfSize = 0.5)
void draw::drawQuad(float halfSize)
{

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0F, 0.0F);
	glVertex3f(-halfSize, halfSize, 0);
	glTexCoord2f(1.0F, 0.0F);
	glVertex3f(halfSize, halfSize, 0);
	glTexCoord2f(1.0F, 1.0F);
	glVertex3f(halfSize, -halfSize, 0);
	glTexCoord2f(0.0F, 1.0F);
	glVertex3f(-halfSize, -halfSize, 0);
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
		glRotatef(i * 90 + 90, 0, 1, 0);
		drawResQuad(resolutionX, resolutionY);
	}
	for (int i = 0; i < 3; i++)
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
	for (i = 0; i <= latitudeResolution; i++) {
		float latitude = PI * (-0.5 + (float)(i - 1) / latitudeResolution);
		float z0 = sin(latitude);
		float zr0 = cos(latitude);

		float latitude1 = PI * (-0.5 + (float)i / latitudeResolution);
		float z1 = sin(latitude1);
		float zr1 = cos(latitude1);

		glBegin(kind);
		for (j = 0; j <= longitudeResolution; j++) {
			float longitude = 2 * PI * (float)(j - 1) / longitudeResolution;
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


/*
// Draw cone primitive (res = )
void draw::drawCone(int res)
{
	GLUquadricObj* quadric = gluNewQuadric();
	glColor3f(0, 1, 1);
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluCylinder(quadric, 0.5, 0, 1, res, res);
	gluDeleteQuadric(quadric);
	for (int i = 0; i < 360; i+=20)
	{
		glRotatef(i, 0, 1, 0);
		glPushMatrix();
		glBegin(GL_QUADS);
		glVertex3f(0, 0, 1);
		glVertex3f(0, 1.0f, 1);
		glVertex3f(1, 1.0f, 1);
		glVertex3f(1, 0, 1);
		glEnd();
		glPopMatrix();
	}
}
*/

void draw::drawCone(int res)
{
	float radius = 0.5f;
	float height = 1;
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= res; i++) {
		float angle = (float)i / (float)res * PI * 2;
		glColor3f(((i) % 2) + 0.5f, 0, 0);
		glVertex3f(radius * cosf(angle), 0, sinf(angle) * radius);
		glVertex3f(0, height, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i <= res; i++) {
		float angle = (float)i / (float)res * PI * 2;
		glColor3f(((i) % 2) + 0.5f, 0, 0);
		glVertex3f(radius * cosf(angle), 0, sinf(angle) * radius);
	}
	glEnd();
}

// Draw gizmo (3 axes from 0.0 to 1.0 of different color)
void draw::drawGizmo()
{
	glLineWidth(1.f);
	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();
}

// Draw quad centered (halfSize = 0.5)
/*void drawQuad3D(float3 inPos, float3 endPos, float3 color)
{

	glBegin(GL_QUADS);
	glColor3f(color.x, color.y, color.z);
	glVertex3f(-inPos.x, inPos.y, inPos.z);
	glColor3f(color.x, color.y, color.z);
	glVertex3f(inPos.x, inPos.y, endPos.z);
	glColor3f(color.x, color.y, color.z);
	glVertex3f(endPos.x, endPos.y, endPos.z);
	glColor3f(color.x, color.y, color.z);
	glVertex3f(endPos.x, endPos.y, inPos.z);
	glEnd();
}*/

void textureOrColor(float3 color, float2 texture, bool isTexture)
{
	if (isTexture)
		glTexCoord2f(texture.x, texture.y);
	else
		glColor3f(color.x, color.y, color.z);
}

void drawQuad3D(float3 inPos, float3 endPos, float3 color, GLuint tex, bool isTexture = true)
{
	float3 vertices[] = {
		{inPos.x, inPos.y, inPos.z},
		{endPos.x, inPos.y, inPos.z},
		{endPos.x, endPos.y, endPos.z},
		{inPos.x, endPos.y, endPos.z}
	};

	float3 colors[] = {
		{color.x, color.y, color.z},
		{color.x, color.y, 255},
		{color.x, 255, color.z},
		{255, color.y, color.z},
	};

	

	if (endPos.y - inPos.y == 0)
		glNormal3f(0, 1, 0);
	else if (endPos.x - inPos.x == 0)
		glNormal3f(1, 0, 0);
	else if (endPos.z - inPos.z == 0)
		glNormal3f(0, 0, 1);


	if (isTexture)
		glBindTexture(GL_TEXTURE_2D, tex);
	glBegin(GL_QUADS);
	/*for (int i = 0; i < 4; i++)
	{
		glColor3f(colors[i].x, colors[i].y, colors[i].z);
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}*/
		glColor3f(1, 0, 1);
		textureOrColor(colors[0], { 0,0 }, isTexture);
		glVertex3f(inPos.x, inPos.y, endPos.z);
		if (endPos.x - inPos.x == 0)
		{
			textureOrColor(colors[1], { 1,0 }, isTexture);
			glVertex3f(endPos.x, inPos.y, inPos.z);
			textureOrColor(colors[2], { 1,1 }, isTexture);
			glVertex3f(endPos.x, endPos.y, inPos.z);
			textureOrColor(colors[3], { 0,1 }, isTexture);
			glVertex3f(inPos.x, endPos.y, endPos.z);
		}
		else
		{
			textureOrColor(colors[1], { 1,0 }, isTexture);
			glVertex3f(endPos.x, inPos.y, endPos.z);
			textureOrColor(colors[2], { 1,1 }, isTexture);
			glVertex3f(endPos.x, endPos.y, inPos.z);
			textureOrColor(colors[3], { 0,1 }, isTexture);
		glVertex3f(inPos.x, endPos.y, inPos.z);
		}
	glEnd();
	if (isTexture)
		glBindTexture(GL_TEXTURE_2D, 0);
}

//Draw Maze
void draw::drawMaze(GLuint tex)
{
	//Floor
	drawQuad3D({ 0,-1,0 }, { 5,-1,5 }, { 1,0,0 }, tex);

	//Walls
	drawQuad3D({ 0,-1,0 }, { 2 , 0 , 0 }, { 0,1,0 }, tex);	
	drawQuad3D({ 3,-1,0 }, { 5 , 0 , 0 }, { 0,1,0 }, tex);
	drawQuad3D({ 0,-1,0 }, { 0 , 0 , 5 }, { 0,1,0 }, tex);
	drawQuad3D({ 5,-1,0 }, { 5 , 0 , 5 }, { 0,1,0 }, tex);
	drawQuad3D({ 0,-1,5 }, { 2 , 0 , 5 }, { 0,1,0 }, tex);
	drawQuad3D({ 3,-1,5 }, { 5 , 0 , 5 }, { 0,1,0 }, tex);
	drawQuad3D({ 0,-1,4 }, { 1 , 0 , 4 }, { 0,1,0 }, tex);
	drawQuad3D({ 0,-1,2 }, { 1 , 0 , 2 }, { 0,1,0 }, tex);
	drawQuad3D({ 1,-1,1 }, { 2 , 0 , 1 }, { 0,1,0 }, tex);
	drawQuad3D({ 2,-1,2 }, { 4 , 0 , 2 }, { 0,1,0 }, tex);
	drawQuad3D({ 2,-1,4 }, { 4 , 0 , 4 }, { 0,1,0 }, tex);
	drawQuad3D({ 1,-1,3 }, { 3 , 0 , 3 }, { 0,1,0 }, tex);
	drawQuad3D({ 4,-1,1 }, { 5 , 0 , 1 }, { 0,1,0 }, tex);
	drawQuad3D({ 2,-1,5 }, { 2 , 0 , 4 }, { 0,1,0 }, tex);
	drawQuad3D({ 2,-1,3 }, { 2 , 0 , 2 }, { 0,1,0 }, tex);
	drawQuad3D({ 1,-1,2 }, { 1 , 0 , 1 }, { 0,1,0 }, tex);
	drawQuad3D({ 3,-1,1 }, { 3 , 0 , 2 }, { 0,1,0 }, tex);
	drawQuad3D({ 4,-1,2 }, { 4 , 0 , 4 }, { 0,1,0 }, tex);
}