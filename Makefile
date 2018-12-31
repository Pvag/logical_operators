SOURCE=logical_operators.c
OUTPUT=logical_operators.o
COMPILER=gcc
FLAGS=-O3
DBG_FLAGS=-O0 -g -Wall -pedantic

$(OUTPUT): $(SOURCE)
	$(COMPILER) $(FLAGS) $^ -o $@

debug: $(SOURCE)
	$(COMPILER) $(DBG_FLAGS) $^ -o $@

.PHONY: clean

clean:
	rm $(OUTPUT)
	rm debug
	rm *.dSYM
