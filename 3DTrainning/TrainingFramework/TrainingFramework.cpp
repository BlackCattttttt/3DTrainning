// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include "Model.h"
#include "Texture.h"
#include "Object.h"
#include "Camera.h"
#include "Singleton.h"
#include "ResourceManager.h"
#include "SceneManager.h"

//Model *model = new Model("../Resources/Models/Woman1.nfg");

int Init ( ESContext *esContext )
{
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//object
	
	Singleton<ResourceManager>::CreateInstance();
	Singleton<ResourceManager>::GetInstance()->loadFile("../Resources/ResourcesManager.txt");

	Singleton<SceneManager>::CreateInstance();
	Singleton<SceneManager>::GetInstance()->loadFile("../Resources/SceneManager.txt");

	//Singleton<Camera>::CreateInstance();
	return 0 ;

}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Singleton<SceneManager>::GetInstance()->render();

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update(ESContext *esContext, float deltaTime)
{
	//Singleton<Camera>::GetInstance()->rotateRight(deltaTime);
	Singleton<Camera>::GetInstance()->update(deltaTime);
	Singleton<SceneManager>::GetInstance()->update(Singleton<Camera>::GetInstance()->getViewMatrix(), Singleton<Camera>::GetInstance()->getPerspectiveMatrix(),deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	Singleton<Camera>::GetInstance()->key(key, bIsPressed);
}

void CleanUp()
{
	Singleton<Camera>::DestroyInstance();
	Singleton<ResourceManager>::DestroyInstance();
	Singleton<SceneManager>::DestroyInstance();
	
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0) 
		return 0;	

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

