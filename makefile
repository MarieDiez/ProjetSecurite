all :
	cd src && gcc -rdynamic `pkg-config --cflags gtk+-3.0` piMonteCarlo.c -o ../build/piMonteCarlo `pkg-config --libs gtk+-3.0`
	gcc src/piMonteCarlo.c -o build/piMonteCarlo
	gcc src/date.c -o build/date
	gcc src/inertieIntraClasse.c -o build/inertieIntraClasse
	gcc src/piece.c -o build/piece
	gcc src/kmMi.c -o build/kmMi

mediaplayer :
	cd src && gcc -rdynamic `pkg-config --cflags gtk+-3.0` mediaplayer.c -o ../build/mediaplayer `pkg-config --libs gtk+-3.0`
	
clean:
	rm -f build/*