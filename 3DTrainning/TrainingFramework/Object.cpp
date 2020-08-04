#include "stdafx.h"
#include "Object.h"
#include"SceneManager.h"

Object::Object()
{
}


Object::~Object()
{
}

void Object::init(Model* model, Texture **texture, Texture **cubeTexture, Shaders *shader)
{
	this->model = model;
	this->texture = texture;
	this ->cubeTexture = cubeTexture;
	this->shader = shader;
	this->initMatrix();
	this->time = 0;
}

void Object::initMatrix()
{
	//WVP Matrix
	Matrix rotateX, rotateY, rotateZ, RotateMatrix;

	rotateX.SetRotationX(0.f);
	rotateZ.SetRotationY(0.f);
	rotateY.SetRotationZ(0.0f);
	RotateMatrix = rotateZ * rotateX * rotateY ;

	Matrix ScaleMatrix, TranslationMatrix;
	ScaleMatrix.SetScale(0.5f);
	TranslationMatrix.SetTranslation(0.0f, 0.0f, 0.f);

	Matrix  ProjectionMatrix;
	this->WorldMatrix =  ScaleMatrix * RotateMatrix * TranslationMatrix;
	this->ViewMatrix.SetIdentity();
	ProjectionMatrix.SetIdentity();
	Singleton<Camera>::CreateInstance();
	WVPMatrix = this->WorldMatrix * this->ViewMatrix * ProjectionMatrix;

}

void Object::Key(unsigned char key)
{
	switch (key)
	{
	case 'Z':
	case 'z': {
		Matrix ScaleMatrix;
		ScaleMatrix.SetScale(0.5f);
		WVPMatrix = WVPMatrix * ScaleMatrix;
		break;
	}

	case 'X':
	case 'x': {
		Matrix ScaleMatrix;
		ScaleMatrix.SetScale(1.5f);
		WVPMatrix = WVPMatrix * ScaleMatrix;
		break;
	}
			  break;
	case 'A':
	case 'a': {
		Matrix  TranslationMatrix;
		TranslationMatrix.SetTranslation(-0.1f, 0.0f, 0.0f);
		WVPMatrix = WVPMatrix * TranslationMatrix;
		break;
	}
			  break;
	case 'D':
	case 'd': {
		Matrix  TranslationMatrix;
		TranslationMatrix.SetTranslation(0.1, 0.0f, 0.0f);
		WVPMatrix = WVPMatrix * TranslationMatrix;
		break;
	}
	case 'W':
	case 'w': {
		Matrix  TranslationMatrix;
		TranslationMatrix.SetTranslation(0.0f, 0.1f, 0.0f);
		WVPMatrix = WVPMatrix * TranslationMatrix;
		break;
	}
	case 'S':
	case 's': {
		Matrix  TranslationMatrix;
		TranslationMatrix.SetTranslation(0.0f, -0.1f, 0.0f);
		WVPMatrix = WVPMatrix * TranslationMatrix;
		break;
	}
	case 'Q':
	case 'q': {
		Matrix  RotateMatrix;
		RotateMatrix.SetRotationY(-0.1f);
		WVPMatrix = WVPMatrix * RotateMatrix;
		break;
	}
	case 'E':
	case 'e': {
		Matrix  RotateMatrix;
		RotateMatrix.SetRotationY(0.1f);
		WVPMatrix = WVPMatrix * RotateMatrix;
		break;
	}
			  break;
	}
}

