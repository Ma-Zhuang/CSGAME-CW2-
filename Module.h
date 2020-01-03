#pragma once
#include<string>
#include"Shader.h"
#include"Mesh.h"
class Module
{
public:
	void Moduleload(std::string path, std::string textureName);
	Module() {}
	~Module();
	void setUpMesh();
	Vertex* v = new Vertex();
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_textCoords;
	std::vector<glm::vec3> temp_normals;
	VertexCombineIndex vertComIndex;
	void Draw_Module(Shader* shader);
	//There are many mesh in an obj. Mesh is based on the sequence of read materials
	std::vector<Mesh> meshs;
	//Mesh used for reading
	Mesh mesh;
};

