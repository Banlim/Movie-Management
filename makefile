grade: main.o signal.o ReadLog.o SaveLink.o inputTag.o
	gcc -o test main.o signal.o ReadLog.o SaveLink.o inputTag.o 
main.o:
	gcc -c main.c
signal.o:
	gcc -c signal.c
ReadLog.o:
	gcc -c ReadLog.c
SaveLink.o:
	gcc -c SaveLink.c
inputTag.o:
	gcc -c inputTag.c
clean:
	rm -rf main.o
	rm -rf signal.o
	rm -rf ReadLog.o
	rm -rf SaveLink.o
	rm -rf inputTag.o
