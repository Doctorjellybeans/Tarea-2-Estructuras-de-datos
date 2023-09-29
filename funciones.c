#include "funciones.h"
#include "turistas.h"
#include "ubicaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funcion exportar archivo .CSV
// Function to export turistas data to a CSV file
void exportarTurista(ListaTuristas *lista, const char *Nombre_archivoTuris) {
  if (lista == NULL) {
    return;
  }

  FILE *turistafile = fopen(Nombre_archivoTuris, "w");
  if (turistafile == NULL) {
    printf("error al abrir el archivo");
    return;
  }
  fprintf(turistafile, "Pasaporte,Nombre,País,Lugares Favoritos\n");

  Turista *current = lista->inicio;
  while (current != NULL) {

    fprintf(turistafile, "%s,%s,%s", current->pasaporte, current->nombre,
            current->pais);
    LugarFavorito *currentlugar = current->lugaresFavoritos;
    while (currentlugar != NULL) {

      fprintf(turistafile, "%s", currentlugar->lugar);
      currentlugar = currentlugar->siguiente;
      if (currentlugar != NULL) {

        fprintf(turistafile, ";");
      }
    }
    fprintf(turistafile,"\n");
    current=current->siguiente;
  }
  printf("Exportacion exitosa\n");
  fclose(turistafile);
}

void exportarpuntos(TablaHash **tabla,const char *nombre_archivoPts){
  FILE *puntosIntfile=fopen(nombre_archivoPts,"w");
  if(puntosIntfile==NULL){
    return;
  }
  fprintf(puntosIntfile, "Nombre,Tipo,Dirección,Horario,Descripción\n");
  for(int i=0 ;i<(*tabla)->capacidad;i++){
    NodoUbicaciones *temp = (*tabla)->tabla[i].inicio;
    while(temp!=NULL){
      fprintf(puntosIntfile,"%s,%s,%s",temp->punto.nombre,temp->punto.tipo,temp->punto.horario);
      fprintf(puntosIntfile,"%s\n",temp->punto.descripcion);
      temp=temp->siguiente;
    }
    
  }
  
  fclose(puntosIntfile);
}

/*void importarTuristas(ListaTuristas *lista) {
  if (lista == NULL) {
    return;
  }
  char Nombre_archivoTuris[50];
  printf("Ingrese el nombre del archivo del archivo de turistas:\n ");
  scanf("%[^\n]", Nombre_archivoTuris);
  getchar();
  FILE *listaturista = fopen(Nombre_archivoTuris, "r");
  if (listaturista == NULL) {
    printf("error al abrir el archivo");
    return;
  }
  char header[1024];
  fgets(header, sizeof(header), listaturista);

  while (fgets(header, sizeof(header), listaturista)) {
    char Pasaporte[50];
    char Nombre[50];
    char Pais[50];
    char Lugaresfav[150];
    sscanf(header, "%[^,],%[^,],%[^,],%[^\n]", Pasaporte, Nombre, Pais,
           Lugaresfav);

    char *token = strtok(Lugaresfav, ";"); // a

    while (token != NULL) {
      char LugarFav[50];
      sscanf(token, "%49[^\n]", LugarFav);
      agregarLugarFavorito(lista, Pasaporte, LugarFav);
      token = strtok(NULL, ";");
      printf("Lugaresfav: %s\n", LugarFav);
    }

    printf("Pasaporte: %s\n", Pasaporte);
    printf("Nombre: %s\n", Nombre);
    printf("Pais: %s\n", Pais);

    registrarTurista(lista, Pasaporte, Nombre, Pais);
  }
  fclose(listaturista);
}*/

