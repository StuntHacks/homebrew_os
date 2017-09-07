#include "includes.h"
#include "./style.h"

MenuPage::MenuPage(int t_screen) {
	this->m_currentScreen = t_screen;
	this->m_lastScreen = t_screen;
	this->m_buttonMode = false;
	this->m_moving = false;
	this->m_selected = 0;

	if(t_screen == 0) {
		this->m_opacity = 255;
	} else {
		this->m_opacity = 80;
	}

	this->m_pos = Style::IconsPosX + ((WIDTH_BOTTOM - (Style::IconsPosX * 1.5)) * this->m_currentScreen);
}

 MenuPage::~MenuPage() {

 }

void MenuPage::addEntry(MenuEntry t_me) {
	this->m_menuEntries.push_back(t_me);
}

void MenuPage::setSelected(int t_id) {
	this->m_selected = t_id;

	for(int i = 0; i < this->m_menuEntries.size(); i++) {
		this->m_menuEntries[i].setSelected(false);
	}

	this->m_menuEntries[this->m_selected].setSelected(true);
}

void MenuPage::setScreen(int t_screen) {
	this->m_currentScreen = t_screen;
}

void MenuPage::setButtonMode(bool t_buttonMode) {
	this->m_buttonMode = t_buttonMode;

	if(t_buttonMode) {
		this->m_menuEntries[this->m_selected].setSelected(true);
	} else {
		for(int i = 0; i < this->m_menuEntries.size(); i++) {
			this->m_menuEntries[i].setSelected(false);
		}
	}
}

void MenuPage::draw() {
	int defaultXPos = this->m_pos;

	for(int i = 0, x = defaultXPos, y = Style::IconsPosY; i < this->m_menuEntries.size(); i++) {

		this->m_menuEntries[i].draw(x, y, this->m_opacity);

		x += Style::EntryDimensions + Style::IconsMargin;

		if((i + 1) % Style::Columns == 0) {
			x = defaultXPos;
			y += Style::EntryDimensions + Style::IconsMargin;
		}
	}
}

void MenuPage::update() {
	if(this->m_currentScreen != this->m_lastScreen) {
		if(this->m_currentScreen == 0) {
			if(this->m_opacity < 255) {
				this->m_opacity += 5;
			} else {
				this->m_opacity = 255;
			}
		} else {
			if(this->m_opacity > 80) {
				this->m_opacity -= 5;
			} else {
				this->m_opacity = 80;
			}
		}
	}

	if(this->m_currentScreen > this->m_lastScreen) {
		this->m_moving = true;

		if(this->m_pos < Style::IconsPosX + ((WIDTH_BOTTOM - (Style::IconsPosX * 1.5)) * this->m_currentScreen)) {
			this->m_pos += Style::PageMoveSpeed;
		} else {
			if(this->m_pos > Style::IconsPosX + ((WIDTH_BOTTOM - (Style::IconsPosX * 1.5)) * this->m_currentScreen)) {
				this->m_pos = Style::IconsPosX + ((WIDTH_BOTTOM - (Style::IconsPosX * 1.5)) * this->m_currentScreen);
			}

			if(this->m_currentScreen == 0) {
				this->m_opacity = 255;
			} else {
				this->m_opacity = 80;
			}

			this->m_lastScreen = this->m_currentScreen;
		}
	} else if(this->m_currentScreen < this->m_lastScreen) {
		this->m_moving = true;

		if(this->m_pos > Style::IconsPosX + ((WIDTH_BOTTOM - (Style::IconsPosX * 1.5)) * this->m_currentScreen)) {
			this->m_pos -= Style::PageMoveSpeed;
		} else {
			if(this->m_pos < Style::IconsPosX + ((WIDTH_BOTTOM - (Style::IconsPosX * 1.5)) * this->m_currentScreen)) {
				this->m_pos = Style::IconsPosX + ((WIDTH_BOTTOM - (Style::IconsPosX * 1.5)) * this->m_currentScreen);
			}

			if(this->m_currentScreen == 0) {
				this->m_opacity = 255;
			} else {
				this->m_opacity = 80;
			}

			this->m_lastScreen = this->m_currentScreen;
		}
	} else {
		this->m_moving = false;
	}

	if(this->m_moving || (this->m_currentScreen <= 1 && this->m_currentScreen >= -1)) {
		draw();
	}
}
