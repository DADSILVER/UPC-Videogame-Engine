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
	char* LoadShaderSource(const char* InShader_file_name);
	int CompileShader(GLenum InType, const char* InSource);

public:
	int m_fragment;
	int m_vertex;
};

