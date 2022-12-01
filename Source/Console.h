#pragma once

#include "imgui.h"
#include <corecrt_malloc.h>

class Console
{

public:
	Console();
	void ClearLog();
	void AddLog(const char* fmt, ...) IM_FMTARGS(2);
	//static int TextEditCallbackStub(ImGuiInputTextCallbackData* data);
	void Draw();
	static char* Strdup(const char* s) { IM_ASSERT(s); size_t len = strlen(s) + 1; void* buf = malloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)s, len); }


private:
	char					m_InputBuf[256];
	ImVector<char*>			Items;
	ImGuiTextFilter			Filter;
	bool					AutoScroll;
	bool					ScrollToBottom;
};

