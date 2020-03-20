#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

void on_destroy_main_window(GtkButton *button, gpointer user_data){
    gtk_main_quit();
}

void on_btn_next_clicked(GtkButton *button, gpointer user_data){
    printf("clicked next\n");
}

void on_btn_prev_clicked(GtkButton *button, gpointer user_data){
    printf("clicked previous\n");
}

int main(int argc, char *argv[]){
    GtkBuilder *builder;
    GtkWidget *window;
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "../media_player.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "media_player"));
    gtk_builder_connect_signals(builder, NULL);
	g_object_unref(builder);
	gtk_widget_show(window);
	gtk_main();

    return 0;
}




