<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>peladosupremo Shell</title>
</head>
<body>

	<h1>🖥️ peladosupremo Shell</h1>

	<p>
	Este proyecto es una implementación de una shell mínima hecha en C, inspirada en el funcionamiento de la shell de Unix.
	</p>

	<h2>📄 Descripción</h2>
	<p>
	La shell <code>./hsh</code> lee comandos del usuario (modo interactivo) o desde una entrada estándar (modo no interactivo),
	los interpreta, los tokeniza, y los ejecuta usando <code>execve()</code>.
	También gestiona errores, recortes de espacios, y retorna correctamente el código de salida del último comando ejecutado.
	</p>

	<h2>🧠 Funcionalidades</h2>
	<ul>
		<li>Lectura de comandos con <code>getline()</code></li>
		<li>Eliminación de espacios con <code>borrar_espacio()</code></li>
		<li>Tokenización con <code>strtok()</code></li>
		<li>Chequeo de permisos con <code>access()</code></li>
		<li>Ejecución con <code>fork()</code> y <code>execve()</code></li>
		<li>Captura de código de salida con <code>WEXITSTATUS()</code></li>
		<li>Soporte para comando <code>exit</code></li>
		<li>Compatible con entrada no interactiva</li>
	</ul>

	<h2>📦 Archivos del Proyecto</h2>
	<table border="1" cellpadding="5">
		<tr><th>Archivo</th><th>Descripción</th></tr>
		<tr><td><code>shell.c</code></td><td>Contiene la implementación principal de la shell</td></tr>
		<tr><td><code>main.h</code></td><td>Prototipos de funciones y librerías requeridas</td></tr>
	</table>

	<h2>🔧 Funciones implementadas</h2>
	<table border="1" cellpadding="5">
		<tr><th>Función</th><th>Descripción</th></tr>
		<tr><td><code>char *borrar_espacio(char *input);</code></td><td>Recorta espacios y tabulaciones al inicio y fin de una cadena</td></tr>
		<tr><td><code>int megan_tokens_colo(char *line, char **argv);</code></td><td>Tokeniza una línea en palabras separadas</td></tr>
		<tr><td><code>void ejecutar_comando(char **argv);</code></td><td>Ejecuta un comando usando <code>fork()</code> y <code>execve()</code></td></tr>
		<tr><td><code>int main(void);</code></td><td>Función principal. Administra el ciclo de lectura, validación y ejecución</td></tr>
	</table>

	<h2>🧪 Ejemplo de uso</h2>
	<pre><code>
$ ./hsh
#peladosupremo$ /bin/ls
AUTHORS
README.html
hsh
main.h
shell.c
</code></pre>

	<h2>📌 Modo no interactivo</h2>
	<pre><code>
echo "/bin/ls" | ./hsh
</code></pre>

	<h2>🔚 Salida con 'exit'</h2>
	<pre><code>
#peladosupremo$ exit
odalep ed olep omoc etsiuf eT
</code></pre>

	<h2>📥 Requisitos del checker cubiertos</h2>
	<ul>
		<li>Soporte a modo no interactivo</li>
		<li>Uso correcto de getline, fork, execve, access</li>
		<li>Devolución correcta de códigos de salida</li>
		<li>Sin memory leaks (valgrind clean)</li>
	</ul>

	<h2>👨‍💻 Contribuyentes</h2>
	<ul>
		<li><strong>Nahuel Bica</strong></li>
		<li><strong>Erick Gaiero</strong></li>
	</ul>

</body>
</html>
