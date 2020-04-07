#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <gtk/gtk.h>

void gradientDescent();

typedef struct _Point{
	double x;
	double y;
} Point;

Point *lst_point;
int m = 1;
int nb_point_lastdraw = 1;
double coeffa;
double coeffb;
GtkDrawingArea * drawing_area;


void _on_destroy_main_window(GtkButton *button, gpointer user_data){
	gtk_main_quit();
}

void _on_spin_value_changed(GtkSpinButton *spin_button, gpointer user_data){
	m =  gtk_spin_button_get_value_as_int (spin_button);
}

void _on_calculate_clicked(GtkButton *button, gpointer user_data){
	nb_point_lastdraw = m;
	gradientDescent();
	gtk_widget_queue_draw((GtkWidget*)drawing_area);
}

double function(double a,double b, double x){
	return a*x+b;
}

gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data){
	guint width, height;
	GtkStyleContext *context;
	context = gtk_widget_get_style_context (widget);
	width = gtk_widget_get_allocated_width (widget);
	height = gtk_widget_get_allocated_height (widget);
	gtk_render_background(context, cr, 0, 0, width, height);
	cairo_set_line_width (cr, 2.0);
	cairo_set_source_rgba (cr, 0, 0, 0.5, 1);
	cairo_move_to(cr,0.0, height - function(coeffa,coeffb*MIN(width, height),0));
	cairo_line_to(cr,width, height - function(coeffa,coeffb*MIN(width, height),width));
	cairo_stroke(cr);

	if (lst_point){
		for(int i = 0 ; i < nb_point_lastdraw ; i++){
			cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
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

double model(double x){
	return 2*x +3;
}

double carre(double number){
	return number*number;
}

double gradientA(double a, double b, double (*model)(double), double m, Point * lst_point){
	double somme = 0;
	for (int i = 0; i < m; i++){
		somme +=  lst_point[i].x * (a * lst_point[i].x + b - lst_point[i].y);
	}
	return (1/m)*somme;
}

double gradientB(double a, double b, double (*model)(double), double m, Point * lst_point){
	double somme = 0;
	for (int i = 0; i < m; i++){
		somme +=  (a * lst_point[i].x + b - lst_point[i].y);
	}
	return (1/m)*somme;
}

void gradientDescent(){
	lst_point = realloc(lst_point, m * sizeof(Point));
	for (int i = 0; i < m; i++){
		Point p;
		p.x =  rand()/(double)RAND_MAX;
		p.y =  rand()/(double)RAND_MAX;
		lst_point[i] = p;
	}
	double a = rand()/(double)RAND_MAX;
	double b = rand()/(double)RAND_MAX;
	double learningRate = 0.001;
	double epsilon = 0.5;
	int k = 0;
	double diff = 1;
	double olda;
	double oldb;
	while(fabs(olda-a) != 0 && fabs(oldb-b) != 0){
		olda = a;
		oldb = b;
		a = a - learningRate * gradientA(a,b,model,m,lst_point);
		b = b - learningRate * gradientB(a,b,model,m,lst_point);
	}
	coeffa = a; 
	coeffb = b;
}

int main(int argc, char* argv[]){

	srand(time(0));
	GtkBuilder *builder;
	GtkWidget *window;
	// constructing window
	gtk_init(&argc, &argv);
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "../glade/gradient_descent.glade", NULL);
	window = GTK_WIDGET(gtk_builder_get_object(builder, "gradient_descent"));
	gtk_builder_connect_signals(builder, NULL);
	// GObjects
	GtkSpinButton * btn_spin = (GtkSpinButton*) gtk_builder_get_object(builder, "nb_selector");
	// Global GObjects
	drawing_area = (GtkDrawingArea*) gtk_builder_get_object(builder, "drawing_area");
	// signals
	g_signal_connect(btn_spin, "value-changed", G_CALLBACK(_on_spin_value_changed), NULL);
	g_signal_connect (G_OBJECT (drawing_area), "draw", G_CALLBACK (draw_callback), NULL);
	g_object_unref(builder);
	gtk_widget_show(window);
	gtk_main();

	if (lst_point){
		free(lst_point);
	}
	gtk_widget_destroy(window);

	return EXIT_SUCCESS;
}
