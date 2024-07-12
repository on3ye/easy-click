// @author: on3ye (on3ye@proton.me)
// @date: 11-07-2024 13:00
// @title: Program's Entry Point (main.c)

#include <gtk/gtk.h>
#include "activate.h"

static void shutdown(GtkApplication* app, gpointer user_data) {
    printf("Application Closed!\n");
}

int main(int argc, char** argv) {
    int status_code;        // Returned Exit Code
    GtkApplication* app;    // Application Instance

    app = gtk_application_new("net.on3ye.easy_click", G_APPLICATION_FLAGS_NONE);    // GtkApp Creation (flags=NONE)
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);                  // Connect "activate" signal to main app
    g_signal_connect(app, "shutdown", G_CALLBACK(shutdown), NULL);                  // Connect "shutdown" signal to main app
    status_code = g_application_run(G_APPLICATION(app), argc, argv);                // Run application, set exit status
    g_object_unref(app);                                                            // Finalize the app object and free its memory

    return status_code;
}
