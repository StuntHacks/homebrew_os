#pragma once
#include "includes.h"
#include "drawing.h"
#include "./style.h"
#include "./notification.h"
#include "./menuPage.h"
#include "./menuEntry.h"

class Menu {
private:
	std::vector<menuEntry_s*> m_entries;
	std::vector<MenuPage> m_menuPages;
	std::string m_dir;
	unsigned int m_selected, m_selectedOnScreen, m_selectedRow, m_selectedCol, m_frameCounter, m_batteryIconState, m_currentScreen;
	int m_logoOpacity, m_logoXPos, m_logoMoveDir;
	double m_logoScale;
	bool m_entryLaunched, m_batteryIconShown, m_logoShown, m_logoFade, m_buttonMode, m_hasEntries, m_inDir, m_exited;

	sf2d_texture 	*m_buttonBackTex,
								*m_buttonBackPushedTex,
								*m_buttonSettingsTex,
								*m_buttonSettingsPushedTex,
								*m_logo;

	std::vector<sf2d_texture*> m_batteryIcons, m_wifiIcons;

	Text *m_settingsText, *m_backText, *m_timeText, *m_appTitle;
	Notification m_not;

	// touch control
	bool m_settingsButtonTouched, m_backButtonTouched, m_menuEntryTouched;
	unsigned int m_touchedEntry;

public:
	Menu();
	virtual ~Menu();

	void pushEntry(menuEntry_s* t_me) { this->m_entries.push_back(t_me); };
	void loadEntries(std::string t_path = "sdmc:/3ds");

	void launchEntry(int t_id);

	void navigateLeft();
	void navigateRight();

	std::vector<menuEntry_s*> getEntries() { return this->m_entries; };
	unsigned int getEntryAmount() { return this->m_entries.size(); };
	bool getExited() { return this->m_exited; };
	menuEntry_s* getSelectedEntry() { return this->m_entries[this->m_selected]; };
	bool entryLaunched() { return this->m_entryLaunched; };

	// TODO: move these two to menu.cpp and clean them up
	inline bool touchInAbsoluteBox(int t_x, int t_y, int t_x2, int t_y2, int t_type = 0) {
		touchPosition touch;
		hidTouchRead(&touch);

		u32 keyState;

		if(t_type == 0) {
			keyState = hidKeysHeld();
		} else if(t_type == 1) {
			keyState = hidKeysDown();
		} else {
			keyState = hidKeysUp();
		}

		return	keyState & KEY_TOUCH
						&& touch.px >= t_x
						&& touch.py >= t_y
						&& touch.px <= t_x2
						&& touch.py <= t_y2;
	}
	inline bool touchInRelativeBox(int t_x, int t_y, int t_w, int t_h, int t_type = 0) {
		touchPosition touch;
		hidTouchRead(&touch);

		u32 keyState;

		if(t_type == 0) {
			keyState = hidKeysHeld();
		} else if(t_type == 1) {
			keyState = hidKeysDown();
		} else {
			keyState = hidKeysUp();
		}

		return	keyState & KEY_TOUCH
						&& touch.px >= t_x
						&& touch.py >= t_y
						&& touch.px <= t_x + t_w
						&& touch.py <= t_y + t_h;
	}

	void drawLogo();
	void drawTop();
	void drawBottom();
	void draw();
	void update();
};
