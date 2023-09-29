#ifndef UBICACIONES_H
#define UBICACIONES_H

typedef struct {
  char nombre[50];
  char tipo[50];
  char direccion[100];
  char horario[50];
  char descripcion[200];
} PuntoDeInteres;

typedef struct NodoUbicaciones {
  PuntoDeInteres punto;
  struct NodoUbicaciones *siguiente;
} NodoUbicaciones;

typedef struct ListaColisiones {
  NodoUbicaciones *inicio;
} ListaColisiones;

typedef struct {
  int capacidad;
  int elementos;
  ListaColisiones *tabla;
} TablaHash;

unsigned int hash(char *nombre, int capacidad);

TablaHash *crearTabla(int capacidad);

void liberarTabla(TablaHash **tabla);

void redimensionarTabla(TablaHash **tabla);

void registrarPuntoDeInteres(TablaHash **tabla, char *nombre, char *tipo, char *direccion, char *horario, char *descripcion);

void mostrarDatosPuntoDeInteres(TablaHash *tabla, char *nombre);

void mostrarPuntosPorTipo(TablaHash *tabla, char *tipo);

void eliminarPuntosDeInteres(TablaHash **tabla, char *nombre);

void mostrarPuntosPorTipo(TablaHash *tabla, char *tipo);

char* leerValidarUbicaciones(int tipo);

#endif
