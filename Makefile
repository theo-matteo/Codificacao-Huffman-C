# Nome dos executáveis
COMPACTA = compacta
DESCOMPACTA = descompacta

# Lista de arquivos .c para o compacta e descompacta
SRCS_COMPACTA = compacta.c utils.c tree.c bitmap.c
SRCS_DESCOMPACTA = descompacta.c utils.c tree.c bitmap.c

# Comandos para compilar os arquivos
CC = gcc
CFLAGS = -Wall -Wextra -g

# Comandos para executar os programas com argumentos de linha de comando
COMPACTA_CMD = ./$(COMPACTA) input.txt
DESCOMPACTA_CMD = ./$(DESCOMPACTA) input.txt.comp

# Regra padrão: compilação de ambos os programas
all: $(COMPACTA) $(DESCOMPACTA)

# Regra para compilar o compacta
$(COMPACTA): $(SRCS_COMPACTA)
	$(CC) $(CFLAGS) $(SRCS_COMPACTA) -o $(COMPACTA)

# Regra para compilar o descompacta
$(DESCOMPACTA): $(SRCS_DESCOMPACTA)
	$(CC) $(CFLAGS) $(SRCS_DESCOMPACTA) -o $(DESCOMPACTA)

# Regra para executar o programa compacta e depois descompacta
run: $(COMPACTA) $(DESCOMPACTA)
	$(COMPACTA_CMD)
	$(DESCOMPACTA_CMD)

# Regra para limpar os arquivos objeto (arquivos .o), executáveis e o arquivo binario
clean:
	rm -f $(COMPACTA) $(DESCOMPACTA) input.txt.comp output.txt
