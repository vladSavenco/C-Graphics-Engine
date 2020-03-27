#pragma once

#include <glew.h>
#include <glfw3.h>

#include <vector>
#include "Vertex.h"

class BasicShapes
{
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

public:
	BasicShapes();
	virtual ~BasicShapes();

	void set(const Vertex* vertices, const unsigned nrOfVertices, const GLuint* indices, const unsigned nrOfIndices);

	inline Vertex* getVertices() { return this->vertices.data(); }
	inline GLuint* getIndices() { return this->indices.data(); }

	inline const unsigned getNrOfVertices() { return this->vertices.size(); }
	inline const unsigned getNrOfIndices() { return this->indices.size(); }
};

class Triangle : public BasicShapes
{
public:
	Triangle();
};

class Quad : public BasicShapes
{
public:
	Quad();
};

class Pyramid : public BasicShapes
{
public:
	Pyramid();
};
