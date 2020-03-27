#pragma once

#include<iostream>
#include<vector>

#include <gtc\matrix_transform.hpp>

#include "Texture.h"
#include "BasicShapes.h"
#include "Material.h"
#include "Vertex.h"
#include "Shader.h"

class Mesh
{
private:
	//Making the mesh keep its own vertex data
	Vertex* vertexArray;
	unsigned nrOfVertices;
	GLuint* indexArray;
	unsigned nrOfIndices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	//Pos,Origin,rotation,scale values
	glm::vec3 position;
	glm::vec3 originPos;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 ModelMatrix;

	void initVAO();

	void updateUniforms(Shader* shader);

	void updateModelMatrix();

public:
	Mesh(BasicShapes* primitive, glm::vec3 position, glm::vec3 originPos, glm::vec3 rotation, glm::vec3 scale);

	Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndicies, glm::vec3 position, glm::vec3 originPos, glm::vec3 rotation, glm::vec3 scale);

	Mesh(const Mesh& obj);

	~Mesh();

	//Movement for initial placement
	void setOriginPos(const glm::vec3& originPos);

	void setPosition(const glm::vec3& position);

	void setRotation(const glm::vec3& rotation);

	void setScale(const glm::vec3 setScale);

	//Movement Functions - to be used with key presses
	void move(const glm::vec3 position);

	void rotate(const glm::vec3 rotation);

	void scaleMesh(const glm::vec3 scale);

	void moveOriginPos(glm::vec3 move);

	//Update and Render
	void update();

	void render(Shader* shader);

};