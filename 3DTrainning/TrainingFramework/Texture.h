#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"

#define REPEAT 0
#define CLAMP_TO_EDGE 1
class Texture
{
private:
	GLuint textureID;
	int id;
	int tiling;
public:
	Texture();
	~Texture();
	GLuint GetTextureID() { return this->textureID; };
	void loadFile(char *str);
	void loadCubeFile(char *str[]);
	int getID() { return this->id; }
	void setID(int id) { this->id = id; }
	void setTiling(int tiling) { this->tiling = tiling; }
};

