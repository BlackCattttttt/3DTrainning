#pragma once

#include"stdafx.h"
#include "Shaders.h"
#include "Globals.h"

#define BACKWARD 1
#define FORWARD 2
#define LEFT 3
#define RIGHT 4
#define ROTATELEFT 5
#define ROTATERIGHT 6
#define ROTATEUP 7
#define ROTATEDOWN 8
#define UP 9
#define DOWN 10
class Camera
{
	
private:
	GLfloat nearPlane;
	GLfloat farPlane;
	GLfloat verticalFOV;
	GLfloat speech;
	GLfloat rotateSpeech;
	GLfloat aspect;

	Vector3 pos;
	Vector3 target;
	Vector3 up;

	Matrix worldMatrix;
	Matrix viewMatrix;

	int dir;

public:
	Camera();
	~Camera();
	void increseTager() { pos.z--; }
	Matrix getViewMatrix() { this->caculateViewMatrix(); return this->viewMatrix; }
	Matrix getWorldMatrix() { this->caculateWorldMatrix(); return this->worldMatrix; }
	Matrix getPerspectiveMatrix();
	void caculateViewMatrix();
	void caculateWorldMatrix();
	void forward(float deltatime);
	void backward(float deltatime);
	void left(float deltaTime);
	void right(float deltaTime);
	void Up(float deltaTime);
	void Down(float deltaTime);
	Matrix setRotationAroundY(float angle);
	void rotateLeft(float deltaTime);
	void rotateRight(float deltaTime);
	Matrix setRotationAroundX(float angle);
	void rotateUp(float deltaTime);
	void rotateDown(float deltaTime);
	void key(unsigned char key, bool bIsPressed);
	void update(float deltaTime);
};

