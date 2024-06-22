#include <X11/Xlib.h>
#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <xcb/xcb.h>

#include <libinput.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <iostream>


void simulateMouseClick(int button, int x, int y)
{
    Display* display = XOpenDisplay(NULL);
    if (!display) {
        std::cerr << "Failed to open display!" << std::endl;
        return;
    }

    int event_base, error_base;
//    if (!XTestQueryExtension(display, &event_base, &error_base, NULL, NULL)) {
//        std::cerr << "XTest extension not available!" << std::endl;
//        return;
//    }

    XWarpPointer(display, None, DefaultRootWindow(display), 0, 0, 0, 0, x, y);
    XFlush(display);

    XTestFakeButtonEvent(display, button, True, CurrentTime);
    XTestFakeButtonEvent(display, button, False, CurrentTime);
    XFlush(display);
}

void MouseClick(int button)
{
    Display *display = XOpenDisplay(NULL);

    XEvent event;

    if(display == NULL)
    {
        fprintf(stderr, "Errore nell'apertura del Display !!!\n");
        exit(EXIT_FAILURE);
    }

    memset(&event, 0x00, sizeof(event));

    event.type = ButtonPress;
    event.xbutton.button = button;
    event.xbutton.same_screen = True;


    XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

    event.xbutton.subwindow = event.xbutton.window;

    while(event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;

        XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

    if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Error\n");

    XFlush(display);

    usleep(100000);

    event.type = ButtonRelease;
    event.xbutton.state = 0x100;

    if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Error\n");

    XFlush(display);

    XCloseDisplay(display);
}