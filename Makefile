# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Arquivos-fonte e de cabeçalho
SRC = main.c campeonato.c
OBJ = $(SRC:.c=.o)
DEPS = campeonato.h utils.h

# Nome do executável final
TARGET = campeonato_gronerjose

# Regra padrão: compilar tudo
all: $(TARGET)

# Como gerar o executávelnmake -f Makefile.win
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Regra genérica para compilar .c em .o
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos compilados
clean:
	rm -f $(OBJ) $(TARGET)

# Rodar o programa
run: $(TARGET)
	./$(TARGET)