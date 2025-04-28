#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * handle_input - Reads and processes the input line
 * @line: pointer to the input buffer
 * @len: pointer to the size of buffer
 * @argv: arguments array to fill
 * Return: number of tokens or -1 if error
 */
int handle_input(char **line, size_t *len, char **argv)
{
	ssize_t nread;
	char *clean_line;
	int argc = 0;

	nread = leer_linea(line, len);
	if (nread == -1)
		return (-1);

	if ((*line)[nread - 1] == '\n')
		(*line)[nread - 1] = '\0';

	clean_line = borrar_espacio(*line);
	if (clean_line[0] == '\0')
		return (0);

	argc = tokenizar_entrada(clean_line, argv);
	return (argc);
}

/**
 * process_command - Handles command execution
 * @argv: arguments array
 */
void process_command(char **argv)
{
	char *cmd_path;

	if (strcmp(argv[0], "exit") == 0)
		exit(0);

	if (strchr(argv[0], '/'))
	{
		if (access(argv[0], X_OK) != 0)
		{
			fprintf(stderr, "%s: command not found\n", argv[0]);
			return;
		}
		cmd_path = argv[0];
	}
	else
	{
		cmd_path = buscar_en_path(argv[0]);
		if (!cmd_path)
		{
			fprintf(stderr, "%s: command not found\n", argv[0]);
			return;
		}
	}
	ejecutar_comando(cmd_path, argv);
	if (cmd_path != argv[0])
		free(cmd_path);
}

/**
 * simple_shell - Main shell loop
 * Return: Exit status
 */
int simple_shell(void)
{
	char *line = NULL;
	size_t len = 0;
	char *argv[100];
	int argc;

	while (1)
	{
		argc = handle_input(&line, &len, argv);

		if (argc == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		if (argc == 0)
			continue;

		process_command(argv);
	}

	free(line);
	return (0);
}
