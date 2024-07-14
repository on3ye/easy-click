#include "gui.h"

// Function to create and return a combo box with provided options
GtkWidget* create_combo_box_with_options(const char* options[], int options_count, int active_index) {
    GtkWidget* combo_box = gtk_combo_box_text_new();
    for (int i = 0; i < options_count; i++) 
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), options[i]);
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box), active_index);
    return combo_box;
}

// Function to create a spin button with specified adjustment properties
GtkWidget* create_spin_button(double initial, double min, double max, double step) {
    GtkAdjustment* adjustment = gtk_adjustment_new(initial, min, max, step, 0.0, 0.0);
    GtkWidget* spin_button = gtk_spin_button_new(adjustment, 1.0, (guint)0);
    return spin_button;
}

// Function to create two labeled buttons and put them in a horizontal box
GtkWidget* create_two_labeled_buttons(const char* label1, const char* label2) {
    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget* first_button = gtk_button_new_with_label(label1);
    GtkWidget* second_button = gtk_button_new_with_label(label2);
    gtk_widget_set_size_request(first_button, 175, 10);
    gtk_widget_set_size_request(second_button, 175, 10);
    gtk_box_append(GTK_BOX(box), first_button);
    gtk_box_append(GTK_BOX(box), second_button);
    return box;
}

// Main function to render widgets in the window
void render_widgets(GtkWindow* window) {
    // Create main box for vertical layout
    GtkWidget* main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(window, main_box);
    gtk_widget_set_margin_top(main_box, 10);
    gtk_widget_set_margin_bottom(main_box, 10);
    gtk_widget_set_margin_start(main_box, 20);
    gtk_widget_set_margin_end(main_box, 20);

    // Click type combo box
    const char* click_types[] = { "Single Click", "Double Click" };
    GtkWidget* click_type_label = gtk_label_new("Click Type:");
    GtkWidget* click_type_combo = create_combo_box_with_options(click_types, 2, 0);
    gtk_box_append(GTK_BOX(main_box), click_type_label);
    gtk_box_append(GTK_BOX(main_box), click_type_combo);

    // Mouse button combo box
    const char* mouse_buttons[] = { "Left Button", "Right Button", "Both (Left & Right Buttons)" };
    GtkWidget* mouse_button_label = gtk_label_new("Mouse Button:");
    GtkWidget* mouse_button_combo = create_combo_box_with_options(mouse_buttons, 3, 0);
    gtk_box_append(GTK_BOX(main_box), mouse_button_label);
    gtk_box_append(GTK_BOX(main_box), mouse_button_combo);

    // Click interval spin button
    GtkWidget* click_interval_label = gtk_label_new("Click Interval (ms):");
    GtkWidget* click_interval_box = create_spin_button(100.0, 10.0, 10000.0, 10.0);
    gtk_box_append(GTK_BOX(main_box), click_interval_label);
    gtk_box_append(GTK_BOX(main_box), click_interval_box);

    // Repeat options combo box and number of clicks spin button
    const char* repeat_modes[] = { "Fixed Number of Clicks", "Until Stopped" };
    GtkWidget* repeat_mode_label = gtk_label_new("Repeat Options:");
    GtkWidget* repeat_mode_combo = create_combo_box_with_options(repeat_modes, 2, 1);
    GtkWidget* number_of_clicks_box = create_spin_button(30.0, 1.0, 100000.0, 1.0);
    gtk_widget_set_sensitive(number_of_clicks_box, FALSE);
    g_signal_connect(repeat_mode_combo, "changed", G_CALLBACK(repeat_mode_combo_changed), number_of_clicks_box);
    gtk_box_append(GTK_BOX(main_box), repeat_mode_label);
    gtk_box_append(GTK_BOX(main_box), repeat_mode_combo);
    gtk_box_append(GTK_BOX(main_box), number_of_clicks_box);

    // Buttons
    GtkWidget* buttons_label = gtk_label_new("Control Buttons / Misc:");
    GtkWidget* control_buttons = create_two_labeled_buttons("Start", "Stop");
    GtkWidget* hotkeys_help_buttons = create_two_labeled_buttons("Start/Stop Hotkeys", "Need help?");
    gtk_box_append(GTK_BOX(main_box), buttons_label);
    gtk_box_append(GTK_BOX(main_box), control_buttons);
    gtk_box_append(GTK_BOX(main_box), hotkeys_help_buttons);
}
