#define FUNCIONES_H
#ifdef FUNCIONES_H
#include "turistas.h"
#include "ubicaciones.h"

void exportcsv(char Nombre_archivoTuris, char Nombre_archivoPts);

void importarTuristas(ListaTuristas *lista);

void importarUbicaciones(TablaHash **tabla);

void exportarTurista(ListaTuristas *lista, const char *Nombre_archivoTuris);

void exportarpuntos(TablaHash **tabla,const char *nombre_archivoPts);

#endif
