#pragma once
#include <windows.h>
#include <stdio.h>

#define engLOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

enum moves_camera
{
	MOVE_STRAIGHT	= 1,
	MOVE_RIGTH,
	MOVE_LEFT,
	MOVE_BACK,
	ROTATE_UP,
	ROTATE_DOWN,
	ROTATE_RIGHT,
	ROTATE_LEFT
};

// Constants -----------
#define DEGTORAD 0.01745329251f
#define RADTODEG 1.0f / DEGTORAD

// Configuration -----------
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Super Awesome Engine"