// This will be used for custom themes later.
// Currently, everything in here is hardcoded and has nothing to do with the final version of this.
#pragma once

namespace Style {
	// bottom screen
	const int ButtonHeight = 32;
	const int ButtonWidth = 119;
	const int SettingsTextPosX = 75;
	const int BackTextPosX = 266;
	const int ButtonTextPosY = SCREEN_HEIGHT - (Style::ButtonHeight / 2);
	const int IconsPosX = 37;
	const int IconsPosY = 18;
	const int IconsMargin = 7;
	const int EntryDimensions = 56;
	const int Rows = 3;
	const int Columns = 4;
	const int MinPages = 6;
	const int PageMoveSpeed = 15;

	// top screen
	const int HeaderBarHeight = 20;
	const int HeaderIconMargin = 5;
	const int LogoFadeSpeed = 35;
	const double LogoScale = 0.5f;
	const int LogoMoveOffset = 2;

	// colors
	const unsigned int ClearColor = Colors::White;
	const unsigned int TextColor = Colors::Black;
	const unsigned int TextColorSecondary = Colors::DarkGrey;
	const unsigned int TextColorWhite = Colors::White;
	const unsigned int HomebrewBlue = RGBA8(73, 164, 244, 255);

	const std::string MainFont = "romfs:/fonts/main.ttf";
	const unsigned int ButtonTextSize = 14;
	const unsigned int TimeTextSize = 12;
}
