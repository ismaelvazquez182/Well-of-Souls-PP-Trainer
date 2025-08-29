#pragma once

#include <string>

class BHGui {

public:
	BHGui(std::string title, unsigned int window_width, unsigned int window_height);
	~BHGui();
	void Run(void (*action_function)());
private:
	const std::string m_window_title;
	const unsigned int m_window_width;
	const unsigned int m_window_height;

	const std::string m_button_text{ "Max GP/PP" };
	const unsigned int m_button_width{ 400 };
	const unsigned int m_button_height{ 100 };
	const unsigned int m_button_font_size{ 48 };
};
