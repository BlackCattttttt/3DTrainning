#pragma once

#include"Model.h"
#include"Texture.h"
#include"Shaders.h"
#include"Singleton.h"
#include"Camera.h"

class Object
{
private:
	Model *model;
	Texture **texture;
	Texture **cubeTexture;
	Shaders *shader;
	Matrix WVPMatrix;
	Matrix WorldMatrix;
	Matrix ViewMatrix;

	int id;
	int nrOfTexture;
	int nrOfCubeTexture;
	float time;

public:
	Object();
	~Object();
	void init(Model *model, Texture** texture, Texture** cubeTexture, Shaders *shader);
	void initMatrix();
	void Key(unsigned char key);
	void render();
	void setPos(Vector3 pos);
	void setScale(Vector3 scale);
	void setRotate(Vector3 rotate);
	void initWorldMatrix(Vector3 pos, Vector3 scale, Vector3 rotate);
	void update(Matrix ViewMatrix,Matrix ProjectionMatrix, float deltatime);
	void initShader(char * fileVertexShader, char * fileFragmentShader);
	int getID() { return this->id; }
	void setID(int id) { this->id = id; }
	int getNrOfTexture() { return this->nrOfTexture; }
	void setNrOfTexture(int num) { this->nrOfTexture = num; }
	int getNrOfCubeTexture() { return this->nrOfCubeTexture; }
	void setNrOfCubeTexture(int num) { this->nrOfCubeTexture = num; }
};

