#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPWidgets.h"
#include "XPLMUtilities.h"
#include <string.h>
#include <string>
#include "ui/opengl.h"
#include "ui/Button.h"

#ifndef XPLM300
	#error This is made to be compiled against the XPLM300 SDK
#endif

#include "ui/Colors.h"
#include "ui/Input.h"

static XPLMWindowID g_window = NULL;

xPing::Button *button;
xPing::Input *textInput;
xPing::Input* passwordInput;

int clicks = 0;
int lastX;
int lastY;

void draw_window(XPLMWindowID in_window_id, void *in_refcon);

int mouse_handler(XPLMWindowID in_window_id, int x, int y, XPLMMouseStatus in_mouse, void* in_refcon) {
	button->checkClick(in_mouse);
	textInput->checkClick();
	passwordInput->checkClick();
	return 1; 
}

XPLMCursorStatus cursor_handler(XPLMWindowID in_window_id, int x, int y, void* in_refcon) {
	button->checkHover(x, y);
	textInput->checkHover(x, y);
	passwordInput->checkHover(x, y);
	return xplm_CursorDefault;
}

void key_handler(XPLMWindowID in_window_id, char key, XPLMKeyFlags flags, char virtual_key, void* in_refcon, int losing_focus) {
	if (losing_focus) {
		XPLMDebugString("Losing focus\n");
		return;
	}

	std::string msg = "Key pressed: " + key + '\n';
	XPLMDebugString(msg.c_str());

	textInput->checkKey(key);
	passwordInput->checkKey(key);
}

int dummy_wheel_handler(XPLMWindowID inWindowID, int x, int y, int wheel, int clicks, void* inRefcon) { return 0; }

PLUGIN_API int XPluginEnable(void) {
    return 1;
}
PLUGIN_API void XPluginDisable(void) { }

PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void* inParam) { }

PLUGIN_API int XPluginStart(char *outName, char *outSig, char *outDesc) {
    strcpy(outName, "xPing");
    strcpy(outSig, "net.jazbelt.xping");
    strcpy(outDesc, "ACARS plugin with CPDLC capabilities");

    int left, bottom, right, top;
    XPLMGetScreenBoundsGlobal(&left, &top, &right, &bottom);
    
    XPLMCreateWindow_t params = {};
    params.structSize = sizeof(params);
    params.visible = 1;
    params.drawWindowFunc = draw_window;
    params.handleMouseClickFunc = mouse_handler;
	params.handleCursorFunc = cursor_handler;
	params.handleKeyFunc = key_handler;
	params.handleMouseWheelFunc = dummy_wheel_handler;
    params.layer = xplm_WindowLayerFloatingWindows;
	params.refcon = NULL;
    params.decorateAsFloatingWindow = xplm_WindowDecorationRoundRectangle;
    params.left = left + 100;
    params.bottom = bottom + 100;
    params.right = params.left + 400;
    params.top = params.bottom + 200;
    
    g_window = XPLMCreateWindowEx(&params);

	if (g_window == NULL) {
		return 0;
	}

	XPLMSetWindowTitle(g_window, "xPing!");

	XPLMDebugString("xPing: Plugin started\n");

	int l, t, r, b;
	XPLMGetWindowGeometry(g_window, &l, &t, &r, &b);
	lastX = l;
	lastY = t;

	button = new xPing::Button(l + 20, b + 20, "Click me!");
	button->registerClickCallback([]() {
		std::string msg = "Button clicked " + std::to_string(++clicks) + " times!\n";
		button->changeLabel(msg);
		XPLMDebugString(msg.c_str());
	});

	textInput = new xPing::Input(l + 20, t - 20, "Enter text here:");
	passwordInput = new xPing::Input(l + 20, t - 50, "Enter password here:", 30, true);
    
    return 1;
}

PLUGIN_API void XPluginStop(void) {
    XPLMDestroyWindow(g_window);
	delete button;
	delete textInput;
	delete passwordInput;
	g_window = NULL;
}

void draw_window(XPLMWindowID in_window_id, void *in_refcon) {
	XPLMTakeKeyboardFocus(g_window);

    int l, t, r, b;
    XPLMGetWindowGeometry(in_window_id, &l, &t, &r, &b);

    XPLMSetGraphicsState
	(
		0, // No fog
		0, // No lighting
		0, // No alpha testing
		1, // Alpha blending
		1, // No depth testing
		0, // No depth writing
		0  // No depth offset
	);

	// Draw a black rectangle as the window background
	glColor4fv(xPing::Colors::BLACK);
		glBegin(GL_QUADS);
		glVertex2i(l, t);
		glVertex2i(r, t);
		glVertex2i(r, b);
		glVertex2i(l, b);
	glEnd();

    glColor4fv(xPing::Colors::GREEN);
	glBegin(GL_LINE_LOOP);
	    glVertex2i(l, t);
	    glVertex2i(r, t);
	    glVertex2i(r, b);
	    glVertex2i(l, b);
	glEnd();

	int deltaX = l - lastX;
	int deltaY = t - lastY;

	button->updatePosition(deltaX, deltaY);
	button->draw();

	textInput->updatePosition(deltaX, deltaY);
	textInput->draw();

	passwordInput->updatePosition(deltaX, deltaY);
	passwordInput->draw();

	lastX = l;
	lastY = t;
}

