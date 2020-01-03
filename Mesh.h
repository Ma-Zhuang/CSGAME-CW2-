#pragma once
#include<vector>
#include<GL/glew.h>
#include<glm.hpp>
#include"Shader.h"



//model data
struct Vertex
{
	//Model vertex coordinates
	glm::vec3 position;
	//Model texture coordinates
	glm::vec2 texCoords;
	//Model normal coordinates
	glm::vec3 normal;
};

//Represents the position, texture coordinates and normal vector index of a vertex in the obj file
struct VertexCombineIndex
{
	// Vertex Index
	GLuint posIndex;
	// Texture Index
	GLuint textCoordIndex;
	// Normal vector
	GLuint normIndex;
};



class Mesh
{
public:
	
	Mesh() {}
	~Mesh();
	void Draw_Mesh(Shader* shader);
	//Data after model analysis
	std::vector<Vertex> vertData;
	int textureId = 0;
	void setUpMesh();
	std::string textureName;
private:
	unsigned int VAO, VBO;
};