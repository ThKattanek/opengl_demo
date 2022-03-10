#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Camera
{
public:
	Camera(float fov, float width, float height);

	mat4 GetViewProj();
	void Update();

	void SetViewSize(float width, float height);

	void Translate(vec3 v);

private:
	mat4 projection;
	mat4 view;
	mat4 viewProj;

	float fov;
	float view_width;
	float view_height;
};

#endif // CAMERA_H
