#version 330

layout (location = 0) in vec3 a_vertex;
layout (location = 1) in vec3 a_normal;

uniform mat4 u_p;
uniform mat4 u_v;
uniform mat4 u_m;

out vec3 var_fcolor;
out vec3 var_normal;
out vec3 var_newPos;

void main(void)
{
    vec4 newPos4 = u_m * vec4(a_vertex, 1.0);
    var_newPos = newPos4.xyz;
    var_fcolor = vec3(1, 0, 0);
    var_normal = normalize(mat3(transpose(inverse(u_m))) * a_normal);
    gl_Position = u_p * u_v * newPos4;
}
