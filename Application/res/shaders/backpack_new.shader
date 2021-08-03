#vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	TexCoord = aTexCoords;
	FragPos = vec3(model * vec4(aPos, 1.0f));
	Normal = normalMatrix * aNormal;
}

#fragment
#version 330 core

struct Material
{
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
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

	vec3 ambient = vec3(0.2f) * vec3(texture(material.texture_diffuse1, TexCoord));
	
	vec3 specular = vec3(1.0f) * spec * vec3(texture(material.texture_specular1, TexCoord));

	vec3 diffuse = vec3(0.8f) * diff * vec3(texture(material.texture_diffuse1, TexCoord));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	FragColor = vec4(ambient + diffuse + specular, 1.0f);
}