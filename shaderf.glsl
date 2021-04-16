#version 140

varying highp vec4 var_fcolor;

void main(void)
{
//    gl_FragColor = vec4(0.5f, 0.5f, 0.5f, 0.5);
    gl_FragColor = var_fcolor;
}
