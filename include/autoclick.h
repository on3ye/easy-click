// @author: on3ye
// @date: 13-07-2024 09:00
// @title: Autoclicker Functionality Header File (autoclick.h)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <gtk/gtk.h>

// Include autoclick headers based on user's operating system
#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#elif defined(__APPLE__) || defined(__MACH__)
    #include <ApplicationServices/ApplicationServices.h>
#elif defined(__unix__) || defined(__linux__) 
    #include <X11/Xlib.h>
    #include <X11/extensions/XTest.h>
#endif

// Struct to hold GUI Widgets Instances
typedef struct {
    GtkWidget* w_click_type;
    GtkWidget* w_mouse_button;
    GtkWidget* w_click_interval;
    GtkWidget* w_repeat_mode;
    GtkWidget* w_num_clicks;
} WidgetsData;

void perform_click(Display* display, int button);           // Click function defined based on user's OS
static gboolean click_loop(gpointer data);                  // Main click loop (Used as GSourceFunc)
void start_autoclicker(GtkWidget *widget, gpointer data);   // Function to start the autoclicker
void stop_autoclicker(GtkWidget *widget, gpointer data);    // Function to stop the autoclicker
