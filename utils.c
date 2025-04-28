#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * borrar_espacio - Recorta espacios y tabulaciones
 * @input: Cadena de entrada
 * Return: Cadena limpia
 */
char *borrar_espacio(char *input)
{
	char *start = input;
	char *end;

	while (*start == ' ' || *start == '\t')
		start++;
	if (*start == '\0')
		return (start);

	end = start + strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t'))
		end--;
	*(end + 1) = '\0';
	return (start);
}

/**
 * tokenizar_entrada - Separa la línea en tokens
 * @line: Línea de entrada
 * @argv: Arreglo para guardar tokens
 * Return: Cantidad de tokens
 */
int tokenizar_entrada(char *line, char **argv)
{
	int argc = 0;
	char *tok;

	tok = strtok(line, " \t");
	while (tok && argc < 99)
	{
		argv[argc++] = tok;
		tok = strtok(NULL, " \t");
	}
	argv[argc] = NULL;
	return (argc);
}

/**
 * encontrar_path - Encuentra la variable PATH manualmente
 * Return: valor de PATH o NULL
 */
char *encontrar_path(void)
{
	int i = 0;
	char *path_prefix = "PATH=";
	size_t prefix_len = 5;

	while (environ[i])
	{
		if (strncmp(environ[i], path_prefix, prefix_len) == 0)
			return (environ[i] + prefix_len);
		i++;
	}
	return (NULL);
}

/**
 * buscar_en_path - Busca el comando en los directorios de PATH
 * @cmd: comando a buscar
 * Return: ruta completa si existe, NULL si no
 */
char *buscar_en_path(char *cmd)
{
	char *path, *path_copy, *dir, *full_path;
	size_t len;

	path = encontrar_path();
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		len = strlen(dir) + strlen(cmd) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		snprintf(full_path, len, "%s/%s", dir, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * leer_linea - Lee una línea mostrando el prompt
 * @line: Puntero para guardar la línea
 * @len: Puntero al tamaño del buffer
 * Return: Número de caracteres leídos
 */
ssize_t leer_linea(char **line, size_t *len)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "#peladosupremo$ ", 16);
	return (getline(line, len, stdin));
}
