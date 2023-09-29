 Tareas_Estructuras_de_datos
# Aplicacion de Gestion de Informacion Turistica de una Ciudad
Integrantes:
- Vicente Rosales 21233477-4
- Alex Alfaro 

Esta aplicacion consiste en un programa en C capaz de gestionar la entrada y salida de datos recurrente de una aplicacion de informacion turistica.

Para eso se diseño un menu con las siguientes funcionalidades:

    1. Registrar un turista
    2. Agregar un lugar favorito a un turista
    3. Mostrar turistas por país
    4. Registrar un punto de interés
    5. Mostrar datos de un punto de interés
    6. Mostrar puntos de interés por tipo
    7. Eliminar un punto de interés
    8. Exportar datos de turistas / ubicaciones a archivo CSV
    9. Importar datos de turistas / ubicaciones desde un archivo .csv
    10. Salir

## Contribuciones individuales:
    
  - Vicente Rosales: Diseño e implementacion de las 7 principales funciones de la aplicacion.
  - nivelContribucion = 3;

  - Alex alfaro: Diseño e implementacion del menu y de las funciones de importacion e exportacion.
  - nivelContribucion = 3;

  - A ambos se les atribuye la depuracion del codigo y pruebas de estres.

## Bugs del codigo :
- Al agregar nuevos lugares a un turista es posible agregar lugares que no se han guardado previamente, la razon de esto es que la lista de turistas no se comunica con el mapa de ubicaciones a la hora de agregar nuevos lugares (No se implemento por mala gestion de tiempo ya que nos dimos cuenta a ultima hora el dia de la entrega) 
  
- Mas Bugs o errores o glitches no se han encontrado

Pasos para ejecutar el programa:
  1. Acceda al link adjuntado en el entregable
     https://replit.com/join/hkjvponzsa-doctorjellybean
  3. Haga click en el boton Run
  4. En caso de que no funcione, utilice el comando "sh test.sh" en la Shell