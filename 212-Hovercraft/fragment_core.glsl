#version 440

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

in vec3 vecposition;
in vec3 veccolor;
in vec2 vectexcoord;
in vec3 vecnormal;

out vec4 fcolor;

//Uniforms
uniform Material material;
uniform vec3 lightPos0;
uniform vec3 cameraPos;

//Functions
vec3 calculateAmbient(Material material)
{
	return material.ambient;
}

vec3 calculateDiffuse(Material material, vec3 vecposition, vec3 vecnormal, vec3 lightPos0)
{
	vec3 posToLightDirVec =normalize(lightPos0-vecposition);
	float diffuse = clamp(dot(posToLightDirVec, vecnormal), 0, 1);
	vec3 finalDiffuse = material.diffuse * diffuse;

	return finalDiffuse;
}

vec3 calculateSpecular(Material material, vec3 vecposition, vec3 vecnormal, vec3 lightPos0, vec3 cameraPos)
{
	vec3 lightToPosDirVec= normalize(vecposition-lightPos0);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec,normalize(vecnormal)));
	vec3 posToViewDirVec = normalize(cameraPos-vecposition);
	float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec),0),30);
	vec3 finalSpecular= material.specular* specularConstant *texture(material.specularTex, vectexcoord).rgb;

	return finalSpecular;
}

void main()
{
	//Ambient Light
	vec3 finalAmbient = calculateAmbient(material);

	//Diffuse Light
	vec3 finalDiffuse = calculateDiffuse(material, vecposition, vecnormal, lightPos0);

	//Specular Light
	vec3 finalSpecular= calculateSpecular(material, vecposition, vecnormal, lightPos0, cameraPos);

	//Final light
	fcolor =texture(material.diffuseTex, vectexcoord)* (vec4(finalAmbient,1.f)+vec4(finalDiffuse,1.f)+vec4(finalSpecular, 1.f));
}