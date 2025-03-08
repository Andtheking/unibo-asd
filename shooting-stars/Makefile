
# Nome file principale senza estensioni
MAIN_FILE_NAME = shooting-stars

# Variabili per i file
SOURCE_FILE = $(MAIN_FILE_NAME).c
OUTPUT_FILE = $(MAIN_FILE_NAME).out

# Nel caso di altri file scriverli con uno spazio tra loro
# Se non ci sono lasciare vuoto
HEADER_FILES = 

# Regola di default
all: $(OUTPUT_FILE)

# Compilazione
# Le flag di GCC sono: 
# -g Per abilitare il debug
# -Wall -Wpedantic -std=c90 le vuole il prof
# -lm serve per avere le librerie di C standard

$(OUTPUT_FILE): $(SOURCE_FILE) $(HEADER_FILES)
	gcc -g -Wall -Wpedantic -std=c90 $(SOURCE_FILE) $(HEADER_FILES) -lm -o $(OUTPUT_FILE)
	chmod +x ./$(OUTPUT_FILE)

valgrind: $(OUTPUT_FILE)
	valgrind ./$(OUTPUT_FILE)

# Pulizia dei file prodotti
clean:
	rm -f $(OUTPUT_FILE)