void importarTuristas(ListaTuristas *lista) {
  if (lista == NULL) {
    return;
  }
  char Nombre_archivoTuris[50];
  printf("Ingrese el nombre del archivo del archivo de turistas:\n ");
  scanf("%[^\n]", Nombre_archivoTuris);
  getchar();
  FILE *listaturista = fopen(Nombre_archivoTuris, "r");
  if (listaturista == NULL) {
    printf("error al abrir el archivo");
    return;
  }
  char header[1024];
  fgets(header, sizeof(header), listaturista);

  while (fgets(header, sizeof(header), listaturista)) {
    char Pasaporte[50];
    char Nombre[50];
    char Pais[50];
    char Lugaresfav[150];
    sscanf(header, "%[^,],%[^,],%[^,],%[^\n]", Pasaporte, Nombre, Pais,
           Lugaresfav);

    registrarTurista(lista, Pasaporte, Nombre, Pais);
    
    char *token = strtok(Lugaresfav, ";"); // a

    while (token != NULL) {
      char LugarFav[50];
      sscanf(token, "%49[^\n]", LugarFav);
      agregarLugarFavorito(lista, Pasaporte, LugarFav);
      token = strtok(NULL, ";");
    }

  }
  fclose(listaturista);
}

void importarUbicaciones(TablaHash **tabla) {
  if (tabla == NULL) {
    return;
  }
  char Nombre_archivoPts[50];
  printf("Ingrese el nombre del archivo del archivo de puntos de interes:\n ");
  scanf("%[^\n]", Nombre_archivoPts);
  getchar();
  char header[1024];
  // Puntos de interes
  FILE *ArchivoPts = fopen(Nombre_archivoPts, "r");
  if (ArchivoPts == NULL) {
    printf("error al abrir el archivo");
    return;
  }
  fgets(header, sizeof(header), ArchivoPts);
  while (fgets(header, sizeof(header), ArchivoPts)) {
    char nombre[50];
    char tipo[50];
    char direccion[50];
    char horario[50];
    char descripcion[50];
    sscanf(header, "%[^,],%[^,],%[^,],%[^,],%[^\n]", nombre, tipo, direccion,
           horario, descripcion);
    registrarPuntoDeInteres(tabla, nombre, tipo, direccion, horario,
                            descripcion);
  }
  fclose(ArchivoPts);
  printf("FINALIZADO\n");
}

// Funcion importar archivo .CSV
/*void import_csv(ListaTuristas *lista, TablaHash **tabla,
                const char *Nombre_archivoTuris, const char *Nombre_archivoPts)
{ if (lista == NULL || tabla == NULL) { printf("no existe tabla o lista");
  }
  printf("ENTRO A LA FUNCION\n");

  FILE *listaturista = fopen(Nombre_archivoTuris, "r");
  if (listaturista == NULL) {
    printf("error al abrir el archivo");
    return;
  }
  char header[1024];
  fgets(header, sizeof(header), listaturista);

  // Turistas
  while (fgets(header, sizeof(header), listaturista)) {
    char Pasaporte[50];
    char Nombre[50];
    char Pais[50];
    char Lugaresfav[150];
    sscanf(header, "%[^,],%[^,],%[^,],%[^\n]", Pasaporte, Nombre, Pais,
           Lugaresfav);

    char *token = strtok(Lugaresfav, ";"); // a

    while (token != NULL) {
      char LugarFav[50];
      sscanf(token, "%49[^\n]", LugarFav);
      agregarLugarFavorito(lista, Pasaporte, LugarFav);
      token = strtok(NULL, ";");
      printf("Lugaresfav: %s\n", LugarFav);

    }

    printf("Pasaporte: %s\n", Pasaporte);
    printf("Nombre: %s\n", Nombre);
    printf("Pais: %s\n", Pais);

    registrarTurista(lista, Pasaporte, Nombre, Pais);
  }
  fclose(listaturista);

  // Puntos de interes
  FILE *ArchivoPts = fopen(Nombre_archivoPts, "r");
  if (ArchivoPts == NULL) {
    printf("error al abrir el archivo");
    return;
  }
  fgets(header, sizeof(header), ArchivoPts);
  while (fgets(header, sizeof(header), ArchivoPts)) {
    char nombre[50];
    char tipo[50];
    char direccion[50];
    char horario[50];
    char descripcion[50];
    sscanf(header, "%[^,],%[^,],%[^,],%[^,],%[^\n]", nombre, tipo, direccion,
           horario, descripcion);
    registrarPuntoDeInteres(tabla, nombre, tipo, direccion, horario,
                            descripcion);
  }
  fclose(ArchivoPts);
  printf("FINALIZADO\n");
}
*/