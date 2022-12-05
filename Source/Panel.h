#pragma once
class Panel
{
public:
	Panel(const char* title);
	virtual bool Draw() = 0;
	inline void SetOpen(const bool& InOpen) { m_Open = InOpen; }
	inline bool& GetOpen() { return m_Open; }

	bool m_Open = true;
protected:
	const char* m_Title;
};

