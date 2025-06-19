FUENTE = TPTPVS
PRUEBA = examples/fof.p
LIB = lfl

all: compile run2

all2: compile run3

compile:
	flex $(FUENTE).l
	bison -o $(FUENTE).tab.c $(FUENTE).y -yd -v --graph=$(FUENTE).dot
	gcc -g -o $(FUENTE) lex.yy.c $(FUENTE).tab.c structs.c -$(LIB) 

run:
	./$(FUENTE) < $(PRUEBA)

run2:
	./$(FUENTE) -f $(PRUEBA)

run3:
	./$(FUENTE) -d examples -h 10

clean:
	rm $(FUENTE) lex.yy.c $(FUENTE).tab.c $(FUENTE).tab.h
