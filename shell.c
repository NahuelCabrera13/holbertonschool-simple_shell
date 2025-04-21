#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - Its the principal function (shell).
 *
 *
 *
 */


extern char **environ;

int main(void)
{
	char *line = NULL, *clean_line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status = 0, start = 0, end = 0, i = 0;


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

		start = 0;
		end = strlen(line) - 1;

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
		clean_line = line + start;

		if (strcmp(clean_line, "exit") == 0)
		{
			printf("odalep ed olep omoc etsiuf eT\n");
			break;
		}

		if (clean_line[0] == '\0')
			continue;

		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			continue;
		}

		if (pid == 0)
		{
			char *argv[2];

			argv[0] = clean_line;
			argv[1] = NULL;

			if (execve(clean_line, argv, environ) == -1)
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
	return (0);
}
