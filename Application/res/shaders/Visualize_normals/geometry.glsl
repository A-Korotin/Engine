#version 410 core
layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

in VS_OUT
{
	vec3 Normal;
} gs_in[];

uniform float MAGNITUDE;

uniform mat4 projection;

void GenerateLine(int index)
{
	gl_Position = projection * gl_in[index].gl_Position;
	EmitVertex();
	gl_Position = projection * (gl_in[index].gl_Position + vec4(gs_in[index].Normal, 0.0f) * MAGNITUDE);
	EmitVertex();
	EndPrimitive();
}

void main()
{
	for(int i = 0; i < 3; i++)
		GenerateLine(i);
}