#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <time.h>

int incrementeCptInCircle(int index, int cpt);
void call_monte_carlo();

typedef struct _Point{
	double x;
	double y;
	int inner;
} Point;

Point *lst_point;
int nb_point = 1;
int nb_point_lastdraw = 1;

// Global GTK Object
GtkDrawingArea * drawing_area;

// GTK callback

void _on_destroy_main_window(GtkButton *button, gpointer user_data){
	gtk_main_quit();
}

void _on_spin_value_changed(GtkSpinButton *spin_button, gpointer user_data){
	nb_point =  gtk_spin_button_get_value_as_int (spin_button);
}

void _on_calculate_clicked(GtkButton *button, gpointer user_data){
	nb_point_lastdraw = nb_point;
	call_monte_carlo();
	gtk_widget_queue_draw((GtkWidget*)drawing_area);
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
			G_PI/2,					// angle1
			0						// angle2
		 );
	cairo_stroke(cr);

	cairo_set_line_width (cr, 1.0);
	if (lst_point){
		for(int i = 0 ; i < nb_point_lastdraw ; i++){
			if (lst_point[i].inner) {
				cairo_set_source_rgba (cr, 0.2, 0.2, 1, 0.6);
			}else{
				cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
			}
			cairo_arc(
					cr,
					lst_point[i].x * MIN(width, height),
					height - lst_point[i].y * MIN(width, height),
					2,
					0,
					2 * G_PI
				 );
			cairo_fill (cr);
		}
	}
	return FALSE;
}

// calcule

void call_monte_carlo(){
	int cpt = 0;

	lst_point = realloc(lst_point, nb_point * sizeof(Point) + sizeof(void*));
	if (lst_point){
		for (int i=0; i<nb_point; i++){
			Point p;
			p.x =  rand()/(double)RAND_MAX;
			p.y =  rand()/(double)RAND_MAX;
			p.inner = 0;

			if (p.x*p.x + p.y*p.y <= 1){
				cpt++;
				p.inner = 1;
			}
			lst_point[i] = p;
		}
		printf("%s %.7f\n", "pi = ",((double)cpt*4)/nb_point);
	}
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
	gtk_builder_add_from_file(builder, "../glade/monte_carlo.glade", NULL);
	window = GTK_WIDGET(gtk_builder_get_object(builder, "monte_carlo"));
	gtk_builder_connect_signals(builder, NULL);

	// GObjects
	GtkSpinButton * btn_spin = (GtkSpinButton*) gtk_builder_get_object(builder, "nb_selector");
	// Global GObjects
	drawing_area = (GtkDrawingArea*) gtk_builder_get_object(builder, "drawing_area");

	// signals
	g_signal_connect(btn_spin, "value-changed", G_CALLBACK(_on_spin_value_changed), NULL);
	g_signal_connect(G_OBJECT (drawing_area), "draw", G_CALLBACK (draw_callback), NULL);

	// - - -
	g_object_unref(builder);
	gtk_widget_show(window);
	gtk_main();
	if(lst_point){
		free(lst_point);
	}
	return EXIT_SUCCESS;
} 


