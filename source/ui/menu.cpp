#include "includes.h"

Menu::Menu() {
	this->m_batteryIconState = 0;
	this->m_frameCounter = 0;
	this->m_selected = 0;
	this->m_currentScreen = 0;
	this->m_logoOpacity = 0;
	this->m_logoScale = Style::LogoScale;
	this->m_entryLaunched = false;
	this->m_batteryIconShown = true;
	this->m_menuEntryTouched = false;
	this->m_settingsButtonTouched = false;
	this->m_launchButtonTouched = false;
	this->m_logoShown = true;
	this->m_logoFade = true;

	this->m_logo = sfil_load_PNG_file("romfs:/images/hb_logo.png", SF2D_PLACE_RAM);

	this->m_buttonLaunchTex = sfil_load_PNG_file("romfs:/images/menu/button_launch.png", SF2D_PLACE_RAM);
	this->m_buttonLaunchPushedTex = sfil_load_PNG_file("romfs:/images/menu/button_launch_pushed.png", SF2D_PLACE_RAM);
	this->m_buttonSettingsTex = sfil_load_PNG_file("romfs:/images/menu/button_settings.png", SF2D_PLACE_RAM);
	this->m_buttonSettingsPushedTex = sfil_load_PNG_file("romfs:/images/menu/button_settings_pushed.png", SF2D_PLACE_RAM);

	this->m_batteryIcons.push_back(sfil_load_PNG_file("romfs:/images/menu/icons/icon_battery_0.png", SF2D_PLACE_RAM));
	this->m_batteryIcons.push_back(sfil_load_PNG_file("romfs:/images/menu/icons/icon_battery_1.png", SF2D_PLACE_RAM));
	this->m_batteryIcons.push_back(sfil_load_PNG_file("romfs:/images/menu/icons/icon_battery_2.png", SF2D_PLACE_RAM));
	this->m_batteryIcons.push_back(sfil_load_PNG_file("romfs:/images/menu/icons/icon_battery_3.png", SF2D_PLACE_RAM));
	this->m_batteryIcons.push_back(sfil_load_PNG_file("romfs:/images/menu/icons/icon_battery_4.png", SF2D_PLACE_RAM));

	this->m_wifiIcons.push_back(sfil_load_PNG_file("romfs:/images/menu/icons/icon_wifi_0.png", SF2D_PLACE_RAM));
	this->m_wifiIcons.push_back(sfil_load_PNG_file("romfs:/images/menu/icons/icon_wifi_1.png", SF2D_PLACE_RAM));
	this->m_wifiIcons.push_back(sfil_load_PNG_file("romfs:/images/menu/icons/icon_wifi_2.png", SF2D_PLACE_RAM));
	this->m_wifiIcons.push_back(sfil_load_PNG_file("romfs:/images/menu/icons/icon_wifi_3.png", SF2D_PLACE_RAM));

	this->m_settingsText = new Text("romfs:/fonts/main.ttf", "Settings", Style::TextColor, 0, 0, Style::ButtonTextSize);
	this->m_launchText = new Text("romfs:/fonts/main.ttf", "Launch", Style::TextColor, 0, 0, Style::ButtonTextSize);
	this->m_timeText = new Text("romfs:/fonts/main.ttf", "", Style::TextColorWhite, 0, 0, Style::TimeTextSize);

	this->m_launchText->setPos(Style::LaunchTextPosX - (this->m_settingsText->getBoundingBox().width / 2), Style::ButtonTextPosY - (this->m_launchText->getBoundingBox().height / 1.7));
	this->m_settingsText->setPos(Style::SettingsTextPosX - (this->m_settingsText->getBoundingBox().width / 2), Style::ButtonTextPosY - (this->m_settingsText->getBoundingBox().height / 1.7));

	// set background color
	sf2d_set_clear_color(Colors::White);
}

Menu::~Menu() {

}

void Menu::loadEntries(std::string t_path) {
	this->m_entries.clear();
	this->m_menuPages.clear();
	menuScan(t_path.c_str());

	menu_s* menu = menuGetCurrent();
	menuEntry_s* me;

	for (me = menu->firstEntry; me; me = me->next) {
		pushEntry(me);
	}

	unsigned int numEntries = this->m_entries.size(), numPages = 0, entriesPerPage = Style::Rows * Style::Columns;
	numPages = (int) std::ceil(numEntries / entriesPerPage);

	for(int i = 0; i <= numPages || i < Style::MinPages; i++) {
		MenuPage page(i);

		for(unsigned int j = entriesPerPage * i; j < entriesPerPage + entriesPerPage * i; j++) {
			if(j < this->m_entries.size()) {
				MenuEntry entry(this->m_entries[j]);
				page.addEntry(entry);
			} else {
				MenuEntry entry(NULL);
				page.addEntry(entry);
			}
		}

		this->m_menuPages.push_back(page);
	}
}

