#include "includes.h"

Console::Console() {
	m_color = 0;
	m_bright = true;
	this->m_screen = GFX_TOP;
}

void Console::init(gfxScreen_t t_screen) {
	consoleInit(t_screen, NULL);
	this->m_screen = t_screen;
}

void Console::print(std::string t_message, int t_color, bool t_bright, bool t_custom_pos, int t_x, int t_y) {
	int color;
	bool bright;

	if(t_color == -1) {
		color = this->m_color;
		bright = this->m_bright;
	} else {
		color = t_color;
		bright = t_bright;
	}

	std::string color_s, pos_s;

	if(bright) {
		color_s = "\x1b[" + std::to_string(color) + ";1m";
	} else {
		color_s = "\x1b[" + std::to_string(color) + "m";
	}

	if(t_custom_pos) {
		pos_s = "\x1b[" + std::to_string(t_y) + ";" + std::to_string(t_x) + "H";
	}

	std::string reset_string = "\x1b[0m";
	std::string out = color_s + pos_s + t_message + reset_string;
	std::cout << out;
}

void Console::setColor(int t_color, bool t_bright) {
	this->m_color = t_color;
	this->m_bright = t_bright;
}
