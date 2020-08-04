#pragma once

#include<vector>
#include "../Utilities/utilities.h"
#include"Vertex.h"
#include"stdafx.h"
#include "Shaders.h"
#include "Globals.h"

using namespace std;

class Model
{
private:
	Vertex * vertexArray;
	unsigned nrOfVertices;
	GLuint* indexArray;
	unsigned nrOfIndices;
	int id;

	bool heightmap;

	GLuint VBO;
	GLuint EBO;

public:

	Model();
	~Model();
	Model(Vertex* vertexArray,
		const unsigned& nrOfVertices,
		GLuint* indexArray,
		const unsigned& nrOfIndices);
	void loadModel(char* str);
	Vertex * getVertexArray() { return this->vertexArray; }
	unsigned getNrOfVertices() { return this->nrOfVertices; }
	GLuint * getIndexarray() { return this->indexArray; }
	unsigned getNrOfIndices() { return this->nrOfIndices; }
	int getID() { return this->id; }
	void setID(int id) { this->id = id; }
	GLuint getVBO() { return this->VBO; }
	GLuint getEBO() { return this->EBO; }
	bool isHeightMap() { return this->heightmap; }
	void setHeightMap(bool heightmap) { this->heightmap = heightmap; }
	void initVAO();
};

