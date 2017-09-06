#pragma once

// TODO: refactor this to use the `Text` class
class Notification {
private:
	std::string m_text;
	sftd_font *m_font;
	bool m_shown;
	unsigned int m_frameCounter, m_opacity, m_showTime;

public:
	Notification();
	virtual ~Notification();

	void show(std::string t_text, unsigned int t_showTime = 60);
	void update();
};
