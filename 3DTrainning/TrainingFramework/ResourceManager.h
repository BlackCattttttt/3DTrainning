#pragma once
#include"Model.h"
#include"Texture.h"
#include"Shaders.h"

class ResourceManager
{
private:
	Model **model;
	unsigned nrOfModel;
	Texture **texture;
	unsigned nrOfTexture;
	Texture **cubeTexture;
	unsigned nrOfCubeTexture;
	Shaders **shader;
	unsigned nrOfShader;
public:
	ResourceManager();
	~ResourceManager();
	unsigned getNrOfModels() { return this->nrOfModel; }
	unsigned getNrOfTextures() { return this->nrOfTexture; }
	unsigned getNrOfCubeTextures() { return this->nrOfCubeTexture; }
	unsigned getNrOfShaders() { return this->nrOfShader; }
	Model* getModel(int id);
	Texture* getTexture(int id);
	Shaders* getShader(int id);
	Texture* getCubeTexture(int id);
	void loadFile(char* str);

};

