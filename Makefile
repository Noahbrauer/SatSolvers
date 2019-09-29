CFLAGS = -std=c++11 -Wall

PROGRAM = SATAlg
OBJS = DPLL.o GSAT.o walkSAT.o readSATFile.o SATSource.o

all:$(PROGRAM)

$(PROGRAM):$(OBJS)
	g++ -O3 $(OBJS) -o $(PROGRAM)

O3:$(OBJS)
	g++ -O3 $(OBJS) -o $(PROGRAM)

O2:$(OBJS)
	g++ -O2 $(OBJS) -o $(PROGRAM)

O1:$(OBJS)
	g++ -O1 $(OBJS) -o $(PROGRAM)

SATSource.o: SATSource.cpp
	g++ -c $(CFLAGS) SATSource.cpp

readSATFile.o: readSATFile.cpp readSATFile.h
	g++ -c $(CFLAGS) readSATFile.cpp

DPLL.o: DPLL.cpp DPLL.h
	g++ -c $(CFLAGS) DPLL.cpp

GSAT.o: GSAT.cpp GSAT.h
	g++ -c $(CFLAGS) GSAT.cpp

walkSAT.o: walkSAT.cpp walkSAT.h
	g++ -c $(CFLAGS) walkSAT.cpp

clean:
	rm -f core $(PROGRAM) $(OBJS)
