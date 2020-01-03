#include "Module.h"
#include<fstream>
#include<sstream>
#include<algorithm>
#include <glm.hpp>
#include <vector>
void Module::Moduleload(std::string path, std::string textureName)
{
	//Determine whether the file is loaded
	std::ifstream file(path);
	if (!file)
	{
		std::cerr << "Error::ObjLoader, could not open obj file:"
			<< path << " for reading." << std::endl;
	}
	std::string line;
	Mesh* tempmesh = new Mesh();
	//This is to determine whether it is the first load
	bool first = false;
	while (getline(file, line))
	{
		//Vertex texture coordinate data
		if (line.substr(0, 2) == "vt")
		{
			std::istringstream s(line.substr(3));
			glm::vec2 vt;
			s >> vt.x;
			s >> vt.y;
			//Note that the DDS texture loaded here needs to reverse y
			vt.y = -vt.y;
			temp_textCoords.push_back(vt);


		}
		//Vertex normal vector data
		else if (line.substr(0, 2) == "vn")
		{
			std::istringstream s(line.substr(3));
			glm::vec3 vn;
			s >> vn.x; s >> vn.y; s >> vn.z;
			temp_normals.push_back(vn);

		}
		//Vertex position data
		else if (line.substr(0, 1) == "v")
		{
			std::istringstream s(line.substr(2));
			glm::vec3 v;
			s >> v.x; s >> v.y; s >> v.z;
			temp_vertices.push_back(v);
		}
		//When reading the face data, you need to determine whether there is a new material. If the new material on the right means that mesh should be installed again
		else if (line.substr(0, 1) == "f") {
			
			/*if (first == false)
			{
				//For the first time, there is no material at this time.
				//Read the data into mesh
				tempmesh = new Mesh();
				first = true;
			}*/

			std::istringstream vtns(line.substr(2));
			std::string vtn;
			int i = 0;
			//Handle multiple vertex attributes in a row
			while (vtns >> vtn) {
				std::replace(vtn.begin(), vtn.end(), '/', ' ');
				std::istringstream ivtn(vtn);
				ivtn >> vertComIndex.posIndex
					>> vertComIndex.textCoordIndex
					>> vertComIndex.normIndex;

				vertComIndex.posIndex--;
				vertComIndex.textCoordIndex--;
				vertComIndex.normIndex--;
				v->position = temp_vertices[vertComIndex.posIndex];
				v->texCoords = temp_textCoords[vertComIndex.textCoordIndex];
				v->normal = temp_normals[vertComIndex.normIndex];
				//Put the data in
				tempmesh->vertData.push_back(*v);
				i++;
				//	vertComIndices.push_back(vertComIndex);
			}
		}
	}
	tempmesh->textureName = textureName;
	//After loading, load temp
	meshs.push_back(*tempmesh);
	setUpMesh();
}

Module::~Module()
{
}

void Module::setUpMesh()
{
	for (int i = 0; i < meshs.size(); i++)
	{
		meshs[i].setUpMesh();
	}
}

void Module::Draw_Module(Shader* shader)
{
	for (int i = 0; i < meshs.size(); i++)
	{
		meshs[i].Draw_Mesh(shader);
	}
}
