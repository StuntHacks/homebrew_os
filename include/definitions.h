#pragma once

#define CONFIG_3D_SLIDERSTATE (*(volatile float*)0x1FF81080)

#define WIDTH_TOP 400 //Width of the top screen
#define WIDTH_BOTTOM 320 //Width of the bottom screen
#define SCREEN_HEIGHT 240 //Height of both screens

#define CONSOLE_LINES 30
#define CONSOLE_ROWS_TOP 50
#define CONSOLE_ROWS_BOTTOM 40

#define SECONDS_IN_DAY 86400
#define SECONDS_IN_HOUR 3600
#define SECONDS_IN_MINUTE 60

#ifdef __cplusplus
	namespace ConsoleColors {
		const int Black		= 30;
		const int Red     = 31;
		const int Green   = 32;
		const int Yellow  = 33;
		const int Blue    = 34;
		const int Magenta = 35;
		const int Cyan    = 36;
		const int White		= 37;
		const int Reset   = 0;
	};

	namespace Colors {
		const unsigned int Black		= RGBA8(0, 0, 0, 255);
		const unsigned int Red			= RGBA8(255, 0, 0, 255);
		const unsigned int Green		= RGBA8(0, 255, 0, 255);
		const unsigned int Yellow		= RGBA8(255, 255, 0, 255);
		const unsigned int Blue			= RGBA8(0, 0, 255, 255);
		const unsigned int Magenta	= RGBA8(255, 0, 255, 255);
		const unsigned int Cyan			= RGBA8(0, 255, 255, 255);
		const unsigned int White		= RGBA8(255, 255, 255, 255);
		const unsigned int Grey			= RGBA8(255, 255, 255, 255);

		const unsigned int DarkRed			= RGBA8(125, 0, 0, 255);
		const unsigned int DarkGreen		= RGBA8(0, 125, 0, 255);
		const unsigned int DarkYellow		= RGBA8(125, 125, 0, 255);
		const unsigned int DarkBlue			= RGBA8(0, 0, 125, 255);
		const unsigned int DarkMagenta	= RGBA8(125, 0, 125, 255);
		const unsigned int DarkCyan			= RGBA8(0, 125, 125, 255);
		const unsigned int DarkGrey			= RGBA8(125, 125, 125, 255);
	};
#endif
