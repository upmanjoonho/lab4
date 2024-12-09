#include <gtk/gtk.h>

void input_completed(GtkWidget *entry, gpointer data) {
    const char *text = gtk_entry_get_text(GTK_ENTRY(entry));
    g_print("텍스트: %s\n", text);
}

int main(int argc, char *argv[]) {
    GtkWidget *window, *vbox, *label, *entry, *button;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Login");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 100);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    label = gtk_label_new("Password:");
    entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry), FALSE);

    button = gtk_button_new_with_label("Submit");
    g_signal_connect(button, "clicked", G_CALLBACK(input_completed), entry);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 5);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
