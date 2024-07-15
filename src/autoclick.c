// @author: on3ye
// @date: 13-07-2024 09:30
// @title: Autoclicker Functionality Logic (depends on user's OS) (autoclick.c)

#include "autoclick.h"

// Define the perform_click function based on user's operating system (WIN/APPLE/UNIX)
#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    void perform_click(int button) {

        return ;
    }
#elif defined(__APPLE__) || defined(__MACH__)
    #include <ApplicationServices/ApplicationServices.h>
    void perform_click(int button) {

        return ;
    }
#elif defined(__unix__) || defined(__linux__) 
    void perform_click(Display* display, int button) {
        if (display == NULL) return;    
        XTestFakeButtonEvent(display, button == 0 ? 1 : button == 1 ? 3 : 2, True, CurrentTime);
        XFlush(display);
        XTestFakeButtonEvent(display, button == 0 ? 1 : button == 1 ? 3 : 2, False, CurrentTime);
        XFlush(display);
    }
#endif

// Struct to hold useful data about the Autoclicker
typedef struct {
    Display* display;
    bool running;
    int click_count;
    int click_type;
    int button;
    int click_interval;
    int repeat_mode;
    int num_clicks;
} ClickerData;

ClickerData clicker_data;

// Main click loop (ClickerData -> Autoclick Functionality)
static gboolean click_loop(gpointer data) {
    // Break the click loop, based on some conditions provided by clicker_data
    if (!clicker_data.running || (!clicker_data.repeat_mode && clicker_data.click_count >= clicker_data.num_clicks)) {
        XCloseDisplay(clicker_data.display);
        clicker_data.running = false;
        g_print("[-] Autoclicker stopped after %d clicks!\n", clicker_data.click_count); // [DEBUG INFO]
        return G_SOURCE_REMOVE;
    }
    
    // Perform 1 or 2 clicks (based on clicker_data). Then, increase the click_count
    perform_click(clicker_data.display, clicker_data.button);
    if (clicker_data.click_type) perform_click(clicker_data.display, clicker_data.button);
    clicker_data.click_count += clicker_data.click_type + 1;

    return G_SOURCE_CONTINUE; // Continue Calling the function
}

// Function to start the autoclicker (fetch data from GUI)
void start_autoclicker(GtkWidget *widget, gpointer data) {
    if (clicker_data.running) return;           // If the autoclicker is already running, quit from the function
    clicker_data.running = true;                // Set the running state to True
    clicker_data.click_count = 0;               // Reset the click counter
    WidgetsData* widgets = (WidgetsData *)data; // Cast the data to WidgetsData*
    clicker_data.display = XOpenDisplay(NULL);  // Establish a connection to X server, to use Display functionalities

    // Exit in case the display is NULL
    if (clicker_data.display == NULL) {
        g_printerr("[-] Could not open display!\n"); // [DEBUG INFO]
        return;
    }

    // Retrieving ClickerData from GUI 
    char* gui_click_type = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widgets->w_click_type));
    char* gui_mouse_button = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widgets->w_mouse_button));
    double gui_click_interval = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widgets->w_click_interval));
    char* gui_repeat_mode = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widgets->w_repeat_mode));
    double gui_num_click = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widgets->w_num_clicks));

    // Set clicker_data options based on the retrieved data
    clicker_data.click_type = !strcmp(gui_click_type, "Single Click") ? 0 : 1;
    clicker_data.button = !strcmp(gui_mouse_button, "Left Button") ? 0 : !strcmp(gui_mouse_button, "Right Button") ? 1 : 2;
    clicker_data.click_interval = (int)gui_click_interval;
    clicker_data.repeat_mode = !strcmp(gui_repeat_mode, "Fixed Number of Clicks") ? 0 : 1;
    clicker_data.num_clicks = (int)gui_num_click;
    
    g_print("[+] Started Autoclicker:\n\t- ClickType = %i\n\t- MouseButton = %i\n\t- ClickInterval(ms) = %i\n\t- RepeatMode = %i\n\t- Number of Clicks: %i\n", 
        clicker_data.click_type,
        clicker_data.button,
        clicker_data.click_interval,
        clicker_data.repeat_mode,
        clicker_data.num_clicks
    ); // [DEBUG INFO]

    // Run the click_loop at regular intervals
    g_timeout_add(clicker_data.click_interval, click_loop, NULL);
    g_print("[+] Successfully run the click_loop!\n"); // [DEBUG INFO]
}

// Stop the autoclicker by setting the running state to False 
void stop_autoclicker(GtkWidget *widget, gpointer data) {
    clicker_data.running = false;
}
