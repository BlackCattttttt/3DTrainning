#include "stdafx.h"
#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

Model* ResourceManager::getModel(int id)
{
	for (int i = 0; i < this->nrOfModel; i++) {
		if (this->model[i]->getID() == id) {
			return model[i];
		}
	}
}

Texture* ResourceManager::getTexture(int id)
{
	for (int i = 0; i < this->nrOfTexture; i++) {
		if (this->texture[i]->getID() == id) {
			return texture[i];
		}
	}
}

Shaders* ResourceManager::getShader(int id)
{
	for (int i = 0; i < this->nrOfShader; i++) {
		if (this->shader[i]->getID() == id) {
			return shader[i];
		}
	}
}

Texture * ResourceManager::getCubeTexture(int id)
{
	for (int i = 0; i < this->nrOfCubeTexture; i++) {
		if (this->cubeTexture[i]->getID() == id) {
			return cubeTexture[i];
		}
	}
	return nullptr;
}

void ResourceManager::loadFile(char * str)
{
	FILE *fptr;
	if ((fptr = fopen(str, "r")) == NULL)
	{
		printf("Error! opening file");
		// Program exits if file pointer returns NULL.
		exit(1);
	}
	int numberOfModel;
	fscanf(fptr, "#Models: %d\n", &numberOfModel);
	if (numberOfModel <= 0)
		return;
	this->nrOfModel = numberOfModel;
	this->model = new Model*[nrOfModel];

	for (int i = 0; i < numberOfModel; i++)
	{
		int id;
		fscanf(fptr, "ID %d\n", &id);

		char srcModel[1000];
		fscanf(fptr, "FILE %s\n", &srcModel);
		int heightmap;
		fscanf(fptr, "HEIGHTMAP %d\n", &heightmap);
		this->model[i] = new Model();
		this->model[i]->setID(id);
		if (heightmap == 0) {
			this->model[i]->setHeightMap(false);
		}
		else {
			this->model[i]->setHeightMap(true);
		}
		this->model[i]->loadModel(srcModel);

		this->model[i]->initVAO();

	}

	int numberOfTexture;
	fscanf(fptr, "#2D Textures: %d\n", &numberOfTexture);
	this->nrOfTexture = numberOfTexture;
	this->texture = new Texture*[numberOfTexture];
	for (int i = 0; i < numberOfTexture; ++i)
	{
		int id;
		fscanf(fptr, "ID %d\n", &id);
		this->texture[i] = new Texture();
		this->texture[i]->setID(id);
		char srcTexture[1000];
		fscanf(fptr, "FILE %s\n", &srcTexture);
		this->texture[i]->loadFile(srcTexture);
		char tiling[100];
		fscanf(fptr, "TILING %s\n", &tiling);
		if (strcmp(tiling, "REPEAT")) {
			this->texture[i]->setTiling(1);
		}
		else {
			this->texture[i]->setTiling(0);
		}
	}

	int numberOfCubeTexture;
	fscanf(fptr, "#Cube Textures: %d\n", &numberOfCubeTexture);
	this->nrOfCubeTexture = numberOfCubeTexture;
	this->cubeTexture = new Texture*[numberOfCubeTexture];
	for (int i = 0; i < numberOfCubeTexture; ++i)
	{
		int id;
		fscanf(fptr, "ID %d\n", &id);
		this->cubeTexture[i] = new Texture();
		this->cubeTexture[i]->setID(id);
		char srcTexture[10][256];
		for (int j = 0; j < 6; j++) {
			fscanf(fptr, "FILE %s\n", &srcTexture[j]);
//			printf("%s\n", srcTexture[j]);
		}	
		char *src[10];
		for (int j = 0; j < 6; j++) {
			src[j] = new char[256];
			strcpy(src[j], srcTexture[j]);
		//	printf("%s\n", src[j]);
		}
		this->cubeTexture[i]->loadCubeFile(src);
	}

	int numberOfShader;
	fscanf(fptr, "#Shaders: %d\n", &numberOfShader);
	this->nrOfShader = numberOfShader;
	this->shader = new Shaders*[numberOfShader];
	for (int i = 0; i < numberOfShader; ++i)
	{
		this->shader[i] = new Shaders();
		int id;
		fscanf(fptr, "ID %d\n", &id);
		this->shader[i]->setID(id);
		char VS[1000],FS[1000];
		fscanf(fptr, "VS %s\n", &VS);
		fscanf(fptr, "FS %s\n", &FS);
		this->shader[i]->Init(VS, FS);
		//fscanf(fptr, "%*[^\n]");
		//fscanf(fptr, "%*[^\n]");
		//fscanf(fptr, "%*[^\n]");

	}
}

