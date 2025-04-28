#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>

extern char **environ;

int simple_shell(void);
char *borrar_espacio(char *input);
int tokenizar_entrada(char *line, char **argv);
char *buscar_en_path(char *cmd);
ssize_t leer_linea(char **line, size_t *len);
void ejecutar_comando(char *cmd, char **argv);

#endif
