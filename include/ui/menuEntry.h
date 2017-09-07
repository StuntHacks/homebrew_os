#pragma once

class MenuEntry {
private:
	std::string m_title, m_description, m_author;
	bool m_selected, m_empty, m_hasIcon;
	sf2d_texture	*m_entryEmptyTex,
								*m_entryBorderTex,
								*m_entryBorderSelectedTex,
								*m_folderTex,
								m_icon;
	menuEntry_s* m_me;

public:
	MenuEntry(menuEntry_s* t_me);
	virtual ~MenuEntry();

	std::string getTitle() { return this->m_title; };
	std::string getDescription() { return this->m_description; };
	std::string getAuthor() { return this->m_author; };

	void setSelected(bool t_selected) { this->m_selected = t_selected; };

	void draw(int t_x, int t_y, int t_opacity = 255);
};
