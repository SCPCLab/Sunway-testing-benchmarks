CC=sw5cc

love: master.o slave.o
	${CC} -hybrid -O0 master.o slave.o -o benchmark

master.o: master.c
	${CC} -host -O0 master.c  -c  -lm 

slave.o: slave.c
	${CC} -O0 -slave slave.c  -c 



clean:
	rm -Rf fd *.o
