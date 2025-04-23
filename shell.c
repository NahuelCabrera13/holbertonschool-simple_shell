#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

/**
 * borrar_espacio - sirve para borrar los espacios y las tabulaciones al inicio y final de cada comando 
 * @input: The original string entered by the user.
 *
 * Return: A pointer to the trimmed version of the string.
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
 * ejecutar_comando - Forks and executes a command using execve.
 * @line: The full path of the command to be executed.
 *
 * Return: Nothing. If the fork fails, it does nothing.
 */

void ejecutar_comando(char *line)
{
	pid_t pid;
	int status;
	char *argv[2];

	pid = fork();
	if (pid < 0)
		return;
	if (pid == 0)
	{
		argv[0] = line;
		argv[1] = NULL;
		execve(line, argv, environ);
		fprintf(stderr, "%s: command not found\n", line);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
}

/**
 * main - Entry point for the custom shell.
 *
 * Return: Always returns 0 on successful execution.
 */

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		printf("#peladosupremo$ ");

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			putchar('\n');
			break;
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (strcmp(line, "exit") == 0)
		{
			printf("odalep ed olep omoc etsiuf eT\n");
			break;
		}
		line = borrar_espacio(line);
		if (line[0] == '\0')
			continue;
		if (access(line, X_OK) != 0)
		{
			fprintf(stderr, "%s: command not found\n", line);
			continue;
		}

		ejecutar_comando(line);
	}

	free(line);
	return (0);
}
