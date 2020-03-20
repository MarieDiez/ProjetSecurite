#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

/* y =ax +b */
typedef struct _Point{
	double x;
	double y;
	int inner;
} Point;


double model(double x){
	return 2*x +3;
}

double carre(double number){
	return number*number;
}
/*

double costFunction(double a, double b, double (*model)(double), int m, Point * lst_point){
	double somme = 0;
	for (int i = 0; i < m; i++){
		somme += carre(a * model(lst_point[i].x) + b - lst_point[i].y);
	}
	return (1/(2*m))*somme;
}
*/

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

double main(){
	srand(time(0));
	printf("%s\n", "Gradient Descent algorithm");

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
	printf("%.2f %.2f\n", a, b);
	return EXIT_SUCCESS;
}


/* y = ax */
