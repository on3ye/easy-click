#include "signals.h"

void repeat_mode_combo_changed(GtkWidget* repeat_mode_combo, GtkWidget* number_of_clicks_box) { 
    const char* repeat_until_stopped_option = "Until Stopped";
    char* active_text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(repeat_mode_combo));
    gboolean field_sensitivity = (strcmp(active_text, repeat_until_stopped_option) == 0) ? FALSE : TRUE;
    gtk_widget_set_sensitive(number_of_clicks_box, field_sensitivity);
    g_free(active_text);
}
