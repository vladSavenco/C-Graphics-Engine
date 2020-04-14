#version 460

layout (location =0) in vec3 vertex_position;
layout (location =1) in vec3 vertex_color;
layout (location =2) in vec2 vertex_texcoord;
layout (location =3) in vec3 vertex_normal;

out vec3 vecposition;
out vec3 veccolor;
out vec2 vectexcoord;
out vec3 vecnormal;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
	vecposition=vec4(ModelMatrix * vec4(vertex_position,1.f)).xyz;
	veccolor=vertex_color;
	vectexcoord=vec2(vertex_texcoord.x,vertex_texcoord.y* -1.f);
	vecnormal=mat3(ModelMatrix) * vertex_normal;

	gl_Position =ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vertex_position, 1.f);
}