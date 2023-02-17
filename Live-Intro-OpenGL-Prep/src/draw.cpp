#include "draw.h"
#include <math.h>


void vertexAndNormal(GLfloat x, GLfloat y, GLfloat z)
{
	glNormal3f(x, y, z);
	glVertex3f(x, y, z);
}
void vertexAndNormal(float3 pos)
{
	vertexAndNormal(pos.x, pos.y, pos.z);
}

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
	glVertex3f(-halfSize, -halfSize, 0);
	glTexCoord2f(1.0F, 0.0F);
	glVertex3f(halfSize, -halfSize, 0);
	glTexCoord2f(1.0F, 1.0F);
	glVertex3f(halfSize, halfSize, 0);
	glTexCoord2f(0.0F, 1.0F);
	glVertex3f(-halfSize, halfSize, 0);
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
			vertexAndNormal(useX, useY, 0.5f);
			glColor3f(((x + y) % 2) + 0.5f, 0, 0);
			vertexAndNormal(useX + 1.f / resolutionX, useY, 0.5f);
			glColor3f(((x + y) % 2) + 0.5f, 0, 0);
			vertexAndNormal(useX + 1.f / resolutionX, useY + 1.f / resolutionY, 0.5f);
			glColor3f(((x + y) % 2) + 0.5f, 0, 0);
			vertexAndNormal(useX, useY + 1.f / resolutionY, 0.5f);

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
	float radius = 0.5f;
	float color = 1.f;
	float color2 = 0.f;
	for (int i = 0; i <= latitudeResolution; i++) {
		float latitude = PI * (-0.5 + (float)(i - 1) / latitudeResolution);
		float par1 = sin(latitude);
		float par2 = cos(latitude);

		float latitude1 = PI * (-0.5 + (float)i / latitudeResolution);
		float par3 = sin(latitude1);
		float par4 = cos(latitude1);

		glBegin(kind);
		for (int j = 0; j <= longitudeResolution; j++) {
			float longitude = 2 * PI * (float)(j - 1) / longitudeResolution;
			float x = cos(longitude);
			float y = sin(longitude);

			glNormal3f(x * par2, y * par2, par1);
			glColor3f(color2, 0, color);
			glVertex3f(radius * x * par2, radius * y * par2, radius * par1);
			glNormal3f(x * par4, y * par4, par3);
			glColor3f(color2, 0, color);
			glVertex3f(radius * x * par4, radius * y * par4, radius * par3);
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

//Draw a cone
void draw::drawCone(int res)
{
	float radius = 0.5f;
	float height = 1;
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= res; i++) {
		float angle = (float)i / (float)res * PI * 2;
		glColor3f(((i) % 2) + 0.5f, 0, 0);
		vertexAndNormal(radius * cosf(angle), 0, sinf(angle) * radius);
		glNormal3f(0, height, 0);
		glVertex3f(0, height, 0);

	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i <= res; i++) {
		float angle = (float)i / (float)res * PI * 2;
		glColor3f(((i) % 2) + 0.5f, 0, 0);
		vertexAndNormal(radius * cosf(angle), 0, sinf(angle) * radius);
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



void textureOrColor(float3 color, float2 texture, bool isTexture)
{
	if (isTexture)
		glTexCoord2f(texture.x, texture.y);
	else
		glColor3f(color.x, color.y, color.z);
}



void draw::drawQuad3D(float3 inPos, float3 endPos, float3 color, GLuint tex, bool isTexture)
{
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

void draw::drawCubeNoRes(float3 inPos, float3 endPos, float3 color, GLuint tex, bool isTexture)
{
	//Face
	draw::drawQuad3D(inPos, { endPos.x, endPos.y, inPos.z }, color, tex, isTexture);
	//Floor
	draw::drawQuad3D(inPos, { endPos.x, inPos.y, endPos.z }, color, tex, isTexture);
	//Back
	draw::drawQuad3D(endPos, { inPos.x, inPos.y, endPos.z }, color, tex, isTexture);
	//Roof
	draw::drawQuad3D({inPos.x, endPos.y, inPos.z}, { endPos.x, endPos.y, endPos.z }, color, tex, isTexture);
	//Wall 1
	draw::drawQuad3D(inPos, {inPos.x, endPos.y, endPos.z}, color, tex, isTexture);
	//Wall 2
	draw::drawQuad3D({endPos.x, inPos.y, inPos.z}, { endPos.x, endPos.y, endPos.z }, color, tex, isTexture);


}

//Draw Maze
void draw::drawMaze(GLuint tex)
{
	//Floor
	drawQuad3D({ 0,-1,0 }, { 5,-1,5 }, { 1,0,0 }, tex);

	//Walls
	drawCubeNoRes({ 0,-1,0 }, { 2 , 0 , 0.1f }, { 0,1,0 }, tex);
	drawCubeNoRes({ 3,-1,0 }, { 5 , 0 , 0.1f }, { 0,1,0 }, tex);
	drawCubeNoRes({ 0,-1,0 }, { 0 , 0 , 5.1f }, { 0,1,0 }, tex);
	drawCubeNoRes({ 5,-1,0 }, { 5.1f , 0 , 5 }, { 0,1,0 }, tex);
	drawCubeNoRes({ 0,-1,5 }, { 2 , 0 , 5.1f }, { 0,1,0 }, tex);
	drawCubeNoRes({ 3,-1,5 }, { 5 , 0 , 5.1f }, { 0,1,0 }, tex);
	drawCubeNoRes({ 0,-1,4 }, { 1 , 0 , 4.1f }, { 0,1,0 }, tex);
	drawCubeNoRes({ 0,-1,2 }, { 1 , 0 , 2.1f }, { 0,1,0 }, tex);
	drawCubeNoRes({ 1,-1,1 }, { 2 , 0 , 1.1f }, { 0,1,0 }, tex);
	drawCubeNoRes({ 2,-1,2 }, { 4 , 0 , 2.1f }, { 0,1,0 }, tex);
	drawCubeNoRes({ 2,-1,4 }, { 4 , 0 , 4.1f }, { 0,1,0 }, tex);
	drawCubeNoRes({ 1,-1,3 }, { 3 , 0 , 3.1f }, { 0,1,0 }, tex);
	drawCubeNoRes({ 4,-1,1 }, { 5 , 0 , 1.1f }, { 0,1,0 }, tex);
	drawCubeNoRes({ 2,-1,5 }, { 2.1f , 0 , 4 }, { 0,1,0 }, tex);
	drawCubeNoRes({ 2,-1,3 }, { 2.1f , 0 , 2 }, { 0,1,0 }, tex);
	drawCubeNoRes({ 1,-1,2 }, { 1.1f , 0 , 1 }, { 0,1,0 }, tex);
	drawCubeNoRes({ 3,-1,1 }, { 3.1f , 0 , 2 }, { 0,1,0 }, tex);
	drawCubeNoRes({ 4,-1,2 }, { 4.1f , 0 , 4 }, { 0,1,0 }, tex);

	drawCubeNoRes({ 0,0,6 }, { 1,1,7 }, { 0,1,0 }, tex);
}



//WARNING!!
//This part was done after the project was finished. It is not meant to be marked.
void draw::drawGun(float3 inPos, float3 endPos, float3 color, GLuint tex, bool isTexture)
{
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
	glColor3f(1, 0, 1);
	textureOrColor(colors[0], { 0,1 }, isTexture);
	glVertex3f(inPos.x, inPos.y, endPos.z);
	if (endPos.x - inPos.x == 0)
	{
		textureOrColor(colors[1], { 1,1 }, isTexture);
		glVertex3f(endPos.x, inPos.y, inPos.z);
		textureOrColor(colors[2], { 1,0 }, isTexture);
		glVertex3f(endPos.x, endPos.y, inPos.z);
		textureOrColor(colors[3], { 0,0 }, isTexture);
		glVertex3f(inPos.x, endPos.y, endPos.z);
	}
	else
	{
		textureOrColor(colors[1], { 1,1 }, isTexture);
		glVertex3f(endPos.x, inPos.y, endPos.z);
		textureOrColor(colors[2], { 1,0 }, isTexture);
		glVertex3f(endPos.x, endPos.y, inPos.z);
		textureOrColor(colors[3], { 0,0 }, isTexture);
		glVertex3f(inPos.x, endPos.y, inPos.z);
	}
	glEnd();
	if (isTexture)
		glBindTexture(GL_TEXTURE_2D, 0);
}