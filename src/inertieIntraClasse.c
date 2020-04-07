#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _Point {
	int x;
	int y;
	int groupe;
} Point;

typedef struct _Points {
	struct _Point * listPoint;
	int nb;
} Points;


double distanceCarreEuclienne(Point a, Point b){
	double val1 = ((double)a.x-(double)b.x)*((double)a.x-(double)b.x);
	double val2 = ((double)a.y-(double)b.y)*((double)a.y-(double)b.y);
	return  val1 + val2;
}

Points * getPtsGroupe(Points * points, int groupe){
	Points * ptsInGrp = malloc(sizeof(Points));
	ptsInGrp->listPoint = malloc(points->nb*sizeof(Point));
	int k = 0;
	for (int i = 0; i < points->nb; i++){
		if (points->listPoint[i].groupe == groupe){
			ptsInGrp->listPoint[k] = points->listPoint[i];
			k++;
		}
	}
	ptsInGrp->nb = k;
	return ptsInGrp;
}


int nombreGrps(Points * points){
	int groupe = 0;
	for (int i = 0; i < points->nb; i++){
		if (points->listPoint[i].groupe != groupe){
			groupe++;
		}
	}
	return groupe+1;
}

Point mean(Points * points){
	Point pts;
	int n = points->nb;
	int x = 0;
	int y = 0;

	for (int i = 0; i < points->nb; i++){
		x += points->listPoint[i].x;
		y += points->listPoint[i].y;
	}
	pts.x = x/n;
	pts.y = y/n;
	pts.groupe = points->listPoint[0].groupe;

	return pts;
}

double inertieIntraClasse(Points * points){
	int n = points->nb;
	double dist = 0;
	int nbGrp = nombreGrps(points);
	for (int i = 0; i < nbGrp; i++){
		Points * ptsInGrps = getPtsGroupe(points, i);
		for (int j = 0 ; j < ptsInGrps->nb; j++){
			dist += distanceCarreEuclienne(ptsInGrps->listPoint[j],mean(ptsInGrps));
		}
		free(ptsInGrps->listPoint);
		free(ptsInGrps);
	}
	return dist/n;
}

int main(){

	int MAX_PTS = 10;
	int n;
	int nbGrp;
	char pts[10*sizeof(char)];
	int ptsX;
	int ptsY;
	int cpt = 0;

	printf("%s\n", "Calcule de l'inertie intra-classe");
	printf("%s ", "Nombre de groupe : ");
	scanf("%d",&n);
	printf("%d\n", (n*10)*10*sizeof(char));
	Points * mesPoints = malloc(sizeof(Points));
	mesPoints->listPoint = malloc(n*sizeof(Point));
	for (int i = 0; i < n; i++){
		printf("Nombre de points dans le groupe %d (max: %d): ", i+1, MAX_PTS);
		scanf("%d",&nbGrp);
		mesPoints->listPoint = realloc(mesPoints->listPoint,n*nbGrp*sizeof(Point));
		for (int j = 0; j < nbGrp; j++) {
			Point monPts;
			printf("Points n°%d -> x : ", j+1);
			scanf("%d",&monPts.x);
			printf("Points n°%d -> y : ", j+1);
			scanf("%d",&monPts.y);
			monPts.groupe = i;
			mesPoints->listPoint[cpt] = monPts;
			printf("-----------\n");
			cpt++;
		}
	}
	mesPoints->nb = cpt;
	printf("%.2f\n", inertieIntraClasse(mesPoints));

	free(mesPoints->listPoint);
	free(mesPoints);
	return EXIT_SUCCESS;
}
