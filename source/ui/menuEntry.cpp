#include "includes.h"
#include "./style.h"

MenuEntry::MenuEntry(menuEntry_s* t_me) {
	this->m_entryEmptyTex = sfil_load_PNG_file("romfs:/images/menu/entry_empty.png", SF2D_PLACE_RAM);
	this->m_entryBorderTex = sfil_load_PNG_file("romfs:/images/menu/entry_border.png", SF2D_PLACE_RAM);
	this->m_entryBorderSelectedTex = sfil_load_PNG_file("romfs:/images/menu/entry_border_selected.png", SF2D_PLACE_RAM);
	this->m_folderTex = sfil_load_PNG_file("romfs:/images/menu/entry_folder.png", SF2D_PLACE_RAM);
	this->m_selected = false;

	if(t_me == NULL) {
		this->m_empty = true;
	} else {
		this->m_title = t_me->name;
		this->m_description = t_me->description;
		this->m_author = t_me->author;
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

void MenuEntry::draw(int t_x, int t_y, int t_opacity) {
	if(this->m_empty) {
		sf2d_draw_texture_blend(this->m_entryEmptyTex, t_x, t_y, RGBA8(255, 255, 255, t_opacity));
	} else {
		if(this->m_me->type == ENTRY_TYPE_FOLDER) {
			sf2d_draw_texture_blend(this->m_folderTex, t_x + 4, t_y + 4, RGBA8(255, 255, 255, t_opacity));
		} else {
			if(this->m_hasIcon) {
				sf2d_draw_texture_scale_blend(&this->m_icon, t_x + 4, t_y + 4 + this->m_icon.height, 1, -1, RGBA8(255, 255, 255, t_opacity));
			}
		}

		if(this->m_selected) {
			sf2d_draw_texture_blend(this->m_entryBorderSelectedTex, t_x, t_y, RGBA8(255, 255, 255, t_opacity));
		} else {
			sf2d_draw_texture_blend(this->m_entryBorderTex, t_x, t_y, RGBA8(255, 255, 255, t_opacity));
		}
	}
}
