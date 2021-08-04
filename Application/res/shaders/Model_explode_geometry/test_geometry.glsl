#version 410 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT
{
	vec2 texCoord;
	vec3 Normal;
	vec3 FragPos;
} gs_in[];

uniform float time;
out vec2 TexCoord;

vec3 GetNormal()
{
	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	return normalize(cross(a, b));
}

vec4 explode(vec4 position, vec3 normal)
{
	float magnitude = 2.0f;
	vec3 direction = normal * ((sin(time) + 1.0f) / 2.0f) * magnitude;
	return position + vec4(direction, 0.0f);
}

void main()
{
	vec3 normal = GetNormal();

	gl_Position = explode(gl_in[0].gl_Position, normal);
	TexCoord = gs_in[0].texCoord;
	EmitVertex();
	gl_Position = explode(gl_in[1].gl_Position, normal);
	TexCoord = gs_in[1].texCoord;
	EmitVertex();
	gl_Position = explode(gl_in[2].gl_Position, normal);
	TexCoord = gs_in[2].texCoord;
	EmitVertex();
	EndPrimitive();
}