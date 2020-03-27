#include "Model.h"

void Model::updateUniforms()
{
}

Model::Model(glm::vec3 mainPosition, Material* material, Texture* TexDiffuse, Texture* TexSpecular, std::vector<Mesh*> meshes)
{
	this->mainPosition = mainPosition;
	this->material = material;
	this->TexDiffuse = TexDiffuse;
	this->TexSpecular = TexSpecular;

	//c++ 11 for loop, way faster, it will go through all the meshes
	for (auto*i : meshes)
	{
		this->meshes.push_back(new Mesh(*i));
	}

	for (auto& i : this->meshes)
	{
		i->move(this->mainPosition);
		i->setOriginPos(this->mainPosition);
	}
}

Model::~Model()
{
	for (auto*& i : this->meshes)
	{
		delete i;
	}
}

void Model::rotate(const glm::vec3 rotation)
{
	for (auto& i: this->meshes)
	{
		i->rotate(rotation);
	}
}

void Model::move(const glm::vec3 moveVec)
{
	for (auto& i : this->meshes)
	{
		i->move(moveVec);
	}
}

void Model::moveModel(const glm::vec3 movement)
{
	for (auto& i : this->meshes)
	{
		i->moveOriginPos(movement);
	}
}


void Model::update()
{

}

void Model::render(Shader* shader)
{
	//Update the uniforms
	this->updateUniforms();

	//Update the uniforms
	this->material->sendToShader(*shader);

	//Use the shader program
	shader->use();

	//Binding the textures
	this->TexDiffuse->bind(0);
	this->TexSpecular->bind(1);

	//Draw
	for (auto& i : this->meshes)
	{
		//Activate the texture for each mesh that needs it
		this->TexDiffuse->bind(0);
		this->TexSpecular->bind(1);

		i->render(shader);
	}
}
