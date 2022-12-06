#pragma once

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

enum type_screen
{
	FULLSCREEN = 1,
	RESIZABLE,
	BORDERLESS
};

class ModuleWindow : public Module
{
public:

	ModuleWindow();
	virtual ~ModuleWindow();

	bool Init();
	bool CleanUp();

	void WindowResized(int InWidth, int InHeight);

	void SetTypeScreen(type_screen InTypeScreen);
	float GetBrightness();
	void SetBrightness(float& InBrightness);
	inline type_screen GetTypeScreen() { return m_ActualTypeScreen; }
	void SetWidth(int& InWidth);
	inline const int& GetWidth() { return m_Width; }
	void SetHeight(int& InHeight);
	inline const int& GetHeight() { return m_Height; }
	inline const int& GetMaxWidht() { return m_MaxWidth; }
	inline const int& GetMaxHeight() { return m_MaxHeight; }

public:
	SDL_Window* m_Window = NULL;

	SDL_Surface* m_Screen_Surface = NULL;

private:
	type_screen m_ActualTypeScreen = RESIZABLE;
	int m_Width, m_Height;
	int m_MaxWidth, m_MaxHeight;

};