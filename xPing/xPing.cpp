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

static XPLMWindowID g_window = NULL;

xPing::Button *button;
int lastX;
int lastY;

void draw_window(XPLMWindowID in_window_id, void *in_refcon);
int draw_nuklear(XPLMDrawingPhase inPhase, int inIsBefore, void* inRefcon);

int mouse_handler(XPLMWindowID in_window_id, int x, int y, XPLMMouseStatus in_mouse, void* in_refcon) {
	button->checkClick(in_mouse);
	return 1; 
}

XPLMCursorStatus cursor_handler(XPLMWindowID in_window_id, int x, int y, void* in_refcon) {
	button->checkHover(x, y);
	return xplm_CursorDefault;
}

void dummy_key_handler(XPLMWindowID in_window_id, char key, XPLMKeyFlags flags, char virtual_key, void* in_refcon, int losing_focus) { }

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
	params.handleKeyFunc = dummy_key_handler;
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

	button = new xPing::Button(l + 200, t - 100, "Click me!");

	button->registerClickCallback([]() {
		XPLMDebugString("xPing: Button clicked!\n");
	});
    
    return 1;
}

PLUGIN_API void XPluginStop(void) {
    XPLMDestroyWindow(g_window);
	delete button;
	g_window = NULL;
}

void draw_window(XPLMWindowID in_window_id, void *in_refcon) {
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

    float green[] = { 0.0, 1.0, 0.0, 1.0 };
	float black[] = { 0.0, 0.0, 0.0, 1.0 };

	// Draw a black rectangle as the window background
	glColor4fv(black);
		glBegin(GL_QUADS);
		glVertex2i(l, t);
		glVertex2i(r, t);
		glVertex2i(r, b);
		glVertex2i(l, b);
	glEnd();

    glColor4fv(green);
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

	lastX = l;
	lastY = t;
}

