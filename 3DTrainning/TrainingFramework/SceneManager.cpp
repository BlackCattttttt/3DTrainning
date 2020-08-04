#include "stdafx.h"
#include "SceneManager.h"


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::loadFile(char * str)
{
	FILE *fptr;
	if ((fptr = fopen(str, "r")) == NULL)
	{
		printf("Error! opening file");
		// Program exits if file pointer returns NULL.
		exit(1);
	}
	int numberOfObject;
	fscanf(fptr, "#Objects: %d\n", &numberOfObject);
	if (numberOfObject <= 0)
		return;
	this->nrOfObject = numberOfObject;
	this->objects = new Object[nrOfObject];

	for (int i = 0; i < numberOfObject; ++i)
	{
		int id;
		fscanf(fptr, "ID %d\n", &id);
		this->objects[i].setID(id);
		int idModel;
		fscanf(fptr, "MODEL %d\n", &idModel);
		//printf("%d\n", idModel);
		int numberOfTextures;
		fscanf(fptr, "TEXTURES %d\n", &numberOfTextures);
		//printf("%d\n", numberOfTextures);
		Texture **texture;
		texture = new Texture*[numberOfTextures];
		this->objects[i].setNrOfTexture(numberOfTextures);
		if (numberOfTextures > 0) {
			for (int j = 0; j < numberOfTextures; j++) {
				int idTexture;
				fscanf(fptr, "TEXTURE %d\n", &idTexture);
//				printf("%d\n", idTexture);
				texture[j] = Singleton<ResourceManager>::GetInstance()->getTexture(idTexture);
			}
		}

		int numberOfCubeTextures;
		fscanf(fptr, "CUBETEXTURES %d\n", &numberOfCubeTextures);
		//printf("%d\n", numberOfCubeTextures);
		
		this->objects[i].setNrOfCubeTexture(numberOfCubeTextures);
		Texture **cubeTexture;
		cubeTexture = new Texture*[numberOfCubeTextures];
		if (numberOfCubeTextures > 0) {
			
			for (int j = 0; j < numberOfCubeTextures; j++) {
				int idTexture;
				fscanf(fptr, "CUBETEX %d\n", &idTexture);
				//printf("%d\n", idTexture);
				cubeTexture[j] = Singleton<ResourceManager>::GetInstance()->getCubeTexture(idTexture);
			}
		}
		
		int idShader;
		fscanf(fptr, "SHADER %d\n", &idShader);
		//printf("%d\n", idShader);
		this->objects[i].init(Singleton<ResourceManager>::GetInstance()->getModel(idModel),
			texture,
			cubeTexture,
			Singleton<ResourceManager>::GetInstance()->getShader(idShader));
		Vector3 pos, scale, rotate;
		fscanf(fptr, "POSITION %f,%f,%f\n", &pos.x, &pos.y, &pos.z);
		fscanf(fptr, "ROTATION %f,%f,%f\n", &rotate.x, &rotate.y, &rotate.z);
		fscanf(fptr, "SCALE %f,%f,%f\n", &scale.x, &scale.y, &scale.z);

		//printf("POSITION %f,%f,%f\n", pos.x, pos.y, pos.z);
		//printf("ROTATION %f,%f,%f\n", rotate.x, rotate.y, rotate.z);
		//printf("SCALE %f,%f,%f\n", scale.x,scale.y, scale.z);

		//this->objects[i].setPos(pos);
		//this->objects[i].setScale(scale);
		//this->objects[i].setRotate(rotate);
		this->objects[i].initWorldMatrix(pos, scale, rotate);
	}

 	fscanf(fptr, "#LINEARFOG:\n");
	fscanf(fptr, "FOGCOLOR: %f,%f,%f,%f\n", &this->fogColor.x, &this->fogColor.y, &this->fogColor.z, &this->fogColor.w);
	//printf("FOGCOLOR: %f,%f,%f,%f\n", fogColor.x, fogColor.y, fogColor.z, fogColor.w);
	fscanf(fptr, "FOGNEAR: %f\n", &this->fogNear);
	fscanf(fptr, "FOGFAR: %f\n", &this->fogFar);
	//printf("FOGNEAR: %f\n", fogNear);
	//printf("FOGFAR: %f\n", fogFar);
}

void SceneManager::render()
{
	for (int i = 0; i < nrOfObject; i++) {
		this->objects[i].render();
	}
}

void SceneManager::update(Matrix ViewMatrix, Matrix ProjectionMatrix, float deltatime)
{
	for (int i = 0; i < nrOfObject; i++) {
		this->objects[i].update(ViewMatrix,ProjectionMatrix,deltatime);
	}
}
