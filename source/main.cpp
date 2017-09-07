#include "includes.h"

int main(int argc, char **argv)
{
	osSetSpeedupEnable(true);

	//Initialize libraries
	sf2d_init();
	sftd_init();
	Result ptmu_result = ptmuInit();
	Result romfs_result = romfsInit();
	launchInit();
	sf2d_set_3D(true);

	bool recovery = false, error = false, menuEntryLaunched = false;
	menuEntry_s* launchedEntry;
	std::string errorCode = "";

	hidScanInput();
	if(hidKeysHeld() & KEY_SELECT) recovery = true;

	if(romfs_result) {
		recovery = true;
		error = true;
		errorCode += "100 RomFS init failed\n";
	}

	if(ptmu_result) {
		recovery = true;
		error = true;
		errorCode += "200 PTMU init failed\n";
	}

	if(recovery) {
		Console c;
		c.init(GFX_BOTTOM);
		int recoveryLength = 9;

		// c.print("FTP-Adress: ", ConsoleColors::Yellow);
		// c.print("10.0.0.62\n", ConsoleColors::Cyan);
		// c.print("Port:       ", ConsoleColors::Yellow);
		// c.print("5000", ConsoleColors::Cyan);
		c.print("Recovery!", -1, true, true, (CONSOLE_ROWS_BOTTOM / 2) - (recoveryLength / 2), CONSOLE_LINES / 2);

		if(error) {
			c.print("Error-Code: " + errorCode, ConsoleColors::Red, true, true, 0, CONSOLE_LINES);
		}

		consoleInit(GFX_TOP, NULL);

		RecoveryMenu menu;
		menu.loadEntries("sdmc:/3ds");
		menu.draw();

		while (aptMainLoop())
		{
			if(menu.entryLaunched()) {
				menuEntryLaunched = true;
				launchedEntry = menu.getSelectedEntry();
				break;
			}

			//Scan all the inputs. This should be done once for each frame
			hidScanInput();
			if (hidKeysDown() & KEY_START) break; // break in order to return to hbmenu

			menu.update();

			gfxFlushBuffers();
			gfxSwapBuffers();
			gspWaitForVBlank();
		}
	} else {
		Menu menu;
		menu.loadEntries();

		// Main loop
		while (aptMainLoop())
		{
			if(menu.entryLaunched()) {
				menuEntryLaunched = true;
				launchedEntry = menu.getSelectedEntry();
				break;
			}

			//Scan all the inputs. This should be done once for each frame
			hidScanInput();
			if (menu.getExited()) break; // break in order to return to hbmenu

			menu.update();

			//Swap the buffers
			sf2d_swapbuffers();
		}
	}

	// exit libraries
	romfsExit(); // VERY important
	ptmuExit();
	sftd_fini();
	sf2d_fini();

	if(menuEntryLaunched) {
		launchMenuEntry(launchedEntry);
	}

	// finally, exit the launcher
	launchExit();

	// close the launcher
	return 0;
}
