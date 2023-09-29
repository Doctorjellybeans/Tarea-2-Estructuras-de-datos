#ifndef TURISTAS_H
#define TURISTAS_H

typedef struct LugarFavorito {
  char lugar[50];
  struct LugarFavorito *siguiente;
} LugarFavorito;

typedef struct listaFavoritos {
    LugarFavorito *head;
} listaFavoritos;


typedef struct Turista {
  char pasaporte[10];
  char nombre[50];
  char pais[50];
  listaFavoritos *lugaresFavoritos;
  struct Turista *siguiente;
} Turista;

typedef struct ListaTuristas {
  Turista *inicio;
} ListaTuristas;

ListaTuristas *crearListaTuristas();

void registrarTurista(ListaTuristas *lista, char *pasaporte, char *nombre,
                      char *pais);

void agregarLugarFavorito(ListaTuristas *lista, char *pasaporte,
                          char *nombre_lugar);

void mostrarTuristasPorPais(ListaTuristas *lista, char *paisBuscado);

char *leerValidarTuristas(int tipo);



#endif
