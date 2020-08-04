#include "stdafx.h"
#include "Model.h"

Model::Model()
{
}


Model::~Model()
{
}

Model::Model(Vertex * vertexArray, const unsigned & nrOfVertices, GLuint * indexArray, const unsigned & nrOfIndices)
{
	this->nrOfVertices = nrOfVertices;
	this->nrOfIndices = nrOfIndices;

	this->vertexArray = new Vertex[this->nrOfVertices];
	for (size_t i = 0; i < nrOfVertices; i++)
	{
		this->vertexArray[i] = vertexArray[i];
	}

	this->indexArray = new GLuint[this->nrOfIndices];
	for (size_t i = 0; i < nrOfIndices; i++)
	{
		this->indexArray[i] = indexArray[i];
	}
	this->initVAO();
}

void Model::loadModel(char * str)
{
	FILE *fptr;
	if ((fptr = fopen(str, "r")) == NULL)
	{
		printf("Error! opening file\n");
		//printf("%s\n", str);
		// Program exits if file pointer returns NULL.
		exit(1);
	}
	int numberOfVertices;
	fscanf(fptr, "NrVertices: %d\n", &numberOfVertices);
	if (numberOfVertices <= 0)
		return ;
	//printf("%d\n", numberOfVertices);
	this->nrOfVertices = numberOfVertices;
	this->vertexArray = new Vertex[nrOfVertices];
	for (int i = 0; i < numberOfVertices; ++i)
	{
		fscanf(fptr, "   %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%*f, %*f, %*f]; tgt:[%*f, %*f, %*f]; uv:[%f, %f];\n",
			&vertexArray[i].pos.x, &vertexArray[i].pos.y, &vertexArray[i].pos.z,
			&vertexArray[i].normal.x, &vertexArray[i].normal.y, &vertexArray[i].normal.z,
			&vertexArray[i].texcoord.x, &vertexArray[i].texcoord.y);
	}
	int numberOfIndices;
	fscanf(fptr, "NrIndices: %d\n", &numberOfIndices);
	this->nrOfIndices = numberOfIndices;
	this->indexArray = new GLuint[numberOfIndices];
	for (int i = 0; i < numberOfIndices; i += 3)
	{
		fscanf(fptr, "   %*d.    %d,    %d,    %d\n", &indexArray[i], &indexArray[i + 1], &indexArray[i + 2]);
	}
	
	if (heightmap == true) {
		int iWidth, iHeight, bpp;
		char *imageData = LoadTGA("../Resources/Texture/heightmap.tga", &iWidth, &iHeight, &bpp);
		if (imageData != NULL) {
			Vector3 color;
			int imgX, imgY;
			for (int j = 0; j < this->getNrOfVertices(); j++) {
				imgX = vertexArray[j].texcoord.x * iWidth;
				imgY = vertexArray[j].texcoord.y * iHeight;

				color.x = (unsigned char)imageData[(imgY * iWidth + imgX)*(bpp / 8) + 0] / (float)255;
				color.y = (unsigned char)imageData[(imgY * iWidth + imgX)*(bpp / 8) + 1] / (float)255;
				color.z = (unsigned char)imageData[(imgY * iWidth + imgX)*(bpp / 8) + 2] / (float)255;
				float h = 1 - ((0.3 * color.x) + (0.59 * color.y) + (0.11 * color.z));

				vertexArray[j].pos.y +=10 *  h;
			}
		}
		delete[] imageData;
	}
	
}

void Model::initVAO()
{
	//buffer object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, this->getNrOfVertices() * sizeof(Vertex), this->getVertexArray(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//buffer object
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->getNrOfIndices() * sizeof(GLuint), this->getIndexarray(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}


