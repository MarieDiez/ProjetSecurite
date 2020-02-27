#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <time.h>

int incrementeCptInCircle(int cpt, double x, double y);

def struct _Point{
	double x;
	double y;
	int inner;
}

int nb_point;



// GTK callback

void _on_destroy_main_window(GtkButton *button, gpointer user_data){
    gtk_main_quit();
}

void _on_spin_value_changed(GtkSpinButton *spin_button, gpointer user_data){
	nb_point =  gtk_spin_button_get_value_as_int (spin_button);
}

void _on_calculate_clicked(GtkButton *button, gpointer user_data){
	printf("%d\n",42);
}

gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data){

	guint width, height;
	
	GtkStyleContext *context;
	context = gtk_widget_get_style_context (widget);
	
	width = gtk_widget_get_allocated_width (widget);
	height = gtk_widget_get_allocated_height (widget);
	
	gtk_render_background(context, cr, 0, 0, width, height);
	
	
	// drawing arc
	cairo_set_line_width (cr, 2.0);
	cairo_arc(
		cr,
	  	0,						// x
	  	height,					// y
		MIN (width, height),	// rayon
		0,						// angle1
		2 * G_PI				// angle2
	);
	cairo_stroke(cr);
	
	cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
	

  	cairo_fill (cr);

 return FALSE;
}

// calcule

void call_monte_carlo(){


	int cpt = 0;

	
	for (int i=0; i<nb_point; i++){
		x =  rand()/(double)RAND_MAX;
		y =  rand()/(double)RAND_MAX;

		cpt = incrementeCptInCircle(cpt, x, y);

	}
	printf("%s %.7f\n", "pi = ",((double)cpt*4)/nb_point);
}

int incrementeCptInCircle(int cpt, double x, double y){
	if (x*x + y*y <= 1)
		cpt++;
	return cpt;
}

/*
 * Main
 */

int main(int argc, char* argv[]){

	srand(time(0));

	GtkBuilder *builder;
    GtkWidget *window;

	// constructing window
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "../monte_carlo.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "monte_carlo"));
    gtk_builder_connect_signals(builder, NULL);
	
	//GObjects
    GtkSpinButton * btn_spin = (GtkSpinButton*) gtk_builder_get_object(builder, "nb_selector");
    GtkDrawingArea * drawing_area = (GtkDrawingArea*) gtk_builder_get_object(builder, "drawing_area");
    
    //signals
    g_signal_connect(btn_spin, "value-changed", G_CALLBACK(_on_spin_value_changed), NULL);
	g_signal_connect (G_OBJECT (drawing_area), "draw", G_CALLBACK (draw_callback), NULL);
	
	// - - - 
    g_object_unref(builder);
    gtk_widget_show(window);                
    gtk_main();
    
	return EXIT_SUCCESS;
} 


