attribute highp vec3 a_vertex;
attribute highp vec3 a_fcolor;

uniform highp mat4 u_p;
uniform highp mat4 u_v;
uniform highp mat4 u_m;

varying highp vec4 var_fcolor;

void main(void)
{
    gl_Position = u_p * u_v * u_m * vec4(a_vertex, 1.0f);
//    gl_Position = vec4(a_vertex, 1.0f);
    var_fcolor = vec4(a_fcolor, 1.0f);
}
