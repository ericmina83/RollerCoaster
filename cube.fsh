#version 330

in vec3 var_fcolor;
in vec3 var_normal;
in vec3 var_newPos;

// the first output will become fragment color
// out float testColor; // R
// out vec2 testColor; // RG
// out vec3 testColor; // RGB
out vec4 testColor; // RGBA
out vec4 fragColor;

uniform vec3 u_light;
uniform vec3 u_eye;

void main(void)
{
    vec3 normal = normalize(var_normal);
    vec3 eye_dir = normalize(u_eye - var_newPos);
    vec3 light_dir = normalize(u_light - var_newPos);

    float ambient = 0.1;
    // float ambient = 0;

    float diffuse = max(dot(light_dir, normal), 0.0);
    // float diffuse = 0;

    float specular = 0.5 * pow(max(dot(reflect(-light_dir, normal), eye_dir), 0.0), 256);
    // float specular = 0;
    
    // gl_FragColor = (ambient + diffuse + specular) * vec4(var_fcolor, 1.0); // gl_FragColor still work
    fragColor = (ambient + diffuse + specular) * vec4(var_fcolor, 1.0);
    // testColor = vec4(0, 1, 0, 0);// RGBA
    // testColor = vec3(0, 1, 0);   // RGB
    // testColor = vec2(1, 0.5);    // RG
    // testColor = 0.5;             // R
}
