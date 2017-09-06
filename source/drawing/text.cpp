#include "includes.h"

Text::Text(sftd_font *t_font, std::string t_text, unsigned int t_color, int t_x, int t_y, unsigned int t_size) {
	this->m_text	= t_text;
	this->m_font	= t_font;
	this->m_x			= t_x;
	this->m_y			= t_y;
	this->m_size	= t_size;
	this->m_color = t_color;
}

Text::Text(std::string t_font, std::string t_text, unsigned int t_color, int t_x, int t_y, unsigned int t_size) {
	this->m_text	= t_text;
	this->m_font	= sftd_load_font_file(t_font.c_str());
	this->m_x			= t_x;
	this->m_y			= t_y;
	this->m_size	= t_size;
	this->m_color = t_color;
}

Text::~Text() {
	sftd_free_font(m_font);
}

BoundingBox Text::getBoundingBox() {
	int width, height;
	BoundingBox box;

	width = sftd_get_text_width(this->m_font, this->m_size, this->m_text.c_str());
	height = this->m_size;

	box.x = this->m_x;
	box.y = this->m_y;
	box.width = width;
	box.height = height;

	return box;
}

void Text::draw() {
	sftd_draw_text(this->m_font, this->m_x, this->m_y, this->m_color, this->m_size, this->m_text.c_str());
}
