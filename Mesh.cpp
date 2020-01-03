#include "Mesh.h"
#include"Texture.h"
Mesh::~Mesh()
{
}

void Mesh::Draw_Mesh(Shader* shader)
{
	//Bind VAO data
	glBindVertexArray(VAO);
	//Bind Texture
	glBindTexture(GL_TEXTURE_2D, textureId);
	//Pass in picture to fragment
	shader->setUniform1i("tex", 0);
	//Draw the model as a triangle through drawarray
	glDrawArrays(GL_TRIANGLES, 0, vertData.size());

	//Untying vertexdata
	glBindVertexArray(0);
	//Untying texture
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::setUpMesh()
{
	//Create VAO
	glGenVertexArrays(1, &VAO);

	//Bind VAO
	glBindVertexArray(VAO);

	//Create VBO
	glGenBuffers(1, &VBO);

	//Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Fill VBO with data type, size, data method: whether to change frequently, if not select static
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertData.size(), vertData.data(), GL_STATIC_DRAW);
	//Value model vertex position
	glEnableVertexAttribArray(0);
	//Take model vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	//Value model texture position
	glEnableVertexAttribArray(1);
	//Take model texture data
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(GL_FLOAT)));
	//Value model normal position
	glEnableVertexAttribArray(2);
	//Take model normal data
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(GL_FLOAT)));
	//Clear
	glBindVertexArray(0);

	textureId = Texture::load2DTexture(textureName.c_str(), GL_RGB, GL_RGB, 0);
}
