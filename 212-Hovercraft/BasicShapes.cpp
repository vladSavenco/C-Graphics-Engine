#include "BasicShapes.h"

BasicShapes::BasicShapes()
{
}

BasicShapes::~BasicShapes()
{
}

void BasicShapes::set(const Vertex* vertices, const unsigned nrOfVertices, const GLuint* indices, const unsigned nrOfIndices)
{
	for (size_t i = 0; i < nrOfVertices; i++)
	{
		this->vertices.push_back(vertices[i]);
	}

	for (size_t i = 0; i < nrOfIndices; i++)
	{
		this->indices.push_back(indices[i]);
	}
}

//Quad Class
Quad::Quad() : BasicShapes()
{
	Vertex vertices[] =
	{
		//Position                      //Color                         //Texcoords                 //Normals
		glm::vec3(-0.5f,0.5f,0.f),      glm::vec3(1.f,0.f,0.f),         glm::vec2(0.f,1.f),         glm::vec3(0.f,0.f,1.f),

		glm::vec3(-0.5f,-0.5f,0.f),     glm::vec3(0.f,1.f,0.f),         glm::vec2(0.f,0.f),         glm::vec3(0.f,0.f,1.f),

		glm::vec3(0.5f,-0.5f,0.f),      glm::vec3(0.f,0.f,1.f),         glm::vec2(1.f,0.f),         glm::vec3(0.f,0.f,1.f),

		glm::vec3(0.5f,0.5f,0.f),       glm::vec3(1.f,1.f,0.f),         glm::vec2(1.f,1.f),         glm::vec3(0.f,0.f,1.f)
	};
	unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

	GLuint indices[] =
	{
		0,1,2, //triangle 1
		0,2,3 //triangle 2
	};
	unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

	this->set(vertices,nrOfVertices,indices,nrOfIndices);
}

Triangle::Triangle()
{
	Vertex vertices[] =
	{
		//Position                      //Color                         //Texcoords                 //Normals
		glm::vec3(0.0f,0.5f,0.f),      glm::vec3(1.f,0.f,0.f),         glm::vec2(0.f,1.f),         glm::vec3(0.f,0.f,1.f),

		glm::vec3(-1.f,-1.0f,0.f),      glm::vec3(0.f,1.f,0.f),         glm::vec2(0.f,0.f),         glm::vec3(0.f,0.f,1.f),

		glm::vec3(1.0f,-1.0f,0.f),     glm::vec3(0.f,0.f,1.f),         glm::vec2(1.f,0.f),         glm::vec3(0.f,0.f,1.f),

	};
	unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

	GLuint indices[] =
	{
		0,1,2, //triangle 1
	};
	unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

	this->set(vertices, nrOfVertices, indices, nrOfIndices);
}

Pyramid::Pyramid()
{
	Vertex vertices[] =
	{
		//Position                      //Color                         //Texcoords                 //Normals
		//front
		glm::vec3(0.f, 0.5f, 0.f),		glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(0.5f, -0.5f, 0.5f),	glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),

		//left
		glm::vec3(0.f, 0.5f, 0.f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(-1.f, 0.f, 0.f),
		glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),
		glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),

		//back
		glm::vec3(0.f, 0.5f, 0.f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 0.f, -1.f),
		glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
		glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),

		//right
		glm::vec3(0.f, 0.5f, 0.f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.5f, -0.5f, 0.5f),	glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(1.f, 0.f, 0.f)
	};
	
	unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

	this->set(vertices, nrOfVertices, nullptr, 0);
	}
