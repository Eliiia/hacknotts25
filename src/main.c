#include <gtk-2.0/gtk/gtk.h>

int main(int argc, char* argv[]) {
	GtkWidget *window;
	GtkWidget *label;

	gtk_init (&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "L:A_N:application_PC:TS_ID:org.team_ate.kindle_balatro");
	gtk_widget_set_size_request(window, 632, 840);

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	label = gtk_label_new("Hello Kindle!");
	gtk_container_add(GTK_CONTAINER(window), label);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
