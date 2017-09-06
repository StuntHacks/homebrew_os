#pragma once
#include "includes.h"

class RecoveryMenu {
private:
	std::vector<menuEntry_s*> m_entries;
	unsigned int m_selected;
	bool m_entryLaunched;

public:
	RecoveryMenu();

	void pushEntry(menuEntry_s* t_me) { this->m_entries.push_back(t_me); };
	void loadEntries(std::string t_path = "sdmc:/3ds");

	std::vector<menuEntry_s*> getEntries() { return this->m_entries; };
	unsigned int getEntryAmount() { return this->m_entries.size(); };
	unsigned int getSelected() { return this->m_selected; };
	menuEntry_s* getSelectedEntry() { return this->m_entries[this->m_selected]; };
	bool entryLaunched() { return this->m_entryLaunched; };

	void draw();
	void update();
};
