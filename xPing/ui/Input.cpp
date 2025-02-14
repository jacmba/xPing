#include "Input.h"
#include "opengl.h"
#include "Colors.h"
#include <XPLMGraphics.h>

xPing::Input::Input(int x, int y, std::string txt, int max, bool pass)
{
	focused = false;

	std::string measureSting = "";
	for (int i = 0; i < max; i++) {
		measureSting += "W";
	}

	width = XPLMMeasureString(xplmFont_Proportional, measureSting.c_str(), measureSting.length()) + 10;
	height = 20;
	l = x;
	t = y;
	r = x + width;
	b = y - height;

	password = pass;
	text = txt;
	hovered = false;
	focused = false;
}

void xPing::Input::draw()
{
	float* color = Colors::GREEN;

	glColor4fv(color);
	glBegin(GL_LINE_LOOP);
		glVertex2i(l, t);
		glVertex2i(r, t);
		glVertex2i(r, b);
		glVertex2i(l, b);
	glEnd();

	std::string displayText = text;
	if (password) {
		for (int i = 0; i < displayText.size(); i++) {
			displayText[i] = '*';
		}
	}

	float stringSize = XPLMMeasureString(xplmFont_Proportional, displayText.c_str(), displayText.length());

	// Draw cursor square next to the text
	if (focused) {
		glColor4fv(color);
			glBegin(GL_QUADS);
			glVertex2i(l + 5 + stringSize, t - 2);
			glVertex2i(l + 10 + stringSize, t - 2);
			glVertex2i(l + 10 + stringSize, b + 2);
			glVertex2i(l + 5 + stringSize, b + 2);
		glEnd();
	}

	XPLMDrawString(color, l + 5, t - 10, displayText.c_str(), NULL, xplmFont_Proportional);
}

void xPing::Input::checkClick()
{
	focused = hovered;
}

void xPing::Input::checkHover(int x, int y)
{
	hovered = x >= l && x <= r && y <= t && y >= b;
}

void xPing::Input::checkKey(char key)
{
	if (focused) {
		if (key == 8) {
			if (text.size() > 0) {
				text.pop_back();
			}
		}
		else {
			text += key;
		}
	}
}
