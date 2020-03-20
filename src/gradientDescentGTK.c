#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <gtk/gtk.h>

/* y =ax +b */
typedef struct _Point{
	double x;
	double y;
	int inner;
} Point;


void _on_destroy_main_window(GtkButton *button, gpointer user_data){
	gtk_main_quit();
}

void _on_calculate_clicked(GtkButton *button, gpointer user_data){
	nb_point_lastdraw = nb_point;
	gradientDescent();
}

gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data){

	guint width, height;
	
	GtkStyleContext *context;
	context = gtk_widget_get_style_context (widget);
	
	width = gtk_widget_get_allocated_width (widget);
	height = gtk_widget_get_allocated_height (widget);
	
	gtk_render_background(context, cr, 0, 0, width, height);

	cairo_set_line_width (cr, 1.0);
		if (lst_point){
			for(int i = 0 ; i < nb_point_lastdraw ; i++){

				cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
				
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
		//somme +=  model(lst_point[i].x) * (a * model(lst_point[i].x) + b - lst_point[i].y);
		somme +=  lst_point[i].x * (a * lst_point[i].x + b - lst_point[i].y);
	}
	return (1/m)*somme;
}

double gradientB(double a, double b, double (*model)(double), double m, Point * lst_point){
	double somme = 0;
	for (int i = 0; i < m; i++){
		//somme +=  (a * model(lst_point[i].x) + b - lst_point[i].y);
		somme +=  (a * lst_point[i].x + b - lst_point[i].y);
	}
	return (1/m)*somme;
}

double[] gradientDescent(){
	double m = 10;
	Point *lst_point = malloc(m * sizeof(Point));

	/*for (int i = 0; i < m; i++){
		Point p;
		p.x =  rand()%10;
		p.y =  rand()%10;
		lst_point[i] = p;
		printf("%.2f %.2f\n",p.x,p.y);
	}

	double a = rand()%1000;
	double b = rand()%1000;*/

	Point p;
	p.x = 2;
	p.y = 1;
	lst_point[0] = p;
	Point p1;
	p1.x = 2;
	p1.y = 3;
	lst_point[1] = p1;
	Point p2;
	p2.x = 4;
	p2.y = 2;
	lst_point[2] = p2;
	Point p3;
	p3.x = 3;
	p3.y = 5;
	lst_point[3] = p3;
	Point p4;
	p4.x = 7;
	p4.y = 3;
	lst_point[4] = p4;
	Point p5;
	p5.x = 6;
	p5.y = 7;
	lst_point[5] = p5;
	Point p6;
	p6.x = 8;
	p6.y = 4;
	lst_point[6] = p6;
	Point p7;
	p7.x = 8;
	p7.y = 6;
	lst_point[7] = p7;
	Point p8;
	p8.x = 4;
	p8.y = 6;
	lst_point[8] = p8;
	Point p9;
	p9.x = 7;
	p9.y = 5;
	lst_point[9] = p9;

	double a = 10;
	double b = 7;

	printf("%.2f %.2f\n",a,b);
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
	double coeff[2];
	coeff[0] = a;
	coeff[1] = b;

	return coeff;
}

double main(){
	srand(time(0));

	GtkBuilder *builder;
    GtkWidget *window;

	// constructing window
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "../gradient_descent.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "gradient_descent"));
    gtk_builder_connect_signals(builder, NULL);
	
	//GObjects
    GtkDrawingArea * drawing_area = (GtkDrawingArea*) gtk_builder_get_object(builder, "drawing_area");

    //signals
	g_signal_connect (G_OBJECT (drawing_area), "draw", G_CALLBACK (draw_callback), NULL);
	
	// - - - 
    g_object_unref(builder);
    gtk_widget_show(window);                
    gtk_main();

	
	return EXIT_SUCCESS;
}
