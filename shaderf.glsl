#version 330

in vec4 var_fcolor;

out vec4 fragColor;

void main(void)
{
//    gl_FragColor = vec4(0.5f, 0.5f, 0.5f, 0.5);
    fragColor = var_fcolor;
}
