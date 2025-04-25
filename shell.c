#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

char *borrar_espacio(char *input)
{
	char *start = input;
	char *end;

	while (*start == ' ' || *start == '\t')
		start++;
	if (*start == '\0')
		return start;
	end = start + strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t'))
		end--;
	*(end + 1) = '\0';
	return start;
}

int megan_tokens_colo(char *line, char **argv)
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

void ejecutar_comando(char **argv)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
		return;
	if (pid == 0)
	{
		execve(argv[0], argv, environ);
		fprintf(stderr, "%s: command not found\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
}

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *argv[100];
	int argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		printf("#peladosupremo$ ");

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			putchar('\n');
			break;
		}
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		line = borrar_espacio(line);

		if (line[0] == '\0')
			continue;

		argc = megan_tokens_colo(line, argv);

		if (argc == 0)
			continue;

		if (strcmp(argv[0], "exit") == 0)
		{
			printf("odalep ed olep omoc etsiuf eT\n");
			break;
		}

		if (access(argv[0], X_OK) != 0)
		{
			fprintf(stderr, "%s: command not found\n", argv[0]);
			continue;
		}

		ejecutar_comando(argv);
	}

	free(line);
	return (0);
}
