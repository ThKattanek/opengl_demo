#include "camera.h"

Camera::Camera(float fov, float width, float height)
{
	projection = perspective(fov / 2.0f, width / height, 0.01f, 1000.0f);
	view = mat4(1.0f);
	Update();
}

mat4 Camera::GetViewProj()
{
	return viewProj;
}

void Camera::Update()
{
	viewProj = projection * view;
}

void Camera::Translate(vec3 v)
{
	view = translate(view, v*-1.0f);
}
