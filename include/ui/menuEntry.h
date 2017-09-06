#pragma once

class MenuEntry {
private:
	std::string m_title;
	bool m_selected, m_empty, m_hasIcon;
	sf2d_texture	*m_entryEmptyTex,
								*m_entryBorderTex,
								*m_entryBorderSelectedTex,
								m_icon;
	menuEntry_s* m_me;

public:
	MenuEntry(menuEntry_s* t_me);
	virtual ~MenuEntry();

	void draw(int t_x, int t_y);
};
