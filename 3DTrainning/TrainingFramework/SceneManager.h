#pragma once
#include"Object.h"
#include"ResourceManager.h"
#include"Singleton.h"

class SceneManager
{
private:
	Object *objects;
	unsigned nrOfObject;
	Vector4 fogColor;
	float fogNear;
	float fogFar;
public:
	SceneManager();
	~SceneManager();
	unsigned getNrOfObjects() { return this->nrOfObject; }
	void loadFile(char *str);
	void render();
	void update(Matrix ViewMatrix, Matrix ProjectionMatrix, float deltatime);
	Vector4 getFogColor() { return this->fogColor; }
	float getFogNear() { return this->fogNear; }
	float getFogFar() { return this->fogFar; }
};

