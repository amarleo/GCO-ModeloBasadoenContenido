# SISTEMAS DE RECOMENDACIÓN
## MODELOS BASADOS EN EL CONTENIDO

> Nombre: Alejandro Martín de León  
> Contacto: alu0101015941@ull.edu.es

## Índice

1. [Introducción](#introducción)  
2. [Estructura del repositorio](#estructura-del-repositorio)
3. [Detalles sobre el código](#detalles-sobre-el-código)
4. [Páginas que componen principalmente la web](#páginas-que-componen-principalmente-la-web)  
    4.1. [Index (login)](#index-login)  
    4.2. [Sign in](#sign-in)  
    4.3. [Home](#home)  
    4.4. [Menú desplegable](#menú-desplegable)  
    4.5. [Perfil de usuario](#perfil-de-usuario)  
    4.6. [Página de reciclado](#página-de-reciclado)  
    4.7. [Página de actividades](#página-de-actividades)  
    &nbsp;&nbsp;&nbsp;4.7.1. [Actividad Trail](#actividad-trail)  
    4.8. [Tienda de intercambio de puntos](#tienda-de-intercambios)  


## Introducción

Este informe tiene como objetivo detallar el código que ha sido elaborado, así como de realizar un pequeño análisis de los datos obtenido tras los ejemplos propuestos.

## Estructura del repositorio

El repositorio se descompone en los siguientes directorios: 

```
.
├── bin
│   └── main.o
├── csv
│   ├── file-01.txt.csv
│   ├── file-02.txt.csv
│   └── file-03.txt.csv
├── files
│   ├── file-01.txt
│   ├── file-02.txt
│   └── file-03.txt
├── include
├── makefile
├── README.md
├── sist_recomendacion
└── src
    └── main.cpp

```

Con el objetivo de comprender mejor cada uno de los directorios, se procede a realizar una breve descripción: 

- **bin**: Aquí se almacenan los ficheros .o
- **csv**: Después de ejecutar el programa, si se ha elegido la opción CSV, se generará un fichero de salida por cada fichero de entrada, conteniendo la tabla resultado.
- **files**: Es el directorio que almacena los ficheros de entrada.
- **src**: Almacena el código fuente principal del programa
- **makefile**: Al ejecutar la orden "make", se encarga de compilar todo el programa principal.
- **sist_recomendacion**: Es el ejecutable creado tras compilar el programa.


## Detalles sobre el código

Principalmente se ha creado el programa sobre un única fuente de códi