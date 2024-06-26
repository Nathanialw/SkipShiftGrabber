#include <iostream>
#include "X11/Xlib.h"
#include "X11/Xutil.h"
#include "GetWindowID.h"
#include "MouseClick.h"
#include "vector"
#include "chrono"

void PushButton(Display *display, int x, int y) {
//    std::cout << "clicking" << std::endl;


    simulateMouseClick(display, 1, x, y);

//    sleep(1);
}

bool CheckPixdelWeston(char *hex, const std::string &green, int x, int y, int x2, int y2) {
    if (strcmp(hex, "#FAFAFA") == 0 || strcmp(hex, "#172026") == 0) {
        return true;
    }

    if (strcmp(hex, green.c_str()) == 0) {  //color code for use scrcpy when the screen is dimmed/unplugged
        Display *display = XOpenDisplay(0);
//        Window root = DefaultRootWindow(display);

        // Create an XEvent structure
        PushButton(display, (x + 50), y);

//        std::cout << "Found pixel: " << hex << ", " << x << " " << y << std::endl;
        XFlush(display);

        int i = 0;
        while (i < 15) {
            PushButton(display, (x2), y2);
            i++;
            usleep(50000);
        }


        XCloseDisplay(display);
        return true;
    }
    return false;
}

void RunBash(const std::string &x, const std::string &y, int x2, int y2) {
    //std::string filename = "select.sh";
//    std::string shell = "/home/nathanial/CLionProjects/untitled/select.sh";
//    auto value = shell + " " + x + " " + y;

    std::string shell = "/home/nathanial/Workspace/SkipShiftGrabber/select.sh";

    //for weston


    //for screen share
//    x2 += rand() % 2 - 1;
//    y2 += rand() %  2 - 1;
//    std::cout << x2 << std::endl;
//    std::cout << y2 << std::endl;


    auto value = shell + " " + x + " " + y + " " + std::to_string(x2) + " " + std::to_string(y2);
    std::system(value.c_str());

    /* IN THE BASH SCRIPT
     *
     *  SPATH=$1
        DPATH=$2
        FILE=$3
        cp ${SPATH}/${FILE} ${DPATH}/${FILE}
     */
}

bool CheckPixdel(char *hex, const std::string &green, int x, int y, int x2, int y2) {
    if (strcmp(hex, "#FAFAFA") == 0) {
        return true;
    }

    if (strcmp(hex, green.c_str()) == 0) {  //color code for use scrcpy when the screen is dimmed/unplugged
        // Create an XEvent structure
        RunBash(std::to_string(x + 50), std::to_string(y), x2, y2);
        std::cout << "Found pixel: " << hex << ", " << x << " " << y << std::endl;
        return true;
    }
    return false;
}


char*  getpixelcol(Window win, int x, int y) {
    XColor c;
    Display *d = XOpenDisplay((char *) NULL);
    if (d == NULL) {
    }

    XImage *image;

    // Get the pixel color
    // I want to get it from the Weston Compositor window instead of the root window

    image = XGetImage(d, XRootWindow(d, XDefaultScreen(d)), x, y, 1, 1, AllPlanes, XYPixmap);
    XRootWindow(d, XDefaultScreen(d));
//    image = XGetImage(d, win, x, y, 1, 1, AllPlanes, XYPixmap);
    if (image == NULL) {
        std::cout << "Error getting image" << std::endl;
        XCloseDisplay(d);
    }

    c.pixel = XGetPixel(image, 0, 0);
    XFree(image);
    XQueryColor(d, XDefaultColormap(d, XDefaultScreen(d)), &c);
    XCloseDisplay(d);

    // print colour of pixel in format #rrggbb
    // printf("#%06X\n", c.pixel);
    // fflush(stdout);

    char *hex;
    asprintf(&hex, "#%06X", (unsigned int)c.pixel);

//    std::cout << hex << std::endl;

//    for (auto &c : color) {
//        if (CheckPixdel(hex, c, x, y, x2, y2)) {fflush(stdout); return true;};
//    }

    fflush(stdout);
    return hex;
//    return false;
}

bool checkColor(int x, int y, int x2, int y2, char *hex, const std::vector<std::string> &color, bool share) {
    if (!share) {
        for (auto &c : color) {
            if (CheckPixdelWeston(hex, c, x, y, x2, y2)) {return true;};
        }
    }
    else {
        for (auto &c : color) {
//            if (CheckPixdel(hex, c, x, y, x2, y2)) {return true;};
            if (CheckPixdelWeston(hex, c, x, y, x2, y2)) {return true;};
        }
    }
    return false;
}

