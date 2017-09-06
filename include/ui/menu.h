#pragma once
#include "includes.h"
#include "drawing.h"
#include "./style.h"
#include "./notification.h"
#include "./menuEntry.h"

class Menu {
private:
	std::vector<menuEntry_s*> m_entries;
	std::vector<MenuEntry> m_menuEntries;
	unsigned int m_selected, m_frameCounter, m_batteryIconState;
	bool m_entryLaunched, m_batteryIconShown;

	sf2d_texture 	*m_buttonLaunchTex,
								*m_buttonLaunchPushedTex,
								*m_buttonSettingsTex,
								*m_buttonSettingsPushedTex;

	std::vector<sf2d_texture*> m_batteryIcons, m_wifiIcons;

	Text *m_settingsText, *m_launchText, *m_timeText;
	Notification m_not;

	// touch control
	bool m_settingsButtonTouched, m_launchButtonTouched, m_menuEntryTouched;
	unsigned int m_touchedEntry;

public:
	Menu();
	virtual ~Menu();

	void pushEntry(menuEntry_s* t_me) { this->m_entries.push_back(t_me); };
	void loadEntries(std::string t_path = "sdmc:/3ds");

	std::vector<menuEntry_s*> getEntries() { return this->m_entries; };
	unsigned int getEntryAmount() { return this->m_entries.size(); };
	unsigned int getSelected() { return this->m_selected; };
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

	void drawTop();
	void drawBottom();
	void draw();
	void update();
};
