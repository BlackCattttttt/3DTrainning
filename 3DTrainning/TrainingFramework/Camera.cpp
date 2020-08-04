#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	nearPlane = 0.1f;
	farPlane = 500.0f;
	verticalFOV = 1.0f;
	speech = 1.2f;
	rotateSpeech = 0.5f;

	pos = Vector3(0.0f, 0.0f, -3.0f);
	target = Vector3(0.0f, 0.0f, 0.0f);
	up = Vector3(0.0f, 1.0f, 0.0f);

	this->viewMatrix.SetIdentity();
	this->caculateViewMatrix();
}


Camera::~Camera()
{
}

Matrix Camera::getPerspectiveMatrix()
{
	Matrix PerspectiveMatrix;
	this->aspect = Globals::screenWidth / Globals::screenHeight;
	PerspectiveMatrix.SetPerspective(this->verticalFOV, this->aspect, this->nearPlane, this->farPlane);
	return PerspectiveMatrix;
}

void Camera::caculateViewMatrix()
{
	Vector3 xaxis, yaxis, zaxis;
	//printf("%f  %f   %f", this->pos.x, this->pos.y, this->pos.z);
	zaxis = (this->pos - this->target).Normalize();
	xaxis = (up.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();

	this->viewMatrix.m[0][0] = xaxis.x;
	this->viewMatrix.m[0][1] = yaxis.x;
	this->viewMatrix.m[0][2] = zaxis.x;
	this->viewMatrix.m[0][3] = 0;

	this->viewMatrix.m[1][0] = xaxis.y;
	this->viewMatrix.m[1][1] = yaxis.y;
	this->viewMatrix.m[1][2] = zaxis.y;
	this->viewMatrix.m[1][3] = 0;

	this->viewMatrix.m[2][0] = xaxis.z;
	this->viewMatrix.m[2][1] = yaxis.z;
	this->viewMatrix.m[2][2] = zaxis.z;
	this->viewMatrix.m[2][3] = 0;

	this->viewMatrix.m[3][0] = -this->pos.Dot(xaxis);
	this->viewMatrix.m[3][1] = -this->pos.Dot(yaxis);
	this->viewMatrix.m[3][2] = -this->pos.Dot(zaxis);
	this->viewMatrix.m[3][3] = 1;
}

void Camera::caculateWorldMatrix()
{
	Vector3 xaxis, yaxis, zaxis;

	zaxis = (this->pos - this->target).Normalize();
	xaxis = (up.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();

	this->worldMatrix.m[0][0] = xaxis.x;
	this->worldMatrix.m[0][1] = xaxis.y;
	this->worldMatrix.m[0][2] = xaxis.z;
	this->worldMatrix.m[0][3] = 0;

	this->worldMatrix.m[1][0] = yaxis.x;
	this->worldMatrix.m[1][1] = yaxis.y;
	this->worldMatrix.m[1][2] = yaxis.z;
	this->worldMatrix.m[1][3] = 0;

	this->worldMatrix.m[2][0] = zaxis.x;
	this->worldMatrix.m[2][1] = zaxis.y;
	this->worldMatrix.m[2][2] = zaxis.z;
	this->worldMatrix.m[2][3] = 0;

	this->worldMatrix.m[3][0] = this->pos.x * xaxis.x + this->pos.y * yaxis.x + this->pos.z * zaxis.x;
	this->worldMatrix.m[3][1] = this->pos.x * xaxis.y + this->pos.y * yaxis.y + this->pos.z * zaxis.y;
	this->worldMatrix.m[3][2] = this->pos.x * xaxis.z + this->pos.y * yaxis.z + this->pos.z * zaxis.z;
	this->worldMatrix.m[3][3] = 1;
}

void Camera::forward(float deltatime)
{
	Vector3 deltaMove = -(this->pos - this->target).Normalize()*deltatime*speech;
	this->pos = this->pos + deltaMove;
	this->target = this->target + deltaMove;
}
void Camera::backward(float deltatime)
{
	Vector3 deltaMove = -(this->pos - this->target).Normalize()*deltatime*speech;
	this->pos = this->pos - deltaMove;
	this->target = this->target - deltaMove;
}

void Camera::left(float deltaTime)
{
	Vector3 xaxis, zaxis;
	zaxis = (this->pos - this->target).Normalize();
	xaxis = (up.Cross(zaxis)).Normalize();
	Vector3 deltaMove = xaxis * deltaTime * speech;
	this->pos = this->pos - deltaMove;
	this->target = this->target - deltaMove;
}

void Camera::right(float deltaTime)
{
	Vector3 xaxis, zaxis;
	zaxis = (this->pos - this->target).Normalize();
	xaxis = (up.Cross(zaxis)).Normalize();
	Vector3 deltaMove = xaxis * deltaTime * speech;
	this->pos = this->pos + deltaMove;
	this->target = this->target + deltaMove;
}

void Camera::Up(float deltaTime)
{
	Vector3 xaxis, yaxis, zaxis;
	zaxis = (this->pos - this->target).Normalize();
	xaxis = (up.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();
	Vector3 deltaMove = yaxis * deltaTime * speech;
	this->pos = this->pos + deltaMove;
	this->target = this->target + deltaMove;
}

void Camera::Down(float deltaTime)
{
	Vector3 xaxis, yaxis, zaxis;
	zaxis = (this->pos - this->target).Normalize();
	xaxis = (up.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();
	Vector3 deltaMove = yaxis * deltaTime * speech;
	this->pos = this->pos - deltaMove;
	this->target = this->target - deltaMove;
}

Matrix Camera::setRotationAroundY(float angle)
{
	Matrix rotation;
	Vector4 rotateAxis = Vector4(0, 1, 0, 0);
	rotateAxis = rotateAxis * this->getViewMatrix();
	return rotation.SetRotationAngleAxis(angle, rotateAxis.x, rotateAxis.y, rotateAxis.z);
}

void Camera::rotateLeft(float deltaTime)
{
	float rotateAngle = deltaTime * rotateSpeech;
	Vector4 localTarget = Vector4(0.f, 0.f, -(this->pos - this->target).Length(), 1.f);
	Vector4 localNewTarget = localTarget * this->setRotationAroundY(rotateAngle);
	Vector4 worldNewTarget = localNewTarget * this->getWorldMatrix();
	this->target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
	//printf("%f %f %f \n", worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}

void Camera::rotateRight(float deltaTime)
{
	float rotateAngle = deltaTime * rotateSpeech;
	Vector4 localTarget = Vector4(0.f, 0.f, -(this->pos - this->target).Length(), 1.f);
	Vector4 localNewTarget = localTarget * this->setRotationAroundY(-rotateAngle);
	Vector4 worldNewTarget = localNewTarget * this->getWorldMatrix();
	this->target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
	//this->caculateViewMatrix();
}


void Camera::rotateUp(float deltaTime)
{
	Matrix rotation;
	float rotateAngle = deltaTime * rotateSpeech;
	Vector4 localTarget = Vector4(0.f, 0.f, -(this->pos - this->target).Length(), 1.f);
	Vector4 localNewTarget = localTarget * rotation.SetRotationX(rotateAngle);
	Vector4 worldNewTarget = localNewTarget * this->getWorldMatrix();
	this->target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}

void Camera::rotateDown(float deltaTime)
{
	Matrix rotation;
	float rotateAngle = deltaTime * rotateSpeech;
	Vector4 localTarget = Vector4(0.f, 0.f, -(this->pos - this->target).Length(), 1.f);
	Vector4 localNewTarget = localTarget * rotation.SetRotationX(-rotateAngle);
	Vector4 worldNewTarget = localNewTarget * this->getWorldMatrix();
	this->target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}

void Camera::key(unsigned char key, bool bIsPressed)
{
	if (bIsPressed) {
		switch (key)
		{
		case 'C':
		case 'c': {
			dir = ROTATEDOWN;
			break;
		}

		case 'V':
		case 'v': {
			dir = ROTATEUP;
			break;
		}
				  break;
		case 'A':
		case 'a': {
			dir = LEFT;
			break;
		}
				  break;
		case 'D':
		case 'd': {
			dir = RIGHT;
			break;
		}
		case 'W':
		case 'w': {
			dir = FORWARD;
			break;
		}
		case 'S':
		case 's': {
			dir = BACKWARD;
			break;
		}
		case 'Q':
		case 'q': {
			dir = ROTATELEFT;
			break;
		}
		case 'E':
		case 'e': {
			dir = ROTATERIGHT;
			break;
		}
		case 'X':
		case 'x': {
			dir = UP;
			break;
		}
		case 'Z':
		case 'z': {
			dir = DOWN;
			break;
		}
				  break;
		}
	}
	else {
		dir = 0;
	}
	
}

void Camera::update(float deltaTime)
{
	switch (dir)
	{
	case LEFT: {
		left(deltaTime);
		break;
	}

	case RIGHT: {
		right(deltaTime);
		break;
	}
			  break;
	case FORWARD: {
		forward(deltaTime);
		break;
	}
			  break;
	case BACKWARD: {
		backward(deltaTime);
		break;
	}
	case ROTATELEFT: {
		rotateLeft(deltaTime);
		break;
	}
	case ROTATERIGHT: {
		rotateRight(deltaTime);
		break;
	}
	case ROTATEUP: {
		rotateUp(deltaTime);
		break;
	}
	case ROTATEDOWN: {
		rotateDown(deltaTime);
		break;
	}
	case DOWN: {
		Down(deltaTime);
		break;
	}
	case UP: {
		Up(deltaTime);
		break;
	}
			  break;
	}
}
