# hsh - peladosupremo Shell

Este repositorio contiene la implementación de una shell simple llamada `hsh`, escrita en lenguaje C. Esta shell puede ejecutarse en modo interactivo o no interactivo, interpretar comandos del usuario y ejecutarlos utilizando llamadas al sistema como `fork()`, `execve()` y `access()`.

---

## 📄 Descripción

`hsh` es una shell personalizada que emula el comportamiento básico de una shell de Unix.  
Puede ejecutar comandos con rutas completas como `/bin/ls`, manejar errores básicos, cortar espacios innecesarios y retornar correctamente el código de salida del último comando ejecutado.

---

## 🚀 Funcionalidades

- Leer entradas con `getline()`
- Eliminar espacios y tabulaciones innecesarias
- Separar comandos y argumentos con `strtok()`
- Verificar permisos de ejecución con `access()`
- Crear procesos con `fork()` y ejecutar comandos con `execve()`
- Retornar el código de salida del último comando (`$?`)
- Modo interactivo y no interactivo
- Comando interno `exit` para salir de la shell

---

## 📂 Archivos del proyecto

| Archivo        | Descripción                                                        |
|----------------|--------------------------------------------------------------------|
| `shell.c`      | Contiene el código fuente principal de la shell                   |
| `main.h`       | Encabezado con prototipos y librerías necesarias                  |
| `README.md`    | Documentación del proyecto                                        |

---

## 🧠 Prototipos de funciones

| Función                         | Descripción                                                                 |
|---------------------------------|-----------------------------------------------------------------------------|
| `char *borrar_espacio(char *);` | Elimina espacios y tabulaciones al inicio y final de una cadena            |
| `int megan_tokens_colo(char *, char **);` | Tokeniza una línea en un arreglo de argumentos para `execve()`    |
| `void ejecutar_comando(char **);` | Ejecuta un comando con `execve()` después de hacer `fork()`               |
| `int main(void);`               | Función principal: gestiona lectura, parseo, validación y ejecución        |

---

## 🔧 Valor de retorno

La shell retorna el código de salida del último comando ejecutado.  
Por ejemplo, si `/bin/ls /noexiste` retorna 2, la shell termina con código 2.

---

## 💻 Ejemplo de uso interactivo

```bash
$ ./hsh
#peladosupremo$ /bin/ls
AUTHORS
README.md
hsh
main.h
shell.c
#peladosupremo$ exit
odalep ed olep omoc etsiuf eT
