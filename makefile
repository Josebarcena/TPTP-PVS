CC = gcc
CFLAGS = -fsanitize=address -g -O0
LDFLAGS = -fsanitize=address -lfl

FLEX_SRC = TPTPVS.l
BISON_SRC = TPTPVS.y
UTILS_SRC = structs.c

FLEX_OUT = lex.yy.c
BISON_C = TPTPVS.tab.c
BISON_H = TPTPVS.tab.h

FUENTE = TPTPVS
PRUEBA = examples/fof.p
LIB = lfl -lpthread

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
	./$(FUENTE) -d examples -h 10

clean:
	rm $(FUENTE) lex.yy.c $(FUENTE).tab.c $(FUENTE).tab.h

asan: $(FLEX_OUT) $(BISON_C) $(UTILS_SRC)
	$(CC) $(CFLAGS) -o $(FUENTE) $(FLEX_OUT) $(BISON_C) $(UTILS_SRC) $(LDFLAGS)