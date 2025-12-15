#include "screen.h"

#include "raylib.h"

namespace screen
{
	static const int width = 1040;
	static const int height = 720;
	static const std::string name = "1942";

	void openWindow()
	{
		InitWindow(width, height, name.c_str());
	}

	void closeWindow()
	{
		CloseWindow();
	}
}
