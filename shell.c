#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status;

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

		if (strcmp(line, "exit") == 0)
			break;

		if (line[0] == '\0')
			continue;

		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			continue;
		}

		if (pid == 0)
		{
			char *argv[] = { line, NULL };

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

	free(line);
	return 0;
}
