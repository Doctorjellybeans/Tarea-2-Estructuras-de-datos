#include "turistas.h"
#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funcion para crear una lista (turistas)
ListaTuristas *crearListaTuristas() {
  ListaTuristas *nuevaLista = (ListaTuristas *)malloc(sizeof(ListaTuristas));
  if (nuevaLista != NULL) {
    nuevaLista->inicio = NULL;
  }
  return nuevaLista;
}

// Función para registrar un turista
void registrarTurista(ListaTuristas *lista, char *pasaporte, char *nombre,
                      char *pais) {
  if (lista == NULL) {
    return;
  }

  Turista *nuevoTurista = (Turista *)malloc(sizeof(Turista));
  if (nuevoTurista != NULL) {
    strcpy(nuevoTurista->pasaporte, pasaporte);
    strcpy(nuevoTurista->nombre, nombre);
    strcpy(nuevoTurista->pais, pais);

    nuevoTurista->lugaresFavoritos = (listaFavoritos *)malloc(sizeof(listaFavoritos));
    if (nuevoTurista->lugaresFavoritos != NULL) {
      nuevoTurista->lugaresFavoritos->head = NULL;

      // Agregar el turista al inicio de la lista
      nuevoTurista->siguiente = lista->inicio;
      lista->inicio = nuevoTurista;
    } else {
      // Manejar error si no se puede asignar memoria para lugaresFavoritos
      free(nuevoTurista);  // Liberar memoria asignada para el turista
    }
  }
}


// Función para agregar un lugar favorito a un turista
void agregarLugarFavorito(ListaTuristas *lista, char *pasaporte, char *nombre_lugar) {
    if (lista == NULL) {
        return;
    }

    Turista *turistaActual = lista->inicio;
    while (turistaActual != NULL) {
        if (strcmp(turistaActual->pasaporte, pasaporte) == 0) { // Se encontró al turista
            LugarFavorito *nuevoFavorito = (LugarFavorito*)malloc(sizeof(LugarFavorito));
            strcpy(nuevoFavorito->lugar, nombre_lugar);
            nuevoFavorito->siguiente = NULL;

            listaFavoritos *listaFavoritosTurista = turistaActual->lugaresFavoritos;
            if (listaFavoritosTurista->head == NULL) {
                listaFavoritosTurista->head = nuevoFavorito;
            } else {
                nuevoFavorito->siguiente = listaFavoritosTurista->head;
                listaFavoritosTurista->head = nuevoFavorito;
            }
            return; 
        }
        turistaActual = turistaActual->siguiente;
    }
}

// Función para mostrar turistas por país
void mostrarTuristasPorPais(ListaTuristas *lista, char *paisBuscado) {
  if (lista == NULL) {
    return;
  }

  Turista *actual = lista->inicio;
  int encontrados = 0;

  printf("========== TURISTAS DE %s ==========\n", paisBuscado);
  while (actual != NULL) {
    if (strcmp(actual->pais, paisBuscado) == 0) {
      printf("Pasaporte: %s\n", actual->pasaporte);
      printf("Nombre:    %s\n", actual->nombre);
      printf("País:      %s\n", actual->pais);

      LugarFavorito *lugarActual = actual->lugaresFavoritos->head;
      if (lugarActual != NULL) {
        while (lugarActual != NULL) {
          printf("Lugares Favoritos: %s \n", lugarActual->lugar);
          lugarActual = lugarActual->siguiente;
        }
      } else {
        printf("Lugares Favoritos: ------ \n");
      }

      printf("==================================\n");
      encontrados = 1;
    }
    actual = actual->siguiente;
  }

  if (!encontrados) {
    printf("No se encontraron turistas de %s.\n", paisBuscado);
  }
}