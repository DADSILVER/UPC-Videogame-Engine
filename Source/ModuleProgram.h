#pragma once
#include "Module.h"
#include <GL/glew.h>

class ModuleProgram :
    public Module
{
public:
	ModuleProgram();
	~ModuleProgram();

	int CreateProgram();

private:
	char* LoadShaderSource(const char* shader_file_name);
	int CompileShader(GLenum _type, const char* _source);

public:
	int m_fragment;
	int m_vertex;
};

