/*
  Módulo de definición de 'aplicaciones'.


  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */


#ifndef _APLICACIONES_H
#define _APLICACIONES_H

#include "cadena.h"
#include "iterador.h"



/*
  Inserta al final de 'cad' un elemento cuyos componentes son 'natural' y
  'real'.
  Devuelve 'cad'. 
  No se recorre la cadena.
 */
TCadena insertarAlFinal(nat natural, double real, TCadena cad);

/*
  Remueve el primer elemento de 'cad'.
  Se libera la memoria asignada al mismo.
  Devuelve 'cad'.
  Precondición: cantidadEnCadena(cad) > 0.
  No se recorre la cadena.
 */
TCadena removerPrimero(TCadena cad);

/*
  Devuelve una copia de 'cad'.
  El resultado no comparte memoria con el parámetro. 
 */
TCadena copiaCadena(TCadena cad); 


/*
  Devuelve un TIterador con los mismos elementos que iter pero 
  en sentido opuesto.
  El resultado no comparte memoria con el parámetro.
  Cada elemento de 'iter' solo se visita una vez.
  No se puede usar estructuras auxiliares.
  Poscondición: ! estaDefinidaActual(iter)
  (al terminar la posición actual de iter queda no definida)
 */
TIterador reversoDeIterador(TIterador iter);

#endif
