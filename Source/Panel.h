#pragma once
class Panel
{
public:
	Panel(const char* title);
	virtual bool Draw() = 0;

	bool m_Open = true;
protected:
	const char* m_Title;
};

