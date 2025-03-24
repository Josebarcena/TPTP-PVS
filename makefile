FUENTE = TFG
PRUEBA = examples/example1.p
LIB = lfl

all: compile run2

all2: compile run3

compile:
	flex $(FUENTE).l
	bison -o $(FUENTE).tab.c $(FUENTE).y -yd -v
	gcc -g -o $(FUENTE) lex.yy.c $(FUENTE).tab.c structs.c -$(LIB) 

run:
	./$(FUENTE) < $(PRUEBA)

run2:
	./$(FUENTE) -f $(PRUEBA)

run3:
	./$(FUENTE) -d examples

clean:
	rm $(FUENTE) lex.yy.c $(FUENTE).tab.c $(FUENTE).tab.h
