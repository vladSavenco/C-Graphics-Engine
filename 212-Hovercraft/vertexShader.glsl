#version 460

//The order that the shader looks at the float array from the vertex data and decides what is what
layout (location =0) in vec3 vertex_position;
layout (location =1) in vec3 vertex_color;
layout (location =2) in vec2 vertex_texcoord;
layout (location =3) in vec3 vertex_normal;

//Sends stuff out to the fragment shader
out vec3 vecposition;
out vec3 veccolor;
out vec2 vectexcoord;
out vec3 vecnormal;

//Seting the uniforms
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
	//Position
	vecposition=vec4(ModelMatrix * vec4(vertex_position,1.f)).xyz;
	//Colour
	veccolor=vertex_color;
	//TexCoord
	vectexcoord=vec2(vertex_texcoord.x,vertex_texcoord.y* -1.f);
	//Normal, needs to be in local space as well as world space
	vecnormal=mat3(ModelMatrix) * vertex_normal;

	gl_Position =ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vertex_position, 1.f);
}