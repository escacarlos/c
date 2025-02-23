#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    gtk_init(); // No arguments needed in GTK 4

    GtkWidget *window = gtk_window_new(); // No arguments in GTK 4
    gtk_window_set_title(GTK_WINDOW(window), "Hello, GTK4!");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_destroy), NULL);

    //gtk_widget_set_visible(window, TRUE); // No more gtk_widget_show_all()
    gtk_window_present(GTK_WINDOW(window));

    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop); // Replaces gtk_main()

    return 0;
}
