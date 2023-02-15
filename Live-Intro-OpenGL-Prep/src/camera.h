#pragma once
#define WIN_HEIGHT 576
#define WIN_WIDTH 1024
#include <imgui/imgui.h>
#include "draw.h"


class Camera
{
public:
	Camera() {};
	void Input();
	void Update();
	float angle = 135;
	bool orthoRendering = 0;
	float offset = 0;
	float offsetI = 0;
	//Camera position
	float3 pos{ 2.5f, -0.5f, 7.f };
	float3 lookAtpos = { 0 };
	void LookAt();
};
