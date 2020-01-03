#version 450 core

in vec2 TextCoord;
in vec3 fragPos;
in vec3 aNormal;

uniform sampler2D tex;
out vec4 FragColor;

void main()
{    
    FragColor = texture(tex, TextCoord);
}