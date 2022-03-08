#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_uv;
layout(location = 2) in vec4 a_color;

out vec4 v_color;
out vec2 v_uv;

uniform  mat4 u_model_matrix;

void main()
{
    gl_Position = u_model_matrix * vec4(a_position.x, a_position.y, a_position.z, 1.0f);
    v_color = a_color;
    v_uv = a_uv;
}
