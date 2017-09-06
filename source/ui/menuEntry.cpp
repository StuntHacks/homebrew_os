#include "includes.h"
#include "./style.h"

MenuEntry::MenuEntry(menuEntry_s* t_me) {
	this->m_entryEmptyTex = sfil_load_PNG_file("romfs:/images/menu/entry_empty.png", SF2D_PLACE_RAM);
	this->m_entryBorderTex = sfil_load_PNG_file("romfs:/images/menu/entry_border.png", SF2D_PLACE_RAM);
	this->m_entryBorderSelectedTex = sfil_load_PNG_file("romfs:/images/menu/entry_border_selected.png", SF2D_PLACE_RAM);
	this->m_selected = false;

	if(t_me == NULL) {
		this->m_empty = true;
	} else {
		this->m_title = t_me->name;
		this->m_empty = false;
		this->m_me = t_me;

		// convert the texture stored in the menu entry to an sf2d_texture
		if(t_me->icon) {
			sf2d_texture icon;
			icon.tex = *m_me->icon;
			icon.tiled = 0;
			icon.width = 48;
			icon.height = 48;
			this->m_icon = icon;
			this->m_hasIcon = true;
		} else {
			this->m_hasIcon = false;
		}
	}
}

MenuEntry::~MenuEntry() {

}

void MenuEntry::draw(int t_x, int t_y) {
	if(this->m_empty) {
		sf2d_draw_texture(this->m_entryEmptyTex, t_x + 4, t_y + 4);
	} else {
		if(this->m_hasIcon) {
			sf2d_draw_texture_scale(&this->m_icon, t_x + 4, t_y + 4 + this->m_icon.height, 1, -1);
		}

		if(this->m_selected) {
			sf2d_draw_texture(this->m_entryBorderSelectedTex, t_x, t_y);
		} else {
			sf2d_draw_texture(this->m_entryBorderTex, t_x, t_y);
		}
	}
}
