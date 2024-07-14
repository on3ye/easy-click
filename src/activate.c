// @author: on3ye
// @date: 11-07-2024 14:00
// @title: Main Activation Callback Logic (activate.c)

#include "activate.h"
#include "gui.h"

void activate(GtkApplication* app, gpointer user_data) {
    // Window's Title: "Easy Click v(*Version*)"
    const char* TITLE = "Easy Click v0.1";

    // Window's Geometry: Width & Height
    const int WIDTH = 400;
    const int HEIGHT = 410;

    // Window's Resizable Option
    const gboolean RESIZABLE = FALSE;

    // Create new application window widget (Cast it to a GtkWindow* type)
    GtkWidget* w_Window = gtk_application_window_new(app);
    GtkWindow* window = GTK_WINDOW(w_Window);
    printf("Initialized new application window!\n"); // [DEBUG INFO]

    // Configure some window's properties
    gtk_window_set_title(window, TITLE);
    gtk_window_set_default_size(window, WIDTH, HEIGHT);
    gtk_window_set_resizable(window, RESIZABLE);
    printf(
        "Configured window:\n\t- Title: %s\n\t- Geometry: %dx%d\n\t- Resizable: %s\n",
        gtk_window_get_title(window), WIDTH, HEIGHT, (gtk_window_get_resizable(window) == FALSE) ? "FALSE" : "TRUE"
    ); // [DEBUG INFO]

    gtk_window_present(window);
    printf("GtkWindow created successfully!\n"); // [DEBUG INFO]

    // Render all widgets at the main window
    render_widgets(window);
}
