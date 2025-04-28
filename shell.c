#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

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
	return argc;
}

void process_command(char **argv)
{
	char *cmd_path;
	pid_t pid;

	if (strcmp(argv[0], "exit") == 0)
		exit(0);

	if (strchr(argv[0], '/'))
	{
		if (access(argv[0], X_OK) != 0)
			exit(127);
		cmd_path = argv[0];
	}
	else
	{
		cmd_path = buscar_en_path(argv[0]);
		if (!cmd_path)
			exit(127);
	}

	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
		execve(cmd_path, argv, environ);
	else
	{
		int status;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			exit(WEXITSTATUS(status));
		exit(1);
	}
}

int simple_shell(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *argv[100];
	int argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("#peladosupremo$ ");
			fflush(stdout);
		}

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

		process_command(argv);
	}

	free(line);
	return 0;
}
