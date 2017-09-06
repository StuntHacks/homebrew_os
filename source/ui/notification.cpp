#include "includes.h"
#include "./style.h"

Notification::Notification() {
	this->m_text = "";
	this->m_font = sftd_load_font_file(Style::MainFont.c_str());
	this->m_shown = false;
	this->m_frameCounter = 0;
	this->m_opacity = 255;
	this->m_showTime = 45;
}

Notification::~Notification() {

}

void Notification::show(std::string t_text, unsigned int t_showTime) {
	this->m_shown = true;
	this->m_text = t_text;
	this->m_frameCounter = 0;
	this->m_opacity = 255;
	this->m_showTime = t_showTime;
}

void Notification::update() {
	if(this->m_shown) {
		if(this->m_opacity <= 0) {
			this->m_shown = false;
		} else {
			this->m_frameCounter++;

			if(this->m_frameCounter > this->m_showTime) {
				if(this->m_opacity > 1) {
					this->m_opacity -= 2;
				} else {
					this->m_opacity -= 1;
				}
			}
		}

		int textWidth = 0, textHeight = 0;
		sftd_calc_bounding_box(&textWidth, &textHeight, this->m_font, 14, WIDTH_BOTTOM - 40, this->m_text.c_str());

		int rectHeight = 0;

		if(textHeight > ((SCREEN_HEIGHT / 5) * 2) - 40) {
			rectHeight = textHeight + 40;
		} else {
			rectHeight = (SCREEN_HEIGHT / 5) * 2;
		}

		int rectPosY = (SCREEN_HEIGHT / 2) - (rectHeight / 2);

		sf2d_draw_rectangle(0, rectPosY, WIDTH_BOTTOM, rectHeight, RGBA8(0, 0, 0, (int) (this->m_opacity * 0.75)));
		sftd_draw_text_wrap(this->m_font, 20, (rectPosY + (rectHeight / 2)) - (textHeight / 2), RGBA8(255, 255, 255, this->m_opacity), 14, WIDTH_BOTTOM - 40, this->m_text.c_str());
	}
}
