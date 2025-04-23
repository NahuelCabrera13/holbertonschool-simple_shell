#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * execute_comand - Its the principal function.
 * @clean_line: Pointer to clean line.
 */

void execute_comand(char *line)
{
	pid_t pid;
	int status;
	char *argv[2];

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		argv[0] = line;
		argv[1] = NULL;

		if (execve(line, argv, environ) == -1)
		{
			fprintf(stderr, "%s: No such file or directory\n", line);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) < 0)
			perror("waitpid");
	}
}

/**
 * main - Its the principal function (shell).
 * @*environ: Variable of environment
 * Return: 0 End program
 */

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		printf("#peladosupremo$ ");
		fflush(stdout);

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

		if (line[0] == '\0')
			continue;

		execute_comand(line);
	}

	free(line);
	return (0);
}
