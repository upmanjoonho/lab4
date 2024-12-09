#include <gtk/gtk.h>

GtkWidget *entry;

void on_button_clicked(GtkWidget *widget, gpointer data) {
    const gchar *current_text = gtk_entry_get_text(GTK_ENTRY(entry));
    const gchar *button_label = (gchar *)data;
    gchar *new_text = g_strdup_printf("%s%s", current_text, button_label);
    gtk_entry_set_text(GTK_ENTRY(entry), new_text);
    g_free(new_text);
}

void on_calculate_clicked(GtkWidget *widget, gpointer data) {
    const gchar *expression = gtk_entry_get_text(GTK_ENTRY(entry));
    double result = 0.0;
    result = g_ascii_strtod(expression, NULL);
    gchar *result_text = g_strdup_printf("%f", result);
    gtk_entry_set_text(GTK_ENTRY(entry), result_text);
    g_free(result_text);
}

int main(int argc, char *argv[]) {
    GtkWidget *window, *grid, *button;
    const gchar *labels[] = {"7", "8", "9", "4", "5", "6", "1", "2", "3", "0", "+", "-", "*", "/", "=", "C"};

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK+ Calculator");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 4, 1);

    for (int i = 0; i < 16; i++) {
        button = gtk_button_new_with_label(labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 4, 1 + i / 4, 1, 1);

        if (g_strcmp0(labels[i], "=") == 0) {
            g_signal_connect(button, "clicked", G_CALLBACK(on_calculate_clicked), NULL);
        } else if (g_strcmp0(labels[i], "C") == 0) {
            g_signal_connect(button, "clicked", G_CALLBACK(gtk_entry_set_text), entry);
        } else {
            g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), (gpointer)labels[i]);
        }
    }

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