int main() {
    int i = 0;
    auto win = GetWindowID();
    std::vector<std::string> share = {"#1CD478", "#1CD479", "#1DD478", "#1DD479", "#1FD27C", "#1ED378"};
    std::vector<std::string> weston = {"#1DD377", "#1BC670"}; //weston
    std::vector<std::string> westonSpinner = {"#FAFAFA"}; //weston
    std::vector<std::string> spinner = {"#FAFAFA"};
    // check if the spinner color is on

    int active = 1;
    int activeChecks = 20;
    bool bShare = false;
//    bool bShare = true;

//    auto t = std::chrono::system_clock::now();
//    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t.time_since_epoch()).count();

    int count = abs(rand() % 8 - 58);
    if (!bShare) {
        if (count == 0) {
        }
    }

    while (i < 100000000) {
        if (!bShare && count == 0) {
            count = abs(rand() % 35 - 8);
            for (int j = 0; j < 5; j++) {
                int longms = abs(rand() % 200 - 100) ;
                std::string shell = "/home/nathanial/Workspace/SkipShiftGrabber/swipe.sh";
                std::system(shell.c_str());
                sleep(longms);
//                std::cout << longms << std::endl;
            }
//            std::cout << count << std::endl;
        }

        if (active == 0) {
            count--;
            if (!bShare) {
//                auto timerType = rand() % 3;
                auto timerType = 0;
                int ms;
                if (timerType == 0) {
                    ms = abs(rand() %  2000000 - 1000000);
//                    std::cout << ms << std::endl;
                }
                    //                else if (timerType == 1) {
//                    ms = rand() % 1000000 - 3000000;
//                } else if (timerType == 2) {
//                    ms = rand() % 1000000 - 4000000;
//                } else if (timerType == 3) {
//                    ms = rand() % 1000000 - 5000000;
//                }
                //make int positive
//                std::cout << ms << std::endl;
                if (ms < 0) {
                    ms = ms * -1;
                }
                usleep(ms);
                std::string shell = "/home/nathanial/Workspace/SkipShiftGrabber/swipe.sh";
                std::system(shell.c_str());

                usleep(200000);
                auto hex = getpixelcol(win, 1970, 220);
//                std::cout << hex << std::endl;
                if (checkColor(1970, 220, 0, 0, hex, westonSpinner, bShare)) {
                    active = activeChecks;
                }
            }

            else {
                usleep(500000);
                auto hex = getpixelcol(win, 1883, 272);
                if (checkColor(1883, 272, 0, 0, hex, spinner, bShare)) {
                    active = activeChecks;
                }
            }
        }

        if (bShare)
        {
            if (active > 0) {
                int openshiftx = 1560;// Pixel x
                int openshifty = 385; // Pixel y
                int confirmx = 1795; // Pixel y
                int confirmy = 1352; // Pixel y
                int spinnerx = 1883;
                int spinnery = 272;

                while (openshifty < 1355) {
                    auto hex = getpixelcol(win, openshiftx, openshifty);
                    if (checkColor(openshiftx, openshifty, confirmx, confirmy, hex, share, bShare)) {
                        break;
                    };
                    openshifty += 145;
                }
                auto hex = getpixelcol(win, spinnerx, spinnery);
                if (checkColor(spinnerx, spinnery, 0, 0, hex, spinner, bShare)) {
                    active = activeChecks;
                }
                active--;
            }
        }
        else {
            if (active > 0) {
                // framework click placement
                int openshiftx = 1697;// Pixel x
                int openshifty = 260; // Pixel y
                int confirmx = 1905; // Pixel y
                int confirmy = 1424; // Pixel y
                int spinnerx = 1977;
                int spinnery = 231;
                int closex = 1728;
                int closey = 155;

                while (openshifty < 1400) {
                    auto hex = getpixelcol(win, openshiftx, openshifty);
                    if (strcmp(hex, "#263540") == 1) {
                    }

                    if (checkColor(openshiftx, openshifty, confirmx, confirmy, hex, weston, bShare)) {
                        usleep(1500000);
                        auto hex2 = getpixelcol(win, closex, closey);
                        if (checkColor(closex, closey, 0, 0, hex2, weston, bShare)) {
                            std::cout << hex2 << std::endl;
                            std::cout << "shift already taken" << std::endl;
                            Display *display = XOpenDisplay(0);
                            PushButton(display, 2017, 400);
                            usleep(500000);
                            PushButton(display, closex, closey);
                            XFlush(display);
                            XCloseDisplay(display);
                        }
                        else {
                            std::cout << hex2 << std::endl;
                            std::cout << "shift grabbed" << std::endl;
                        }
                        active = 0;
                        break;
                    };
                    openshifty += 100;
                }
                auto hex = getpixelcol(win, spinnerx, spinnery);
                if (checkColor(spinnerx, spinnery, 0, 0, hex, spinner, bShare)) {
                    active = activeChecks;
                }
                active--;
            }
        }
        if (active < 1)
            active = 0;
        i++;

    }

    std::cout << "done!";
}

// Get the pixel color
