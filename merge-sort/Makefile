# Variabili per i file
SOURCE_FILE = merge-sort.c
OUTPUT_FILE = merge-sort.out

# Nel caso di altri file
HEADER_FILES = 

# Regola di default
all: $(OUTPUT_FILE)

# Compilazione
$(OUTPUT_FILE): $(SOURCE_FILE)
	gcc -Wall -Wpedantic -std=c90 $(SOURCE_FILE) -o $(OUTPUT_FILE)
	chmod +x $(OUTPUT_FILE)

# Pulizia
clean:
	rm -f $(OUTPUT_FILE)
