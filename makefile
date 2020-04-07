FLAGS_GTK_0 := -g -rdynamic `pkg-config --cflags gtk+-3.0`
FLAGS_GTK_1 := `pkg-config --libs gtk+-3.0`


all :
	mkdir -p build
	cd src && gcc $(FLAGS_GTK_0) piMonteCarlo.c -o ../build/piMonteCarlo $(FLAGS_GTK_1)
	cd src && gcc $(FLAGS_GTK_0) gradientDescentGTK.c -o ../build/gradientDescentGTK $(FLAGS_GTK_1)
	cd src && gcc $(FLAGS_GTK_0) mediaplayer.c -o ../build/mediaplayer $(FLAGS_GTK_1)
	gcc src/date.c -o build/date
	gcc src/inertieIntraClasse.c -o build/inertieIntraClasse
	gcc src/piece.c -o build/piece
	
clean:
	rm -f build/*
