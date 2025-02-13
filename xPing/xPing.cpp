#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPWidgets.h"
#include "XPStandardWidgets.h"
#include "XPWidgetUtils.h"
#include "XPLMUtilities.h"
#include <string.h>
#include <string>
#if IBM
	#include <windows.h>
#endif
#if LIN
	#include <GL/gl.h>
#elif __GNUC__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#ifndef XPLM300
	#error This is made to be compiled against the XPLM300 SDK
#endif

static XPLMWindowID g_window = NULL;
static XPWidgetID g_widget_window = NULL;
static XPWidgetID g_button = NULL;

void draw_window(XPLMWindowID in_window_id, void *in_refcon);
int widget_handler(XPWidgetMessage message, XPWidgetID widgetId, intptr_t param1, intptr_t param2);

PLUGIN_API int XPluginStart(char *outName, char *outSig, char *outDesc) {
    strcpy(outName, "Widget Test");
    strcpy(outSig, "net.example.widgettest");
    strcpy(outDesc, "Testing widgets inside an XPLM window");

    int left, bottom, right, top;
    XPLMGetScreenBoundsGlobal(&left, &top, &right, &bottom);
    
    XPLMCreateWindow_t params = {};
    params.structSize = sizeof(params);
    params.visible = 1;
    params.drawWindowFunc = draw_window;
    params.left = left + 100;
    params.bottom = bottom + 100;
    params.right = params.left + 300;
    params.top = params.bottom + 200;
    params.layer = xplm_WindowLayerFloatingWindows;
    params.decorateAsFloatingWindow = xplm_WindowDecorationRoundRectangle;
    
    g_window = XPLMCreateWindowEx(&params);

    g_widget_window = XPCreateWidget(params.left, params.top, params.right, params.bottom, 1, "Widget Window", 1, NULL, xpWidgetClass_MainWindow);
    g_button = XPCreateWidget(params.left + 50, params.top - 50, params.left + 150, params.top - 100, 1, "Click Me", 0, g_widget_window, xpWidgetClass_Button);
    XPAddWidgetCallback(g_button, widget_handler);
    
    return 1;
}

PLUGIN_API void XPluginStop(void) {
    XPDestroyWidget(g_widget_window, 1);
    XPLMDestroyWindow(g_window);
}

void draw_window(XPLMWindowID in_window_id, void *in_refcon) {
    int l, t, r, b;
    XPLMGetWindowGeometry(in_window_id, &l, &t, &r, &b);
    
    float bg_color[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glColor4fv(bg_color);
    glBegin(GL_QUADS);
    glVertex2i(l, b);
    glVertex2i(r, b);
    glVertex2i(r, t);
    glVertex2i(l, t);
    glEnd();
}

int widget_handler(XPWidgetMessage message, XPWidgetID widgetId, intptr_t param1, intptr_t param2) {
    if (message == xpMsg_PushButtonPressed && widgetId == g_button) {
        XPLMDebugString("Button clicked!\n");
        return 1;
    }
    return 0;
}

