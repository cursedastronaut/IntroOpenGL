#include "camera.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "GL/freeglut.h"
//Handles rendering mode switching, and the Camera Angle.
void Camera::Input()
{
	//ImGui::GetIO().AddKeyEvent();
	float speed = 0.01f;
	if (ImGui::IsKeyDown(ImGuiKey_LeftShift))
		speed *= 10;
	
	bool hasMoved = false;
	if (ImGui::IsKeyDown(ImGuiKey_P)) { orthoRendering = false; }
	if (ImGui::IsKeyDown(ImGuiKey_O)) { orthoRendering = true; }
	if (ImGui::IsKeyDown(ImGuiKey_N)) { angle++; }
	if (ImGui::IsKeyDown(ImGuiKey_M)) { angle--; }
	if (angle == 0) angle = 360.f;
	else if (angle > 360.f) angle -= 360.f;

	if (ImGui::IsKeyDown(ImGuiKey_S))
	{
		pos.x -= (std::cos(angle * (M_PI / 180.f)) + sinf(angle * (M_PI / 180.f))) * speed;
		pos.z -= (std::cos(angle * (M_PI / 180.f)) - sinf(angle * (M_PI / 180.f))) * speed;
		hasMoved = true;
	}
	if (ImGui::IsKeyDown(ImGuiKey_Z))
	{
		pos.x += (std::cos(angle * (M_PI / 180.f)) + sinf(angle * (M_PI / 180.f))) * speed;
		pos.z += (std::cos(angle * (M_PI / 180.f)) - sinf(angle * (M_PI / 180.f))) * speed;
		hasMoved = true;
	}
	if (ImGui::IsKeyDown(ImGuiKey_Q))
	{
		pos.x += (std::cos((angle + 90) * (M_PI / 180.f)) + sinf((angle + 90) * (M_PI / 180.f))) * speed;
		pos.z += (std::cos((angle + 90) * (M_PI / 180.f)) - sinf((angle + 90) * (M_PI / 180.f))) * speed;
		hasMoved = true;
	}
	if (ImGui::IsKeyDown(ImGuiKey_D))
	{
		pos.x += (std::cos((angle - 90) * (M_PI / 180.f)) + sinf((angle - 90) * (M_PI / 180.f))) * speed;
		pos.z += (std::cos((angle - 90) * (M_PI / 180.f)) - sinf((angle - 90) * (M_PI / 180.f))) * speed;
		hasMoved = true;
	}

	if (ImGui::IsKeyDown(ImGuiKey_LeftArrow))	{ pos.x -= 0.1f; }
	if (ImGui::IsKeyDown(ImGuiKey_UpArrow))		{ pos.y += 0.1f; }
	if (ImGui::IsKeyDown(ImGuiKey_RightArrow))	{ pos.x += 0.1f; }
	if (ImGui::IsKeyDown(ImGuiKey_DownArrow))	{ pos.y -= 0.1f; }
	
	if (hasMoved == true)
	{
		offsetI += 0.1f; 
		if (offsetI >= 360) offsetI = 0;
		offset = std::cos(offsetI) * 0.1f;
	}
}

void Camera::Update()
{
	Input();
	if (!orthoRendering)
	{
		gluPerspective(60, (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT), 0.001f, 1000);
	}
	else
		glOrtho(-(float)glutGet(GLUT_WINDOW_WIDTH) / WIN_WIDTH * 3.f - pos.x, //TODO: Remove 1024 and 576 and simply put the original height and width.
			 (float)glutGet(GLUT_WINDOW_WIDTH) / WIN_WIDTH * 3.f - pos.x,
			-(float)glutGet(GLUT_WINDOW_HEIGHT) / WIN_HEIGHT * 3.f - pos.y,
			 (float)glutGet(GLUT_WINDOW_HEIGHT) / WIN_HEIGHT * 3.f - pos.y,
			 0.001f, 1000);



}

void Camera::LookAt()
{
	lookAtpos.x = pos.x + std::cos(angle * (M_PI / 180.f)) + sinf(angle * (M_PI / 180.f)); //Looking at X
	lookAtpos.y = pos.y + offset; //Looking at Y
	lookAtpos.z = pos.z + std::cos(angle * (M_PI / 180.f)) - sinf(angle * (M_PI / 180.f)); //Looking at Z

	gluLookAt(pos.x, pos.y+offset, pos.z, //Position of the camera
		lookAtpos.x, lookAtpos.y, lookAtpos.z, 
		0, 1, 0);
}