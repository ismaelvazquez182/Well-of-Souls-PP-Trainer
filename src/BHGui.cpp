#include "BHGui.h"

#pragma warning(disable : 4996)
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

BHGui::BHGui(std::string window_title, unsigned int window_width, unsigned int window_height) : 
	m_window_title(window_title),
	m_window_width(window_width),
	m_window_height(window_height)
{
	InitWindow(m_window_width, m_window_height, m_window_title.c_str());
	SetTargetFPS(60);

	GuiSetStyle(DEFAULT, TEXT_SIZE, m_button_font_size);
}

BHGui::~BHGui() { CloseWindow(); }

void BHGui::Run(void (*action_function)())
{
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);
		if (GuiButton({ float(m_window_width / 2 - m_button_width / 2),
			float(m_window_height / 2 - m_button_height / 2),
			float(m_button_width),
			float(m_button_height) }, m_button_text.c_str())) action_function();
		EndDrawing();
	}
}
