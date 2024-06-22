#include <X11/Xlib.h>
#include <string.h>

Window GetWindowID() {
    Display *d;
    Window root, parent, *children;
    unsigned int num_children;

    // Connect to the X server
    d = XOpenDisplay(NULL);
    if (d == NULL) {
        // Handle error
        std::cout << "Failed to connect to X server" << std::endl;
        return 0;
    }

    // Get the root window
    root = XDefaultRootWindow(d);

    // Get the list of child windows
    XQueryTree(d, root, &root, &parent, &children, &num_children);

    // Iterate through the child windows to find the Weston Compositor window
    Window weston_compositor_window = 0;

    for (unsigned int i = 0; i < num_children; i++) {
        char *window_name = NULL;
        XFetchName(d, children[i], &window_name);
//        if (window_name != NULL) {
//            std::cout << window_name << std::endl;
//        }

        // Check if the window name matches the Weston Compositor window
        if (window_name != NULL && strcmp(window_name, "Terminal") == 0) {

            Window root0, parent0, *children0;
            root0 = children[i];
            unsigned int num_children0;
            XQueryTree(d, root0, &root0, &parent0, &children0, &num_children0);

            // Iterate through the child windows to find the Weston Compositor window
            for (unsigned int j = 0; j < num_children0; j++) {
                char *window_name0 = NULL;
                XFetchName(d, children0[j], &window_name0);
                if (window_name0 != NULL) {
                    std::cout << window_name0 << std::endl;
                }

                // Check if the window name matches the Weston Compositor window
                if (window_name0 != NULL && strcmp(window_name0, "Weston Compositor - screen0") == 0) {
                    weston_compositor_window = children0[j];
                    break;
                }

                XFree(window_name0);
            }
        }
//        if (window_name != NULL && strcmp(window_name, "Weston Compositor - screen0") == 0) {
//            weston_compositor_window = children[i];
//            break;
//        }

        XFree(window_name);
    }

    // Clean up
    XFree(children);
    XCloseDisplay(d);

    // Use the weston_compositor_window to get the pixel color
    //std::cout << weston_compositor_window << std::endl;
    return weston_compositor_window;
}