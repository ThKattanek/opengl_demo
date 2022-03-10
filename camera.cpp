#include "camera.h"

Camera::Camera(float fov, float width, float height)
{
	this->fov = fov;
	this->view_width = width;
	this->view_height = height;
	projection = perspective(fov / 2.0f, width / height, 0.1f, 1000.0f);
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

void Camera::SetViewSize(float width, float height)
{
	this->view_width = width;
	this->view_height = height;
	projection = perspective(fov / 2.0f, width / height, 0.1f, 1000.0f);
	Update();
}

void Camera::Translate(vec3 v)
{
	view = translate(view, v*-1.0f);
}
