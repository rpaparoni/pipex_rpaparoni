# Pipex

## Descripción

Pipex es un proyecto de la escuela 42 que busca replicar el comportamiento de la tubería (pipeline) en Unix, permitiendo la comunicación entre procesos a través de `pipe()`, `dup2()` y `execve()`.

El objetivo es ejecutar comandos en una cadena como:

```bash
< infile cmd1 | cmd2 > outfile
```

Esto significa que la salida de `cmd1` se convierte en la entrada de `cmd2`, y el resultado final se guarda en `outfile`.

## Instalación y Uso

### Compilación

Para compilar el proyecto, simplemente ejecuta:

```bash
make
```

Esto generará el ejecutable `pipex`.

Para compilar el bonus (soporte para `here_doc` y múltiples pipes):

```bash
make bonus
```

### Uso

Para ejecutar el programa:

```bash
./pipex infile "comando1" "comando2" outfile
```

Ejemplo:

```bash
./pipex input.txt "cat -e" "wc -l" output.txt
```

Esto tomará `input.txt`, ejecutará `cat -e`, luego pasará su salida a `wc -l` y finalmente guardará el resultado en `output.txt`.

#### Bonus (Soporte para here\_doc)

Si quieres utilizar `here_doc` para simular una entrada estándar interactiva:

```bash
./pipex here_doc LIMITER "comando1" "comando2" output.txt
```

Ejemplo:

```bash
./pipex here_doc END "cat" "wc -l" output.txt
```

Aquí, el programa leerá la entrada estándar hasta encontrar la palabra `END`, luego procesará los comandos y guardará la salida en `output.txt`.

## Funciones Utilizadas

El programa utiliza funciones clave de Unix como:

- `pipe()` - Crea un canal de comunicación entre procesos.
- `fork()` - Crea procesos hijo para ejecutar comandos.
- `dup2()` - Redirige la entrada/salida estándar.
- `execve()` - Ejecuta comandos en un entorno nuevo.
- `waitpid()` - Espera la terminación de procesos hijo.

## Errores y Manejo de Excepciones

El programa maneja errores comunes como:

- Archivo de entrada inexistente.
- Comando no encontrado o incorrecto.
- Permisos insuficientes para abrir archivos.
- Fallos en `pipe()`, `fork()`, o `execve()`.

Si algo falla, se imprimirá un mensaje de error con una funcion especifica.

##

