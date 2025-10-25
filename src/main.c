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

	GtkWidget *layout_box = gtk_vbox_new(TRUE, 0);
	GtkWidget *top_box = gtk_hbox_new(TRUE, 0);
	GtkWidget *card_box = gtk_vbox_new(TRUE, 0);
	GtkWidget *card_row1_box = gtk_hbox_new(TRUE, 0);
	GtkWidget *card_row2_box = gtk_hbox_new(TRUE, 0);
	GtkWidget *button_box = gtk_hbox_new(TRUE, 0);
	GtkWidget *score_box = gtk_vbox_new(TRUE, 0);
	GtkWidget *hand_ante_box = gtk_vbox_new(TRUE, 0);
	GtkWidget *discard_round_box = gtk_vbox_new(TRUE, 0);

	gtk_box_pack_start_defaults(GTK_BOX(layout_box), top_box);
	gtk_box_pack_start_defaults(GTK_BOX(layout_box), card_box);
	gtk_box_pack_start_defaults(GTK_BOX(layout_box), button_box);
	gtk_box_pack_start_defaults(GTK_BOX(top_box), score_box);
	gtk_box_pack_start_defaults(GTK_BOX(top_box), hand_ante_box);
	gtk_box_pack_start_defaults(GTK_BOX(top_box), discard_round_box);
	gtk_box_pack_start_defaults(GTK_BOX(card_box), card_row1_box);
	gtk_box_pack_start_defaults(GTK_BOX(card_box), card_row2_box);

	GtkWidget* small_blind_label = gtk_label_new("Small Blind");
	GtkWidget* score_label = gtk_label_new("Score:");
	GtkWidget* score_count_label = gtk_label_new("300");
	GtkWidget* chip_mult_label = gtk_label_new("0 x 0");
	GtkWidget* hands_label = gtk_label_new("5 hands");
	GtkWidget* ante_label = gtk_label_new("Ante 1/8");
	GtkWidget* discards_label = gtk_label_new("3 discards");
	GtkWidget* rounds_label = gtk_label_new("Round 1");

	GtkWidget* play_button = gtk_button_new_with_label("Play Hand");
	GtkWidget* discard_button = gtk_button_new_with_label("Discard Hand");

	gtk_box_pack_start_defaults(GTK_BOX(score_box), small_blind_label);
	gtk_box_pack_start_defaults(GTK_BOX(score_box), score_label);
	gtk_box_pack_start_defaults(GTK_BOX(score_box), score_count_label);
	gtk_box_pack_start_defaults(GTK_BOX(score_box), chip_mult_label);
	gtk_box_pack_start_defaults(GTK_BOX(hand_ante_box), hands_label);
	gtk_box_pack_start_defaults(GTK_BOX(hand_ante_box), ante_label);
	gtk_box_pack_start_defaults(GTK_BOX(discard_round_box), discards_label);
	gtk_box_pack_start_defaults(GTK_BOX(discard_round_box), rounds_label);
	gtk_box_pack_start_defaults(GTK_BOX(button_box), play_button);
	gtk_box_pack_start_defaults(GTK_BOX(button_box), discard_button);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
