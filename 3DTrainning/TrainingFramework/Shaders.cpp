#include "stdafx.h"
#include "Shaders.h"

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if ( vertexShader == 0 )
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	colorAttribute = glGetAttribLocation(program, "a_color");
	texcoordAttribute = glGetAttribLocation(program, "a_uv");
	textureUniform = glGetUniformLocation(program, "u_texture");
	WVPmatrixUniform = glGetUniformLocation(program, "u_WVP");
	WmatrixUniform = glGetUniformLocation(program, "u_W");
	VmatrixUniform = glGetUniformLocation(program, "u_V");
	cubeUniform = glGetUniformLocation(program, "u_samplerCubeMap");

	fogColor = glGetUniformLocation(program, "u_fogColor");
	fogNear = glGetUniformLocation(program, "u_fogNear");
	fogFar = glGetUniformLocation(program, "u_fogFar");

	textureUniform0 = glGetUniformLocation(program, "u_texture0");
	textureUniform1 = glGetUniformLocation(program, "u_texture1");
	textureUniform2 = glGetUniformLocation(program, "u_texture2");
	textureUniform3 = glGetUniformLocation(program, "u_texture3");

	fireUniform = glGetUniformLocation(program, "u_firetexture");
	fireMaskUniform = glGetUniformLocation(program, "u_firemasktexture");
	fireDispUniform = glGetUniformLocation(program, "u_displacementtexture");
	time = glGetUniformLocation(program, "u_time");

	return 0;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}