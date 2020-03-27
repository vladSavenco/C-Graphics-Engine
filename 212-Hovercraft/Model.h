#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"

class Model
{
private:
	Material* material;
	Texture* TexDiffuse;
	Texture* TexSpecular;
	std::vector<Mesh*> meshes;

	void updateUniforms();

public:
	glm::vec3 mainPosition;

	Model(glm::vec3 mainPosition, Material* material, Texture* TexDiffuse, Texture* TexSpecular, std::vector<Mesh*>meshes);

	~Model();

	//movement Functions
	void rotate(const glm::vec3 rotation);
	void move(const glm::vec3 moveVec);

	void moveModel(const glm::vec3 movement);

	//Rendering function
	void update();
	void render(Shader* shader);
};

