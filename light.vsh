#version 330

layout (location = 0) in vec3 a_vertex;
layout (location = 1) in vec3 a_normal;

uniform mat4 u_p;
uniform mat4 u_v;
uniform mat4 u_m;

void main(void)
{
    gl_Position = u_p * u_v * u_m * vec4(a_vertex, 1.0);
}
