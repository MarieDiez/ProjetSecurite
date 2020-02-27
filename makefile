all :
	cd src && gcc -rdynamic `pkg-config --cflags gtk+-3.0` piMonteCarlo.c -o ../build/piMonteCarlo `pkg-config --libs gtk+-3.0`
	gcc src/date.c -o build/date
	gcc src/prix.c -o build/prix
	gcc src/piece.c -o build/piece
	gcc src/kmMi.c -o build/kmMi

mediaplayer :
	cd src && gcc -rdynamic `pkg-config --cflags gtk+-3.0` mediaplayer.c -o ../build/mediaplayer `pkg-config --libs gtk+-3.0`
	
clean:
	rm -f build/*
