#include "ModuleProgram.h"
#include <GL/glew.h>

#include "Application.h"

#include "ModuleEditor.h"

ModuleProgram::ModuleProgram()
{
}

ModuleProgram::~ModuleProgram()
{
}

char* ModuleProgram::LoadShaderSource(const char* InShader_file_name)
{
	char* data = nullptr;
	FILE* file = nullptr;
	fopen_s(&file, InShader_file_name, "rb");
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

int ModuleProgram::CompileShader(GLenum InType, const char* InSource)
{
	unsigned shader_id = glCreateShader(InType);
	glShaderSource(shader_id, 1, &InSource, 0);
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
			App->m_Editor->m_console.AddLog(engLOG("Log Info: %s", info));
			free(info);
		}
	}
	return shader_id;
}

int ModuleProgram::CreateProgram()
{
	m_Fragment = CompileShader(GL_FRAGMENT_SHADER, LoadShaderSource("fragmentShader.glsl"));
	m_Vertex = CompileShader(GL_VERTEX_SHADER, LoadShaderSource("vertexShader.glsl"));

	unsigned program_id = glCreateProgram();
	App->m_Editor->m_console.AddLog(engLOG("program: %d", program_id));
	glAttachShader(program_id, m_Vertex);
	glAttachShader(program_id, m_Fragment);
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
			App->m_Editor->m_console.AddLog(engLOG("Program Log Info: %s", info));
			free(info);
		}
	}
	glDeleteShader(m_Vertex);
	glDeleteShader(m_Fragment);
	return program_id;
}


