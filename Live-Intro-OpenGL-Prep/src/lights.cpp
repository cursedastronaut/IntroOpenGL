#include "lights.h"

Light::Light(float3 pos, int light_index, lightsParam ambientLight, lightsParam diffuseLight, lightsParam specularLight, float shininessLight)
{
	position[0] = pos.x; 
	position[1] = pos.y; 
	position[2] = pos.z;
	position[3] = 1.f;

	index = light_index;
	ambient[0] = ambientLight.r;
	ambient[1] = ambientLight.g;
	ambient[2] = ambientLight.b;
	ambient[3] = ambientLight.a;

	diffuse[0] = diffuseLight.r;
	diffuse[1] = diffuseLight.g;
	diffuse[2] = diffuseLight.b;
	diffuse[3] = diffuseLight.a;

	specular[0] = specularLight.r;
	specular[1] = specularLight.g;
	specular[2] = specularLight.b;
	specular[3] = specularLight.a;
	shininess = shininessLight;
};

void Light::Update()
{
	glLightfv(index, GL_AMBIENT, ambient);
	glLightfv(index, GL_DIFFUSE, diffuse);
	glLightfv(index, GL_SPECULAR, specular);
	glLightfv(index, GL_POSITION, position);
	glEnable(index);
	draw::drawCubeNoRes(
		{ position[0] - 0.1f, position[1] - 0.1f, position[2] - 0.1f },
		{ position[0] + 0.1f, position[1] + 0.1f, position[2] + 0.1f },
		{ 1,1,1 },
		0,
		false
	);
}

void Light::changeAmbiant(lightsParam ambiantLight)
{
	ambient[0] = ambiantLight.r;
	ambient[1] = ambiantLight.g;
	ambient[2] = ambiantLight.b;
	ambient[3] = ambiantLight.a;
}
void Light::changeDiffuse(lightsParam diffuseLight)
{
	diffuse[0] = diffuseLight.r;
	diffuse[1] = diffuseLight.g;
	diffuse[2] = diffuseLight.b;
	diffuse[3] = diffuseLight.a;
}
void Light::changeSpecular(lightsParam specularLight)
{
	specular[0] = specularLight.r;
	specular[1] = specularLight.g;
	specular[2] = specularLight.b;
	specular[3] = specularLight.a;
}
void Light::changePos(float3 posLight)
{
	position[0] = posLight.x;
	position[1] = posLight.y;
	position[3] = posLight.z;
}