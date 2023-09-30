#include "turistas.h"
#include "ubicaciones.h"
#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  ListaTuristas *listaTuristas = crearListaTuristas();
  TablaHash *tablaUbicaciones = crearTabla(100);

  int opcion;
  char nombre[50], tipo[50], direccion[100], horario[50], descripcion[200];
  char pasaporte[10], nombreTurista[50], pais[50], nombreLugar[50];

  while (1) {
    printf("\n=========== MENU ===========\n");
    printf("1. Registrar un turista\n");
    printf("2. Agregar un lugar favorito a un turista\n");
    printf("3. Mostrar turistas por país\n");
    printf("4. Registrar un punto de interés\n");
    printf("5. Mostrar datos de un punto de interés\n");
    printf("6. Mostrar puntos de interés por tipo\n");
    printf("7. Eliminar un punto de interés\n");
    printf("8. Exportar datos a archivo CSV\n");
    printf("9. Importar datos desde archivo CSV\n");
    printf("10. Salir\n");
    printf("Ingrese la opción deseada: ");
    scanf("%d", &opcion);
    getchar();

    switch (opcion) {
    case 1:
      printf("Ingrese el pasaporte del turista: ");
      scanf("%[^\n]", pasaporte);
      getchar();
      printf("Ingrese el nombre del turista: ");
      scanf("%[^\n]", nombreTurista);
      getchar();
      printf("Ingrese el país del turista: ");
      scanf("%[^\n]", pais);
      getchar();
      registrarTurista(listaTuristas, pasaporte, nombreTurista, pais);
      break;

    case 2:
      printf("Ingrese el pasaporte del turista: ");
      scanf("%[^\n]", pasaporte);
      getchar();
      printf("Ingrese el nombre del lugar favorito: ");
      scanf("%[^\n]", nombreLugar);
      getchar();
      agregarLugarFavorito(listaTuristas, pasaporte, nombreLugar);
      break;

    case 3:
      printf("Ingrese el país para mostrar turistas: ");
      scanf("%[^\n]", pais);
      getchar();
      printf("\n");
      mostrarTuristasPorPais(listaTuristas, pais);
      break;

    case 4:
      printf("Ingrese el nombre del punto de interés: ");
      scanf("%[^\n]", nombre);
      getchar();
      printf("Ingrese el tipo del punto de interés: ");
      scanf("%[^\n]", tipo);
      getchar();
      printf("Ingrese la dirección del punto de interés: ");
      scanf("%[^\n]", direccion);
      getchar();
      printf("Ingrese el horario del punto de interés: ");
      scanf("%[^\n]", horario);
      getchar();
      printf("Ingrese la descripción del punto de interés: ");
      scanf("%[^\n]", descripcion);
      getchar();
      registrarPuntoDeInteres(&tablaUbicaciones, nombre, tipo, direccion,
                              horario, descripcion);
      break;

    case 5:
      printf("Ingrese el nombre del punto de interés: ");
      scanf("%[^\n]", nombre);
      getchar();
      printf("\n");
      mostrarDatosPuntoDeInteres(tablaUbicaciones, nombre);
      break;

    case 6:
      printf("Ingrese el tipo de punto de interés: ");
      scanf("%[^\n]", tipo);
      getchar();
      printf("\n");
      mostrarPuntosPorTipo(tablaUbicaciones, tipo);
      break;

    case 7:
      printf("Ingrese el nombre del punto de interés a eliminar: ");
      scanf("%[^\n]", nombre);
      getchar();
      eliminarPuntosDeInteres(&tablaUbicaciones, nombre);
      break;

    case 8:
      exportarTurista(listaTuristas,"archivo exportado.csv");
      exportarpuntos(&tablaUbicaciones,"archivo exportado puntos.csv");
      break;

    case 9:
      importarTuristas(listaTuristas);
      importarUbicaciones(&tablaUbicaciones);
      break;

    case 10:
      // Salir del programa
      return 0;

    default:
      printf("Opción no válida. Por favor, ingrese una opción válida.\n");
    }
  }
  return 0;
}
