# hsh - Simple Shell

Este proyecto consiste en la creación de una shell mínima escrita en lenguaje C. La shell ejecuta comandos ingresados por el usuario en modo interactivo o no interactivo, utilizando llamadas al sistema como `fork()`, `execve()`, `access()` y `waitpid()`.

---

## Descripción breve del proyecto

La shell implementada simula el comportamiento básico de una shell de Unix. Permite ejecutar comandos introducidos por el usuario utilizando rutas absolutas. Gestiona errores de forma simple, recorta espacios innecesarios en las entradas, y retorna el código de salida del último comando ejecutado.

---

## ¿Cómo empezar a usar la shell? (paso a paso)

1. Clonar el repositorio del proyecto:

```bash
git clone https://github.com/NahuelCabrera13/holbertonschool-simple_shell.git
```

2. Ingresar al directorio del proyecto:

```bash
cd holbertonschool-simple_shell
```

3. Compilar el código fuente:

```bash
gcc -Wall -Wextra -Werror -pedantic shell.c -o hsh
```

4. Ejecutar la shell:

```bash
./hsh
```

---

## Funcionalidades

- Lectura de comandos con `getline()`
- Eliminación de espacios iniciales y finales
- Separación de comandos en argumentos con `strtok()`
- Verificación de permisos de ejecución con `access()`
- Creación de procesos con `fork()` y ejecución con `execve()`
- Captura del código de salida del último proceso ejecutado
- Soporte para modo interactivo y no interactivo
- Comando `exit` para finalizar la shell

---

## Archivos del proyecto

| Archivo        | Descripción                                                        |
|----------------|--------------------------------------------------------------------|
| `shell.c`      | Contiene la implementación principal de la shell                   |
| `main.h`       | Archivo de cabecera con prototipos de funciones y librerías        |
| `README.md`    | Documentación del proyecto                                         |

---

## Prototipos de funciones

| Función                         | Descripción                                                                 |
|---------------------------------|-----------------------------------------------------------------------------|
| `char *borrar_espacio(char *);` | Elimina espacios y tabulaciones al inicio y final de una cadena            |
| `int megan_tokens_colo(char *, char **);` | Tokeniza una línea en un arreglo de argumentos para `execve()`    |
| `void ejecutar_comando(char **);` | Ejecuta un comando con `execve()` después de hacer `fork()`               |
| `int main(void);`               | Función principal. Administra el ciclo de lectura, validación y ejecución |

---

## Ejemplos de uso

### Modo interactivo

```bash
$ ./hsh
#peladosupremo$ /bin/ls
AUTHORS
README.md
hsh
main.h
shell.c
#peladosupremo$ /bin/echo Hola mundo
Hola mundo
#peladosupremo$ exit
odalep ed olep omoc etsiuf eT
```

### Modo no interactivo

```bash
echo "/bin/ls" | ./hsh
```

```bash
cat comandos.txt | ./hsh
```

Contenido de `comandos.txt`:

```
/bin/echo Esto es una prueba
/bin/ls
exit
```

---

## Llamadas al sistema utilizadas

| Llamada / Función | Descripción breve                                               |
|-------------------|------------------------------------------------------------------|
| `getline()`       | Lee la entrada del usuario o del pipe                           |
| `strtok()`        | Separa la entrada en tokens (comandos y argumentos)             |
| `fork()`          | Crea un nuevo proceso hijo                                      |
| `execve()`        | Ejecuta el comando solicitado desde el hijo                     |
| `waitpid()`       | Espera a que el hijo termine para continuar                     |
| `access()`        | Verifica si el archivo existe y si tiene permisos de ejecución  |
| `exit()`          | Finaliza el programa                                            |
| `isatty()`        | Detecta si la entrada es interactiva o redirigida               |

---

## Comportamiento general de la shell

1. Lee el input del usuario (o desde entrada estándar)
2. Elimina los espacios innecesarios
3. Tokeniza el input para separar el comando y sus argumentos
4. Verifica si el archivo existe y tiene permisos de ejecución
5. Crea un proceso hijo con `fork()`
6. El hijo ejecuta el comando con `execve()`
7. El padre espera al hijo con `waitpid()`
8. Se muestra el prompt nuevamente si está en modo interactivo

---

## Código de salida

La shell retorna el mismo código de salida del último comando ejecutado, accesible desde `$?`.  
Por ejemplo, si `/bin/ls /directorio_inexistente` falla con código `2`, la shell terminará con código `2`.

---

## Contribuyentes

- **Nahuel Cabrera**
- **Erick Gaiero**
