#version 330

layout (location = 0) in vec3 a_vertex;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uv;

uniform mat4 u_p;
uniform mat4 u_v;
uniform mat4 u_m;

out vec3 var_newPos;
out vec3 var_normal;
out vec2 var_uv;

void main(void)
{
    vec4 newPos4 = u_m * vec4(a_vertex, 1.0);
    var_newPos = newPos4.xyz;
    var_normal = normalize(mat3(transpose(inverse(u_m))) * a_normal);
    var_uv = a_uv;
    gl_Position = u_p * u_v * newPos4;

}
