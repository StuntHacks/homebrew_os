#pragma once
#include "includes.h"
#define IT_TEST 0
class Console {
private:
	int m_color;
	bool m_bright;
	gfxScreen_t m_screen;

public:
	Console();

	void init(gfxScreen_t t_screen);
	void print(std::string t_message, int t_color = -1, bool t_bright = true, bool t_custom_pos = false, int t_x = 0, int t_y = 0);
	void setColor(int t_color, bool t_bright = true);
};
