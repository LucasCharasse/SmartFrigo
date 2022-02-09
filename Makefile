OPTIONS = -O2 -Wall        # pour optimiser

all : tp2

tp2 : main.cpp SmartFrigo.h SmartFrigo.o
	g++ ${OPTIONS} -o tp2 main.cpp SmartFrigo.o

SmartFrigo.o : SmartFrigo.cpp SmartFrigo.h
	g++ ${OPTIONS} -c -o SmartFrigo.o SmartFrigo.cpp

clean:
	rm -rf tp1 *~ *.o