void Menu::navigateRight() {
	if(this->m_currentScreen < this->m_menuPages.size() - 1) {
		this->m_currentScreen++;

		for(int i = 0; i < this->m_menuPages.size(); i++) {
			this->m_menuPages[i].setScreen(this->m_menuPages[i].getScreen() - 1);
		}
	}
}

void Menu::navigateLeft() {
	if(this->m_currentScreen > 0) {
		this->m_currentScreen--;

		for(int i = 0; i < this->m_menuPages.size(); i++) {
			this->m_menuPages[i].setScreen(this->m_menuPages[i].getScreen() + 1);
		}
	}
}

void Menu::update() {
	this->m_frameCounter++;

	if((hidKeysUp() & KEY_TOUCH) && this->m_settingsButtonTouched) {
		this->m_not.show("Sorry, still unimplemented");
	}

	if(touchInRelativeBox(0, SCREEN_HEIGHT - Style::ButtonHeight, Style::ButtonWidth, Style::ButtonHeight, 1)
			|| (touchInRelativeBox(0, SCREEN_HEIGHT - Style::ButtonHeight, Style::ButtonWidth, Style::ButtonHeight) && this->m_settingsButtonTouched)) {
		this->m_settingsButtonTouched = true;
	} else {
		this->m_settingsButtonTouched = false;
	}

	if(touchInRelativeBox(WIDTH_BOTTOM - Style::ButtonWidth, SCREEN_HEIGHT - Style::ButtonHeight, WIDTH_BOTTOM, Style::ButtonHeight, 1)
			|| (touchInRelativeBox(WIDTH_BOTTOM - Style::ButtonWidth, SCREEN_HEIGHT - Style::ButtonHeight, WIDTH_BOTTOM, Style::ButtonHeight) && this->m_launchButtonTouched)) {
		this->m_launchButtonTouched = true;
	} else {
		this->m_launchButtonTouched = false;
	}

	if(!this->m_menuPages[0].isMoving()) {
		if(hidKeysHeld() & KEY_R || hidKeysHeld() & KEY_ZR) {
			navigateRight();
		}

		if(hidKeysHeld() & KEY_L || hidKeysHeld() & KEY_ZL) {
			navigateLeft();
		}
	}

	this->draw();
}

void Menu::draw() {
	this->drawTop();
	this->drawBottom();
}

void Menu::drawLogo() {
	if(this->m_logoFade) {
		if(this->m_logoShown) {
			if(this->m_logoOpacity < 255) {
				this->m_logoOpacity += Style::LogoFadeSpeed;
				this->m_logoScale += Style::LogoScale / (255.f / Style::LogoFadeSpeed);

				if(this->m_logoOpacity > 255) {
					this->m_logoOpacity = 255;
				}

				if(this->m_logoScale > 1) {
					this->m_logoScale = 1;
				}
			} else {
				this->m_logoOpacity = 255;
				this->m_logoScale = 1;
				this->m_logoFade = false;
			}
		} else {
			if(this->m_logoOpacity > 0) {
				this->m_logoOpacity -= Style::LogoFadeSpeed;
				this->m_logoScale -= Style::LogoScale / (255.f / Style::LogoFadeSpeed);

				if(this->m_logoOpacity < 0) {
					this->m_logoOpacity = 0;
				}

				if(this->m_logoScale < Style::LogoScale) {
					this->m_logoScale = Style::LogoScale;
				}
			} else {
				this->m_logoOpacity = 0;
				this->m_logoScale = Style::LogoScale;
				this->m_logoFade = false;
			}
		}
	}

	if(this->m_logoShown || this->m_logoOpacity > 0) {
		int xPos = (WIDTH_TOP / 2) - ((this->m_logo->width * this->m_logoScale) / 2);
		int yPos = (SCREEN_HEIGHT / 2) - ((this->m_logo->height * this->m_logoScale) / 2);
		sf2d_draw_texture_scale_blend(this->m_logo, xPos, yPos, this->m_logoScale, this->m_logoScale, RGBA8(255, 255, 255, this->m_logoOpacity));
	}
}

