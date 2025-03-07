# Variabili per i file
SOURCE_FILE = koch.c
OUTPUT_FILE = koch.out

# Nel caso di altri file
HEADER_FILES = libpsgraph.c 

# Regola di default
all: $(OUTPUT_FILE)

# Compilazione
$(OUTPUT_FILE): $(SOURCE_FILE) $(HEADER_FILES)
	gcc -Wall -Wpedantic -std=c90 $(SOURCE_FILE) $(HEADER_FILES) -lm -o $(OUTPUT_FILE)
	chmod +x $(OUTPUT_FILE)

# Pulizia
clean:
	rm -f $(OUTPUT_FILE)
	rm -f fiocco-di-koch.ps
	rm -f curva-di-koch.ps
