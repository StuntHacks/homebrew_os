#pragma once
#include "includes.h"

struct BoundingBox {
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;

	bool valueInRange(int value, int min, int max) { return (value >= min) && (value <= max); }

	bool intersect(BoundingBox t_box) {
		bool xOverlap = valueInRange(this->x, t_box.x, t_box.x + t_box.width) ||
										valueInRange(t_box.x, this->x, this->x + this->width);

		bool yOverlap = valueInRange(this->y, t_box.y, t_box.y + t_box.height) ||
										valueInRange(t_box.y, this->y, this->y + this->height);

		return xOverlap && yOverlap;
	}
};

class Text {
protected:
	/* data */
	std::string m_text;
	sftd_font *m_font;
	int m_x, m_y;
	unsigned int m_size, m_color;
public:
	Text(sftd_font *t_font, std::string t_text = "", unsigned int t_color = Colors::Black, int t_x = 0, int t_y = 0, unsigned int t_size = 10);
	Text(std::string t_font, std::string t_text = "", unsigned int t_color = Colors::Black, int t_x = 0, int t_y = 0, unsigned int t_size = 10);
	virtual ~Text();

	BoundingBox getBoundingBox();

	std::string getText() { return this->m_text; };
	void setText(std::string t_text) { this->m_text = t_text; };

	// drawing methods
	void draw();

	int getX() { return this->m_x; };
	int getY() { return this->m_y; };
	void setPos(int t_x, int t_y) { this->m_x = t_x; this->m_y = t_y; };

	unsigned int getSize() { return this->m_size; };
	void setSize(unsigned int t_size) { this->m_size = t_size; };

	unsigned int getColor() { return this->m_color; };
	void setColor(unsigned int t_color) { this->m_color = t_color; };

	sftd_font* getFont() { return this->m_font; };
	void setFont(sftd_font *t_font) { this->m_font = t_font; };
	void setFont(std::string t_font) { this->m_font = sftd_load_font_file(t_font.c_str()); };
};
