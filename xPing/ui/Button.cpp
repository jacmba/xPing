#include "Button.h"
#include <XPLMGraphics.h>
#include "opengl.h"
#include "Colors.h"

xPing::Button::Button(
	int x,
	int y,
	std::string labelText
)
{
	l = x;
	t = y;
	label = labelText;
	clicked = false;
	hovered = false;

	labelWidth = XPLMMeasureString(xplmFont_Proportional, label.c_str(), label.length());
	buttonHeight = 20;
	buttonWidth = labelWidth + 10;
	r = x + buttonWidth;
	b = y - buttonHeight;
}

void xPing::Button::draw()
{

	float* bg_color = NAVY_BLUE;
	if (hovered) {
		bg_color = HOVER_BLUE;
	}

	if (clicked) {
		bg_color = CLICK_BLUE;
	}

	// Draw the button frame in light gray
	glColor4fv(LIGHT_BLUE);
	glBegin(GL_QUADS);
		glVertex2i(l, t);
		glVertex2i(r, t);
		glVertex2i(r, b);
		glVertex2i(l, b);
	glEnd();

	// Draw the buttom background in medium gray
	glColor4fv(bg_color);
	glBegin(GL_QUADS);
		glVertex2i(l + 1, t - 1);
		glVertex2i(r - 1, t - 1);
		glVertex2i(r - 1, b + 1);
		glVertex2i(l + 1, b + 1);
	glEnd();

	// Draw the button text in the center
	XPLMDrawString(WHITE, l + 5, t - 15, label.c_str(), NULL, xplmFont_Proportional);
}

void xPing::Button::registerClickCallback(std::function<void()> callback)
{
	onClick = callback;
}

void xPing::Button::checkClick(XPLMMouseStatus status)
{
	if (!clicked && hovered && status == xplm_MouseDown) {
		clicked = true;
		onClick();
	}
	else if (clicked && status == xplm_MouseUp) {
		clicked = false;
	}
}

void xPing::Button::checkHover(int x, int y)
{
	hovered = x >= l && x <= r && y <= t && y >= b;
}
