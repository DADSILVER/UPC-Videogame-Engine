#include "ModuleProgram.h"
#include <GL/glew.h>

ModuleProgram::ModuleProgram()
{
}

ModuleProgram::~ModuleProgram()
{
}

char* ModuleProgram::LoadShaderSource(const char* _shader_file_name)
{
	char* data = nullptr;
	FILE* file = nullptr;
	fopen_s(&file, _shader_file_name, "rb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		data = (char*)malloc(size + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, size, file);
		data[size] = 0;
		fclose(file);
	}
	return data;
}

int ModuleProgram::CompileShader(GLenum type, const char* _source)
{
	unsigned shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &_source, 0);
	glCompileShader(shader_id);
	int res = GL_FALSE;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetShaderInfoLog(shader_id, len, &written, info);
			engLOG("Log Info: %s", info);
			free(info);
		}
	}
	return shader_id;
}



int ModuleProgram::CreateProgram()
{
	m_fragment = CompileShader(GL_FRAGMENT_SHADER, LoadShaderSource("fragmentShader.glsl"));
	m_vertex = CompileShader(GL_VERTEX_SHADER, LoadShaderSource("vertexShader.glsl"));

	unsigned program_id = glCreateProgram();
	engLOG("program: %d", program_id);
	glAttachShader(program_id, m_vertex);
	glAttachShader(program_id, m_fragment);
	glLinkProgram(program_id);
	int res;
	glGetProgramiv(program_id, GL_LINK_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetProgramInfoLog(program_id, len, &written, info);
			engLOG("Program Log Info: %s", info);
			free(info);
		}
	}
	glDeleteShader(m_vertex);
	glDeleteShader(m_fragment);
	return program_id;
}


