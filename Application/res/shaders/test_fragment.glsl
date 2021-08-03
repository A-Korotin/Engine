#version 410 core

struct Material
{
	sampler2D texture_diffuse0;
	sampler2D texture_specular0;
};

out vec4 FragColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform Material material;
uniform vec3 viewPos;
uniform vec3 lightPos;

void main()
{
	vec3 normal = normalize(Normal);

	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 lightDir = normalize(lightPos - FragPos);

	float diff = max(dot(normal, lightDir), 0.0f);

	vec3 reflectDir = reflect(-lightDir, normal);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);

	float distance = length(lightPos - FragPos);
	float attenuation = pow(1.0f + 0.045f * distance + 0.0075f * pow(distance, 2.0f), -1.0f);

	vec3 ambient = vec3(0.2f) * vec3(texture(material.texture_diffuse0, TexCoord));
	
	vec3 specular = vec3(1.0f) * spec * vec3(texture(material.texture_specular0, TexCoord));

	vec3 diffuse = vec3(0.8f) * diff * vec3(texture(material.texture_diffuse0, TexCoord));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	FragColor = vec4(ambient + diffuse + specular, 1.0f);
}