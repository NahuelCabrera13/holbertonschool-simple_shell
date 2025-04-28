#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * ejecutar_comando - Ejecuta el comando dado
 * @cmd: Ruta o comando
 * @argv: Argumentos del comando
 */
void ejecutar_comando(char *cmd, char **argv)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
		return;
	if (pid == 0)
	{
		execve(cmd, argv, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
}
