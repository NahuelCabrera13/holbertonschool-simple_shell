#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * ignore_spaces - Its the principal function.
 * @clean_line: Variable to clean spaces
 * @line: Variable of line the code
 * Return: 0 End program
 */

void ignore_spaces(char *line, char **clean_line)
{
	int i, start = 0, end = strlen(line) - 1;

	for (i = 0; line[i] != '\0'; i++)
	{
		if (line[i] != ' ')
		{
			start = i;
			break;
		}
	}

	for (i = end; i >= 0; i--)
	{
		if (line[i] != ' ')
		{
			end = i;
			break;
		}
	}

	line[end + 1] = '\0';
	*clean_line = line + start;
}

/**
 * execute_comand - Its the principal function.
 * @clean_line: Pointer to clean line.
 */

void execute_comand(char *clean_line)
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
		argv[0] = clean_line;
		argv[1] = NULL;

		if (execve(clean_line, argv, environ) == -1)
		{
			fprintf(stderr, "%s: No such file or directory\n", clean_line);
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
	char *line = NULL, *clean_line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			putchar('\n');
			break;
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		ignore_spaces(line, &clean_line);

		if (strcmp(clean_line, "exit") == 0)
		{
			printf("odalep ed olep omoc etsiuf eT\n");
			break;
		}

		if (clean_line[0] == '\0')
			continue;

		execute_comand(clean_line);
	}

	free(line);
	return (0);
}
