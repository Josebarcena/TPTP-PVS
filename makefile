FUENTE = TFG
PRUEBA = example.p
LIB = lfl

all: compile run

all2: compile run3

compile:
	flex $(FUENTE).l
	bison -o $(FUENTE).tab.c $(FUENTE).y -yd -v
	gcc -o $(FUENTE) lex.yy.c $(FUENTE).tab.c structs.c -$(LIB) 

run:
	./$(FUENTE) < $(PRUEBA)

run2:
	./$(FUENTE) $(PRUEBA)

run3:
	./$(FUENTE)

clean:
	rm $(FUENTE) lex.yy.c $(FUENTE).tab.c $(FUENTE).tab.h
