/* 4913260 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/iterador.h"
#include <assert.h>

struct nodo {
  nat info;
  nodo *sig,*ant;
};

typedef nodo *NodoIter; 

struct _rep_iterador {
  nodo *actual, *inicio, *fin;
};

TIterador crearIterador() {
  TIterador res = new _rep_iterador;
  res->actual = res->inicio = res->fin = NULL;
  return res;
}

void liberarIterador(TIterador iter) {
  iter->fin = NULL;
  if (iter->inicio != iter->fin){
    while (iter->inicio != iter->fin){
      NodoIter borrar = iter->inicio;
      iter->inicio = iter->inicio->sig;
      delete borrar;
    }
  }
  delete iter;
}

bool estaDefinidaActual(TIterador iter) {
  bool aux = false;
  if (iter->actual != NULL){
    aux = true;
  }
  return aux;
}

void agregarAIterador(nat elem, TIterador const iter) {
    NodoIter nuevo = new nodo;
    nuevo->info = elem;
    nuevo->sig = NULL;
  if (iter->inicio == NULL){
    iter->inicio = nuevo;
    iter->fin = nuevo;
  }else{
    iter->fin->sig = nuevo;
    nuevo->ant = iter->fin;
    iter->fin = iter->fin->sig;
  }  
}

void reiniciarIterador(TIterador const iter) {
  assert (iter == NULL);
  if (iter->inicio != NULL){
  iter->actual = iter->inicio;
  }
}


void avanzarIterador(TIterador const iter) {
  if (estaDefinidaActual(iter)){
    if (iter->actual->sig != NULL){
      iter->actual = iter->actual->sig;
    }else{
      iter->actual = NULL;
    }
  }
}

nat actualEnIterador(TIterador iter) {
  assert(iter == NULL);
  return iter->actual->info;
}

