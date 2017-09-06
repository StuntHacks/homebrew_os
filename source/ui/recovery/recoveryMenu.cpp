#include "includes.h"

RecoveryMenu::RecoveryMenu() {
	this->m_selected = 0;
	this->m_entryLaunched = false;
}

void RecoveryMenu::loadEntries(std::string t_path) {
	menuScan(t_path.c_str());

	menu_s* menu = menuGetCurrent();
	menuEntry_s* me;

	int i = 0;

	for (me = menu->firstEntry; me; me = me->next, i++) {
		pushEntry(me);
	}
}

void RecoveryMenu::update() {
	if(hidKeysDown() & KEY_DOWN) {
		if(this->m_selected < this->m_entries.size() - 1)
			this->m_selected++;

		draw();
	}

	if(hidKeysDown() & KEY_UP) {
		if(this->m_selected > 0)
			this->m_selected--;

		draw();
	}

	if(hidKeysDown() & KEY_A) {
		menuEntry_s* me = this->m_entries[this->m_selected];

		if(me->type == ENTRY_TYPE_FILE) {
			this->m_entryLaunched = true;
		}
	}
}

// TODO: clean up this mess
void RecoveryMenu::draw() {
	for(int line = 0; line < CONSOLE_LINES; line++) {
		unsigned int current_entry = this->m_selected + line;

		if(current_entry < this->m_entries.size()) {
			if(line == 0) {
				printf("\x1b[%d;1H\x1b[31;1m%s\x1b[0m%s", line + 1, this->m_entries[current_entry]->name, std::string(CONSOLE_ROWS_TOP - strlen(this->m_entries[current_entry]->name), ' ').c_str());
			} else {
				printf("\x1b[%d;0H%s%s", line + 1, this->m_entries[current_entry]->name, std::string(CONSOLE_ROWS_TOP - strlen(this->m_entries[current_entry]->name), ' ').c_str());
			}
		} else {
			printf("\x1b[%d;0H%s", line + 1, std::string(CONSOLE_ROWS_TOP, ' ').c_str());
		}
	}
}