void Menu::drawTop() {
	// get the time
	u64 timeInSeconds = osGetTime() / 1000;
	u64 dayTime = timeInSeconds % SECONDS_IN_DAY;
	u8 hour = dayTime / SECONDS_IN_HOUR;
	u8 min = (dayTime % SECONDS_IN_HOUR) / SECONDS_IN_MINUTE;

	std::string hourString = std::to_string(hour);
	std::string minString = std::to_string(min);

	if(hourString.size() == 1) {
		hourString = "0" + hourString;
	}

	if(minString.size() == 1) {
		minString = "0" + minString;
	}

	u8 wifiStatus = 0;
	u8 batteryLevel = 0;
	u8 charging = 0;

	wifiStatus = osGetWifiStrength();
	// Result batteryLevelResult = PTMU_GetBatteryLevel(&batteryLevel);
	// Result chargingStateResult = PTMU_GetBatteryChargeState(&charging);

	if(batteryLevel < 2 && charging != 1) {
		if(this->m_frameCounter % 60 == 0) {
			if(this->m_batteryIconShown) {
				this->m_batteryIconShown = false;
			} else {
				this->m_batteryIconShown = true;
			}
		}
	}

	// if(batteryLevelResult) {
	// 	batteryLevel = 0;
	// }
	//
	// if(chargingStateResult) {
	// 	charging = 0;
	// }

	if(charging == 1) {
		if(this->m_frameCounter % 60 == 0) {
			if(this->m_batteryIconState == 4) {
				this->m_batteryIconState = 0;
			} else {
				this->m_batteryIconState++;
			}
		}
	} else {
		this->m_batteryIconState = batteryLevel;
	}

	std::string timeString = hourString + ":" + minString;
	this->m_timeText->setText(timeString);
	this->m_timeText->setPos((WIDTH_TOP / 2) - (this->m_timeText->getBoundingBox().width / 2), (Style::HeaderBarHeight / 2) - (this->m_timeText->getBoundingBox().height / 1.7));

	// Start the frame
	sf2d_start_frame(GFX_TOP, GFX_LEFT);

	// draw the header bar
	sf2d_draw_rectangle(0, 0, WIDTH_TOP, Style::HeaderBarHeight, Style::HomebrewBlue);
	this->m_timeText->draw();
	sf2d_draw_texture(this->m_wifiIcons[wifiStatus], Style::HeaderIconMargin, (Style::HeaderBarHeight / 2) - (this->m_wifiIcons[wifiStatus]->height / 2));

	if(this->m_batteryIconShown) {
		sf2d_draw_texture(this->m_batteryIcons[this->m_batteryIconState], WIDTH_TOP - Style::HeaderIconMargin - this->m_batteryIcons[this->m_batteryIconState]->width, (Style::HeaderBarHeight / 2) - (this->m_batteryIcons[this->m_batteryIconState]->height / 2));
	}

	// header bar shadow (Hacky, lol)
	sf2d_draw_rectangle_gradient(0, Style::HeaderBarHeight, WIDTH_TOP, 5, RGBA8(125, 125, 125, 50), RGBA8(125, 125, 125, 0), SF2D_TOP_TO_BOTTOM);

	if(this->m_frameCounter > 10) {
		drawLogo();
	}
}

void Menu::drawBottom() {
	// Start the frame
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);

	if(this->m_settingsButtonTouched) {
		sf2d_draw_texture(this->m_buttonSettingsPushedTex, 0, SCREEN_HEIGHT - Style::ButtonHeight);
	} else {
		sf2d_draw_texture(this->m_buttonSettingsTex, 0, SCREEN_HEIGHT - Style::ButtonHeight);
	}

	if(this->m_launchButtonTouched) {
		sf2d_draw_texture(this->m_buttonLaunchPushedTex, WIDTH_BOTTOM - Style::ButtonWidth, SCREEN_HEIGHT - Style::ButtonHeight);
	} else {
		sf2d_draw_texture(this->m_buttonLaunchTex, WIDTH_BOTTOM - Style::ButtonWidth, SCREEN_HEIGHT - Style::ButtonHeight);
	}

	// draw menu entries
	for(unsigned int i = 0; i < this->m_menuPages.size(); i++) {
		this->m_menuPages[i].update();
	}

	this->m_settingsText->draw();
	this->m_launchText->draw();
	this->m_not.update();
}
