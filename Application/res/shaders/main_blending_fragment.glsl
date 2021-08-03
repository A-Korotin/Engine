#version 410 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;


uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture0, TexCoord);
}