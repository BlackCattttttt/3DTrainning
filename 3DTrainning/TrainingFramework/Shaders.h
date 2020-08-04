#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
private:
	int id;
public:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute;
	GLint colorAttribute;
	GLint texcoordAttribute;
	GLint textureUniform;
	GLint WVPmatrixUniform;
	GLint WmatrixUniform;
	GLint VmatrixUniform;
	GLint cubeUniform;

	GLint fogColor;
	GLint fogNear;
	GLint fogFar;

	GLint textureUniform0;
	GLint textureUniform1;
	GLint textureUniform2;
	GLint textureUniform3;

	GLint fireUniform;
	GLint fireMaskUniform;
	GLint fireDispUniform;
	GLint time;

	int getID() { return this->id; }
	void setID(int id) { this->id = id; }

	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};