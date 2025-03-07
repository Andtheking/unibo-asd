# Variabili per i file
SOURCE_FILE = shooting-stars.c
OUTPUT_FILE = shooting-stars.out

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
