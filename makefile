myMovie: main.o signal.o ReadLog.o inputTag.o makeList.o Option.o
	gcc -o myMovie main.o signal.o ReadLog.o inputTag.o makeList.o Option.o
main.o:
	gcc -c main.c
signal.o:
	gcc -c signal.c
ReadLog.o:
	gcc -c ReadLog.c
inputTag.o:
	gcc -c inputTag.c
makeList.o:
	gcc -c makeList.c
Option.o:
	gcc -c Option.c
clean:
	rm -rf main.o
	rm -rf signal.o
	rm -rf ReadLog.o
	rm -rf inputTag.o
	rm -rf makeList.o
	rm -rf Option.o
