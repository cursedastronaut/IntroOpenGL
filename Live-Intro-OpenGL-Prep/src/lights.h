#pragma once
#include "app.h"
#include "draw.h"
#define LIGHT_AMBIANT_DEFAULT { 0.1f, 0.1f, 0.1f, 1.0f }
#define LIGHT_DIFFUSE_DEFAULT { 0.7f, 0.7f, 0.7f, 100.f }
#define LIGHT_SPECULAR_DEFAULT { 0.2f, 0.2f, 0.2f, 1.0f }
#define LIGHT_SPECREF_DEFAULT { 1.0f, 1.0f, 1.0f, 1.0f }

typedef struct lightsParam {
	float r, g, b, a;
};

class Light
{
	public:
		Light(float3 pos, int light_index,
			lightsParam ambientLight = LIGHT_AMBIANT_DEFAULT,
			lightsParam diffuseLight = LIGHT_DIFFUSE_DEFAULT,
			lightsParam specularLight = LIGHT_SPECULAR_DEFAULT,
			float shininess = 0);
		void changeAmbiant(lightsParam ambiant);
		void changeDiffuse(lightsParam diffuse);
		void changeSpecular(lightsParam specular);
		void changeSpecref(lightsParam specref);
		void changePos(float3 pos);
		void Update();
	private:
		float	ambient[4] = LIGHT_AMBIANT_DEFAULT;
		float	diffuse[4] = LIGHT_DIFFUSE_DEFAULT;
		float	specular[4] = LIGHT_SPECULAR_DEFAULT;
		float	position[4] = { 0.0f, 0.0f, 0.f, 0 };
		float	shininess = 1;
		int		index;
};