void Object::render()
{
	glUseProgram(shader->program);
	glBindBuffer(GL_ARRAY_BUFFER, this->model->getVBO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->model->getEBO());
	if (nrOfCubeTexture > 0) {
		for (int i = 0; i < nrOfCubeTexture; i++) {
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture[i]->GetTextureID());
		}
	}

	if (shader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(shader->positionAttribute);
		glVertexAttribPointer(shader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, pos));
	}
	if (shader->colorAttribute != -1) {
		glEnableVertexAttribArray(shader->colorAttribute);
		glVertexAttribPointer(shader->colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	}
	if (shader->texcoordAttribute != -1) {
		glEnableVertexAttribArray(shader->texcoordAttribute);
		glVertexAttribPointer(shader->texcoordAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	}
	
	if (shader->WVPmatrixUniform != -1) {
		glUniformMatrix4fv(shader->WVPmatrixUniform, 1, GL_FALSE, (GLfloat*)&WVPMatrix.m);
	}
	if (shader->WmatrixUniform != -1) {
		glUniformMatrix4fv(shader->WmatrixUniform, 1, GL_FALSE, (GLfloat*)&WorldMatrix.m);
	}
	if (shader->VmatrixUniform != -1) {
		glUniformMatrix4fv(shader->VmatrixUniform, 1, GL_FALSE, (GLfloat*)&ViewMatrix.m);
	}
	if (shader->cubeUniform != -1) {
		glEnableVertexAttribArray(shader->cubeUniform);
		glUniform1i(shader->cubeUniform, 0);
	}

	if (shader->fogColor != -1) {
		glUniform4fv(shader->fogColor, 1, (GLfloat*)&Singleton<SceneManager>::GetInstance()->getFogColor());
	}
	if (shader->fogNear != -1) {
		glUniform1f(shader->fogNear, Singleton<SceneManager>::GetInstance()->getFogNear());
	}
	if (shader->fogFar != -1) {
		glUniform1f(shader->fogFar, Singleton<SceneManager>::GetInstance()->getFogFar());
	}
	if (shader->time!= -1) {
		glUniform1f(shader->time, this->time);
	}
	if (nrOfTexture == 4) {
		if (shader->textureUniform0 != -1) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture[0]->GetTextureID());
			
			glUniform1i(shader->textureUniform0, 0);
		}
		if (shader->textureUniform1 != -1) {
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture[1]->GetTextureID());
			//printf("%d\n", texture[1]->getID());
			glUniform1i(shader->textureUniform1, 1);
		}
		if (shader->textureUniform2 != -1) {
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, texture[2]->GetTextureID());
			//printf("%d\n", texture[2]->getID());
			glUniform1i(shader->textureUniform2, 2);
		}
		if (shader->textureUniform3 != -1) {
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, texture[3]->GetTextureID());
			//printf("%d\n", texture[3]->getID());
			glUniform1i(shader->textureUniform3, 3);
		}
	}
	else if (nrOfTexture == 3) {
		if (shader->fireUniform != -1) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture[0]->GetTextureID());
			glUniform1i(shader->fireUniform, 0);
		}
		if (shader->fireDispUniform != -1) {
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture[1]->GetTextureID());
			glUniform1i(shader->fireDispUniform, 1);
		}
		if (shader->fireMaskUniform != -1) {
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, texture[2]->GetTextureID());
			glUniform1i(shader->fireMaskUniform, 2);
		
		}
	}
	else if (nrOfTexture == 1) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]->GetTextureID());
		if (shader->textureUniform != -1) {
			glUniform1i(shader->textureUniform, 0);
		}
	}
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	
	glDrawElements(GL_TRIANGLES, this->model->getNrOfIndices(), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	for (int i = 0; i < nrOfTexture; i++) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	for (int i = 0; i < nrOfCubeTexture; i++) {
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
}

void Object::setPos(Vector3 pos)
{
	Matrix  TranslationMatrix;
	TranslationMatrix.SetTranslation(pos);
	//this->initMatrix();
	this->WorldMatrix = this->WorldMatrix * TranslationMatrix;
}

void Object::setScale(Vector3 scale)
{
	Matrix  ScaleMatrix;
	ScaleMatrix.SetScale(scale);
	//this->initMatrix();
	this->WorldMatrix = this->WorldMatrix * ScaleMatrix;
}

void Object::setRotate(Vector3 rotate)
{
	Matrix rotateX, rotateY, rotateZ, RotateMatrix;

	rotateX.SetRotationX(rotate.x * 3.14 / 180);
	rotateZ.SetRotationY(rotate.y * 3.14 / 180);
	rotateY.SetRotationZ(rotate.z * 3.14 / 180);
	RotateMatrix = rotateZ * rotateX * rotateY;

	this->WorldMatrix = this->WorldMatrix * RotateMatrix;
}

void Object::initWorldMatrix(Vector3 pos, Vector3 scale, Vector3 rotate)
{
	Matrix  TranslationMatrix;
	TranslationMatrix.SetTranslation(pos);
	Matrix  ScaleMatrix;
	ScaleMatrix.SetScale(scale);
	Matrix rotateX, rotateY, rotateZ, RotateMatrix;

	rotateX.SetRotationX(rotate.x * 3.14 / 180);
	rotateZ.SetRotationY(rotate.y * 3.14 / 180);
	rotateY.SetRotationZ(rotate.z * 3.14 / 180);
	RotateMatrix = rotateZ * rotateX * rotateY;

	this->WorldMatrix =  ScaleMatrix * RotateMatrix * TranslationMatrix;
}

void Object::update(Matrix ViewMatrix, Matrix ProjectionMatrix, float deltatime)
{
	this->time += deltatime;
	this->ViewMatrix = ViewMatrix;
	WVPMatrix = this->WorldMatrix * ViewMatrix * ProjectionMatrix;
}

void Object::initShader(char * fileVertexShader, char * fileFragmentShader)
{
	this->shader->Init(fileVertexShader, fileFragmentShader);
}


