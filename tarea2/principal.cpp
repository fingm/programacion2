/*
  Módulo principal de la tarea 2.

Intérprete de comandos para probar los módulos.

Están creados una TCadena 'cad', una TColCadenas 'colCads' y un TIterador 'iter'.

Cada comando tiene un nombre y una secuencia (posiblemente vacía) de parámetros.
Se asume que los comandos están bien formados. Esto implica que:
- el nombre es uno de los descritos más abajo;
- la cantidad y tipo de los parámetros cumplen con lo requerido.

Si un parámetro debe ser de tipo TInfo su formato cumple con lo descrito en
'infoATexto' del módulo 'info''.


El comando
Fin
termina el programa

El comando
# comentario
imprime comentario.

El comando
reiniciar
libera la memoria asignada a 'cad', 'colCads' e 'iter' y los vuelve a crear.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#include "include/aplicaciones.h"
#include "include/iterador.h"
#include "include/cadena.h"
#include "include/colCadenas.h"
#include "include/info.h"
#include "include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#define MAX_PALABRA 32
#define MAX_LINEA 256

// programa principal
int main() {

  TIterador iter = crearIterador();
  TColCadenas colCads = crearColCadenas();
  TCadena cad = crearCadena();

  char restoLinea[MAX_LINEA + 1];
  char nom_comando[MAX_PALABRA];

  int cont_comandos = 0;
  bool salir = false;
  while (!salir) {
    // mostrar el prompt
    cont_comandos++;
    printf("%u>", cont_comandos);

    // leer el comando
    leerChars(nom_comando);

    // procesar el comando
    if (0 == strcmp(nom_comando, "Fin")) {
      salir = true;
      printf("Fin.\n");
      // comentario
    } else if (0 == strcmp(nom_comando, "#")) {
      leerRestoLinea(restoLinea);
      printf("# %s.\n", restoLinea);

      // operaciones de aplicaciones
    } else if (0 == strcmp(nom_comando, "insertarAlFinal")) {
      nat natural = leerNat();
      double real = leerDouble();
      cad = insertarAlFinal(natural, real, cad);
      printf("Se insertó (%d,%4.2lf) al final de la cadena.\n", natural, real);

    } else if (0 == strcmp(nom_comando, "removerPrimero")) {
      assert(cantidadEnCadena(cad) > 0);
      cad = removerPrimero(cad);
      printf("Se removió el primer elemento de la cadena.\n");
      
    } else if (0 == strcmp(nom_comando, "copiaCadena")) {
      TCadena copia = copiaCadena(cad);
      imprimirCadena(copia);
      liberarCadena(copia);
      
    } else if (0 == strcmp(nom_comando, "reversoDeIterador")) {
      TIterador reverso = reversoDeIterador(iter);
      reiniciarIterador(reverso);
      if (estaDefinidaActual(iter))
	printf("Error: la posición de iter no debe estar definida.\n");
      while (estaDefinidaActual(reverso)) {
	printf("%u ", actualEnIterador(reverso));
	avanzarIterador(reverso);
      }
      printf("\n");
      liberarIterador(reverso);
      
      // operaciones de iterador

    } else if (0 == strcmp(nom_comando, "agregarAIterador")) {
      nat elem = leerNat();
      /*iter = */agregarAIterador(elem, iter);
      printf("Agregando %u a it.\n", elem);

    } else if (0 == strcmp(nom_comando, "reiniciarIterador")) {
      /*iter = */reiniciarIterador(iter);
      printf("Reiniciando it.\n");

    } else if (0 == strcmp(nom_comando, "avanzarIterador")) {
      /*iter = */avanzarIterador(iter);
      printf("Avanzando en it.\n");

    } else if (0 == strcmp(nom_comando, "actualEnIterador")) {
      assert(estaDefinidaActual(iter));
      printf("El actual de it es %d.\n", actualEnIterador(iter));

    } else if (0 == strcmp(nom_comando, "estaDefinidaActual")) {
      printf("Actual de it %s definida.\n",
             estaDefinidaActual(iter) ? "está" : "NO está");
      
      // operaciones de cadena

    } else if (0 == strcmp(nom_comando, "cantidadEnCadena")) {
      printf("La cantidad es %u.\n", cantidadEnCadena(cad));

    } else if (0 == strcmp(nom_comando, "estaEnCadena")) {
      nat natural = leerNat();
      printf("%u %s en la cadena.\n", natural,
             (estaEnCadena(natural, cad)) ? "está" : "no está");

    } else if (0 == strcmp(nom_comando, "insertarAlInicio")) {
      nat natural = leerNat();
      double real = leerDouble();
      cad = insertarAlInicio(natural, real, cad);
      printf("Se insertó (%d,%4.2lf) al inicio de la cadena.\n", natural, real);
      
    } else if (0 == strcmp(nom_comando, "primeroEnCadena")) {
      assert(cantidadEnCadena(cad) > 0);
      printf("El primero es ");
      imprimirInfo(primeroEnCadena(cad));
      printf("\n");

    } else if (0 == strcmp(nom_comando, "infoCadena")) {
      nat natural = leerNat();
      assert(estaEnCadena(natural, cad));
      printf("El elemento es ");
      imprimirInfo(infoCadena(natural, cad));
      printf("\n");

    } else if (0 == strcmp(nom_comando, "cadenaSiguiente")) {
      nat sigs = leerNat();
      TCadena siguiente = cad;
      for (nat i = 0; i < sigs; i++)
	siguiente = cadenaSiguiente(siguiente);
      imprimirCadena(siguiente);

    } else if (0 == strcmp(nom_comando, "removerDeCadena")) {
      nat natural = leerNat();
      assert(estaEnCadena(natural, cad));
      cad = removerDeCadena(natural, cad);
      printf("Se removió la primera aparición de %u de la cadena.\n", natural);

    } else if (0 == strcmp(nom_comando, "imprimirCadena")) {
      imprimirCadena(cad);

      // operaciones de colCadenas
    } else if (0 == strcmp(nom_comando, "cadenaDeColCadenas")) {
      nat pos = leerNat();
      assert((0 <= pos) && (pos < CANT_CADS));
      printf("La cadena %u es :", pos );
      imprimirCadena(cadenaDeColCadenas(pos, colCads));
      
    } else if (0 == strcmp(nom_comando, "cantidadColCadenas")) {
      nat pos = leerNat();
      assert((0 <= pos) && (pos < CANT_CADS));
      printf("La cantidad en la cadena %u es %u.\n", pos, cantidadColCadenas(pos, colCads));
      
    } else if (0 == strcmp(nom_comando, "estaEnColCadenas")) {
      nat natural = leerNat();
      nat pos = leerNat();
      assert((0 <= pos) && (pos < CANT_CADS));
      printf("%u %s en la cadena %u.\n", natural,
             (estaEnColCadenas(natural, pos, colCads)) ? "está" : "no está",
             pos);

    } else if (0 == strcmp(nom_comando, "insertarEnColCadenas")) {
      nat natural = leerNat();
      double real = leerDouble();
      nat pos = leerNat();
      assert((0 <= pos) && (pos < CANT_CADS));
      colCads = insertarEnColCadenas(natural, real, pos, colCads);
      printf("Se insertó (%u,%4.2lf) en la cadena %u.\n", natural, real, pos);

    } else if (0 == strcmp(nom_comando, "infoEnColCadenas")) {
      nat natural = leerNat();
      nat pos = leerNat();
      assert((0 <= pos) && (pos < CANT_CADS));
      assert(estaEnColCadenas(natural, pos, colCads));
      printf("La primera aparición de %u en la cadena %u es ", natural, pos);
      imprimirInfo(infoEnColCadenas(natural, pos, colCads));
      printf("\n");

    } else if (0 == strcmp(nom_comando, "removerDeColCadenas")) {
      nat natural = leerNat();
      nat pos = leerNat();
      assert((0 <= pos) && (pos < CANT_CADS));
      assert(estaEnColCadenas(natural, pos, colCads));
      colCads = removerDeColCadenas(natural, pos, colCads);
      printf("Se removió la primera aparición de %d de la cadena %d.\n",
             natural, pos);

    } else if (0 == strcmp(nom_comando, "reiniciarEstructuras")) {
      liberarIterador(iter);
      iter = crearIterador();
      liberarCadena(cad);
      cad = crearCadena();
      liberarColCadenas(colCads);
      colCads = crearColCadenas();
      printf("Estructuras reiniciadas.\n");
      
    } else {
      printf("Comando no reconocido.\n");
    } // if
    fgets(restoLinea, MAX_LINEA + 1, stdin);
  } // while

  liberarIterador(iter);
  liberarCadena(cad);
  liberarColCadenas(colCads);
  return 0;
} // main
