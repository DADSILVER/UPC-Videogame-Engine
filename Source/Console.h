#pragma once
class Console
{

public:
	//static int TextEditCallbackStub(ImGuiInputTextCallbackData* data);
	void Draw();

private:
	char	m_InputBuf[256];
};

