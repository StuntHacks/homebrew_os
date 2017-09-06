#pragma once
#include "./menuEntry.h"

class MenuPage {
private:
	bool m_buttonMode, m_moving;
	int m_dir, m_selected, m_currentScreen, m_lastScreen, m_opacity, m_pos;
	std::vector<MenuEntry> m_menuEntries;

public:
	MenuPage(int t_screen);
	virtual ~MenuPage();

	void addEntry(MenuEntry t_me);
	bool isMoving() { return this->m_moving; };
	void setSelected(int t_id);
	void setScreen(int t_screen);
	int getScreen() { return this->m_currentScreen; };
	void setButtonMode(bool t_buttonMode);
	void draw();
	void update();
};
