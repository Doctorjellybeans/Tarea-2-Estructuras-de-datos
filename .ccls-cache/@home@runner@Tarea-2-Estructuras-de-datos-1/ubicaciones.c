#include "ubicaciones.h"
#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TAMANO 256


// Función hash simple para calcular el índice en la tabla hash
unsigned int hash(char *nombre, int capacidad) {
  unsigned int hashValue = 0;
  for (int i = 0; nombre[i] != '\0'; i++) {
    hashValue += (unsigned int)nombre[i];
  }
  return hashValue % capacidad;
}

// Función para crear una nueva tabla de hash dinámica
TablaHash *crearTabla(int capacidad) {
  TablaHash *nuevaTabla = (TablaHash *)malloc(sizeof(TablaHash));
  if (nuevaTabla != NULL) {
    nuevaTabla->capacidad = capacidad;
    nuevaTabla->elementos = 0;
    nuevaTabla->tabla =
        (ListaColisiones *)malloc(capacidad * sizeof(ListaColisiones));
    if (nuevaTabla->tabla != NULL) {
      for (int i = 0; i < capacidad; i++) {
        nuevaTabla->tabla[i].inicio = NULL;
      }
      return nuevaTabla;
    } else {
      free(nuevaTabla);
    }
  }
  return NULL;
}

// Funcion para liberar la tabla de ubicaciones
void liberarTabla(TablaHash **tabla) {
  if (*tabla == NULL) {
    return;
  }

  for (int i = 0; i < (*tabla)->capacidad; i++) {
    NodoUbicaciones *nodo = (*tabla)->tabla[i].inicio;
    while (nodo != NULL) {
      NodoUbicaciones *temp = nodo;
      nodo = nodo->siguiente;
      free(temp);
    }
  }

  free((*tabla)->tabla);
  free(*tabla);
  *tabla = NULL;
}

// Función para redimensionar la tabla de hash
void redimensionarTabla(TablaHash **tabla) {
  if (*tabla == NULL) {
    return;
  }

  int nuevaCapacidad = (*tabla)->capacidad * 2;

  TablaHash *nuevaTabla = crearTabla(nuevaCapacidad);

  // Transferencia de elementos
  for (int i = 0; i < (*tabla)->capacidad; i++) {
    ListaColisiones *listaActual = &((*tabla)->tabla[i]);
    NodoUbicaciones *nodo = listaActual->inicio;

    while (nodo != NULL) {
      // Rehash
      unsigned int nuevoIndice = hash(nodo->punto.nombre, nuevaCapacidad);

      NodoUbicaciones *nuevoNodo =
          (NodoUbicaciones *)malloc(sizeof(NodoUbicaciones));
      if (nuevoNodo != NULL) {
        nuevoNodo->punto = nodo->punto;
        nuevoNodo->siguiente = nuevaTabla->tabla[nuevoIndice].inicio;
        nuevaTabla->tabla[nuevoIndice].inicio = nuevoNodo;
      }

      nodo = nodo->siguiente;
    }
  }

  liberarTabla(tabla);
  *tabla = nuevaTabla;
}

// Funcion para registrar los puntos de interes
void registrarPuntoDeInteres(TablaHash **tabla, char *nombre, char *tipo,
                             char *direccion, char *horario,
                             char *descripcion) {
  if (*tabla == NULL) {
    return;
  }

  unsigned int indice = hash(nombre, (*tabla)->capacidad);

  NodoUbicaciones *nuevoNodo =
      (NodoUbicaciones *)malloc(sizeof(NodoUbicaciones));
  if (nuevoNodo != NULL) {
    strcpy(nuevoNodo->punto.nombre, nombre);
    strcpy(nuevoNodo->punto.tipo, tipo);
    strcpy(nuevoNodo->punto.direccion, direccion);
    strcpy(nuevoNodo->punto.horario, horario);
    strcpy(nuevoNodo->punto.descripcion, descripcion);

    nuevoNodo->siguiente = (*tabla)->tabla[indice].inicio;
    (*tabla)->tabla[indice].inicio = nuevoNodo;
  }
}

// Función para mostrar datos de un punto de interés
void mostrarDatosPuntoDeInteres(TablaHash *tabla, char *nombre) {
  if (tabla == NULL) {
    return;
  }

  unsigned int indice = hash(nombre, tabla->capacidad);

  NodoUbicaciones *nodo = tabla->tabla[indice].inicio;

  while (nodo != NULL) {
    if (strcmp(nodo->punto.nombre, nombre) == 0) {
      printf("===========================================\n");
      printf("            INFORMACIÓN DEL SITIO BUSCADO\n");
      printf("===========================================\n");
      printf("Nombre:      %s\n", nodo->punto.nombre);
      printf("Tipo:        %s\n", nodo->punto.tipo);
      printf("Dirección:   %s\n", nodo->punto.direccion);
      printf("Horario:     %s\n", nodo->punto.horario);
      printf("Descripción: %s\n", nodo->punto.descripcion);
      printf("===========================================\n");
      return;
    }
    nodo = nodo->siguiente;
  }

  printf("El punto de interés \"%s\" no se encontró en la tabla.\n", nombre);
}

// Funcion para eliminar puntos de interes
void eliminarPuntosDeInteres(TablaHash **tabla, char *nombre) {
  if (tabla == NULL) {
    return;
  }
  unsigned int indice =
      hash(nombre,
           (*tabla)->capacidad); // para acceder debes de dejarla asi (*tabla)
  ListaColisiones *lista = &((*tabla)->tabla[indice]); // pero es mas facil asi

  NodoUbicaciones *temp = (*tabla)->tabla[indice].inicio;
  NodoUbicaciones *anterior = NULL;

  if (lista->inicio == NULL) {
    printf("no se encuentra el punto de interes\n");
    return;
  }

  while (temp != NULL) {
    if (strcmp(nombre, temp->punto.nombre) == 0) {
      if (anterior == NULL) { // Caso 1 el nodo a eliminar esta al principio
        lista->inicio = temp->siguiente;
      } else { // Caso 2 el nodo a eliminar NO se encuentra al principio
        anterior->siguiente = temp->siguiente;
      }
      free(temp);
    }
    anterior = temp;
    temp = temp->siguiente;
  }
}

// Función para mostrar todos los puntos de interés de un tipo
void mostrarPuntosPorTipo(TablaHash *tabla, char *tipo) {
  if (tabla == NULL) {
    return;
  }
  printf("===========================================\n");
  printf("   INFORMACIÓN POR TIPO \"%s\"\n", tipo);
  printf("===========================================\n");
  for (int i = 0; i < tabla->capacidad; i++) {
    NodoUbicaciones *nodo = tabla->tabla[i].inicio;
    while (nodo != NULL) {
      if (strcmp(nodo->punto.tipo, tipo) == 0) {
        printf("=====================#%d======================\n", i);
        printf("Nombre:      %s\n", nodo->punto.nombre);
        printf("Tipo:        %s\n", nodo->punto.tipo);
        printf("Dirección:   %s\n", nodo->punto.direccion);
        printf("Horario:     %s\n", nodo->punto.horario);
        printf("Descripción: %s\n", nodo->punto.descripcion);
        printf("==============================================\n");
      }
      nodo = nodo->siguiente;
    }
  }
}



