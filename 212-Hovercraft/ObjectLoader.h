#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

#include <glew.h>
#include <glfw3.h>
#include<glm.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Vertex.h"

static std::vector<Vertex> objectLoader(const char* file)
{
	// Main vectors for model loading - loading the verticies
	std::vector<glm::fvec3> positionOfVertex;
	std::vector<glm::fvec3> normalOfVertex;
	std::vector<glm::fvec2> texcoordOfVertex;

	//Other vectors - loading the indicies 
	std::vector<GLint> positionIndiciesOfVertex;
	std::vector<GLint> normalIndiciesOfVertex;
	std::vector<GLint> texcoordIndiciesOfVertex;

	//The vertex array
	std::vector<Vertex> vertices;
	std::stringstream strStr;
	std::ifstream inFile(file);

	std::string line = "";
	std::string prefixLine = "";

	glm::vec3 vec3Temporary;
	glm::vec2 vec2Temporary;
	GLint glintTemporary =0;

	//Going through all the lines one at a time
	while (std::getline(inFile, line))
	{
		//Getting the line prefix
		strStr.clear();
		strStr.str(line);
		strStr >> prefixLine;

		//If prefix is # do nothing
		if (prefixLine == "#")
		{

		}

		//If prefix is o do nothing
		else if (prefixLine == "o")
		{

		}

		//If prefix is s do nothing
		else if (prefixLine == "s")
		{

		}

		//If prefix is use_mtl do nothing
		else if (prefixLine == "use_mtl")
		{

		}

		//If the prefix is a v then it is a vertex position so we need to save it
		else if (prefixLine == "v")
		{
			strStr >> vec3Temporary.x >> vec3Temporary.y >> vec3Temporary.z;
			positionOfVertex.push_back(vec3Temporary);
		}
		
		//If the prefix is a vt then we will save 
		else if (prefixLine == "vt")
		{
			strStr >> vec2Temporary.x >> vec2Temporary.y;
			texcoordOfVertex.push_back(vec2Temporary);
		}

		//If the prefix is a vn then it is a normal so we want to save it 
		else if (prefixLine == "vn")
		{
			strStr >> vec3Temporary.x >> vec3Temporary.y>>vec3Temporary.z;
			normalOfVertex.push_back(vec3Temporary);
		}

		//If the prefix is an f then it is a face so we want to save the indicies in it
		else if (prefixLine == "f")
		{
			int counterValue = 0;
			while (strStr >> glintTemporary)
			{
				// Saving the values in their specific indicies vector
				if (counterValue == 0)
				{
					positionIndiciesOfVertex.push_back(glintTemporary);
				}
				else if (counterValue == 1)
				{
					texcoordIndiciesOfVertex.push_back(glintTemporary);
				}
				else if (counterValue == 2)
				{
					normalIndiciesOfVertex.push_back(glintTemporary);
				}

				//Skipping over the space and / characters
				if (strStr.peek() == '/')
				{
					counterValue++;
					strStr.ignore(1, '/');
				}
				else if (strStr.peek() == ' ')
				{
					counterValue++;
					strStr.ignore(1, ' ');
				}

				//Reset the counterValue, very important
				if (counterValue > 2)
				{
					counterValue = 0;
				}
			}
		}

		//Ignore anything else
		else
		{

		}

		//Building the final vertex array that will be used by the mesh function to create the mesh
		vertices.resize(positionIndiciesOfVertex.size(), Vertex());

		//saving all the indicies in
		for (size_t i = 0; i < vertices.size(); i++)
		{
			//Saving the position
			vertices[i].position = positionOfVertex[positionIndiciesOfVertex[i]-1];

			//Saving the texcoord
			vertices[i].texcoord = texcoordOfVertex[texcoordIndiciesOfVertex[i]-1];

			//Saving the normal
			vertices[i].normal = normalOfVertex[normalIndiciesOfVertex[i]-1];

			//Setting a colour 
			vertices[i].color = glm::vec3(1.f, 1.f, 1.f);
		}

	}

	//Returning the loaded model
	return vertices;
}

