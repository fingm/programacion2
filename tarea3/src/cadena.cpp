/* 4913260 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cadena.h"
#include <assert.h>

struct _rep_cadena {
  TInfo dato;
  TCadena sig;
  TCadena ant;
};

TCadena crearCadena() {
  return NULL;
}

void liberarCadena(TCadena cad) {
// printf("\n\n SE EJECUTA LIBERARCADENA\n\n");
  if (cad != NULL){
    if (cad->sig == NULL){
      liberarInfo(cad->dato);
      delete cad;
    }else{
      TCadena iter = cad->sig;
      while (iter->dato != cad->dato){
        TCadena borrar = iter;
        iter = iter->sig;
        liberarInfo(borrar->dato);
        delete borrar;
      }
      liberarInfo(iter->dato);
      delete iter;
    }
  }
}

nat cantidadEnCadena(TCadena cad) {
 // printf("\n\n SE EJECUTA CANTIDADENCADENA\n\n");
  nat contador = 0;
  if (cad != NULL){
    if (cad->sig == NULL){
      contador++;
    }else if (cad->sig != NULL){
      TCadena iter = cad->sig;
      contador++;
      while(iter->dato != cad->dato){
        iter = iter->sig;
        contador++;
      }
    }
  }
  return contador;
}

bool estaEnCadena(nat natural, TCadena cad) {
 //printf("\n\n SE EJECUTA ESTAENCADENA\n\n");
  bool aux = false;
  if (cad != NULL){
    if ( natInfo(cad->dato) ==  natural){
      aux = true;
    }else if (cad->ant != NULL && natInfo(cad->ant->dato) ==  natural){
      aux = true;
    }else if (cad->sig != NULL){
      TCadena iter = cad->sig;
      while (iter->dato != cad->dato &&  natInfo(iter->dato) !=  natural){
        iter = iter->sig;
      }
      if (natInfo(iter->dato) ==  natural){
        aux = true;
      }
    }
  }
  return aux;
}

TCadena insertarAlInicio(nat natural, double real, TCadena cad) {
 // printf("\n\n SE EJECUTA INSERTARENCADENA\n\n");
  TCadena nodo = new _rep_cadena;
  nodo->dato = crearInfo(natural,real);
  if (cad == NULL){
    cad = nodo;
    cad->sig = NULL;
    cad->ant = NULL;
  }else{
    if (cad->sig == NULL){
      TCadena aux = cad;
      cad = nodo;
      aux->ant = nodo;
      cad->sig = aux;
      cad->ant = aux;
      aux->sig = cad;
      aux = NULL;
    }else{
      TCadena ini = cad;
      TCadena fin = cad->ant;
      cad = nodo;
      cad->sig = ini;
      ini->ant = cad;
      cad->ant = fin;
      fin->sig = cad;
      ini= NULL;
      fin = NULL;
    }
  }
  return cad;
}

TInfo infoCadena(nat natural, TCadena cad) {
 // printf("\n\n SE EJECUTA INFOCADENA\n\n");
  if (natInfo(cad->dato) == natural){
    return cad->dato;
  }else{
    TCadena iter = cad->sig;
    while(natInfo(iter->dato) != natural){
      iter = iter->sig;
    }return iter->dato;
  }
}

TInfo primeroEnCadena(TCadena cad) {
 // printf("\n\n SE EJECUTA PRIMEROENCADENA\n\n");
  return cad->dato;
}

TCadena cadenaSiguiente(TCadena cad) {
 // printf("\n\n SE EJECUTACADENASIGUIENTE\n\n");
  if (cad != NULL && cad->sig != NULL){
    cad = cad->sig;
  }  
  return cad;
}

TCadena removerDeCadena(nat natural, TCadena cad) {
  if (cad->sig == NULL){
    liberarCadena(cad);
    cad = NULL;
  }else{
    if (natInfo(cad->dato) == natural){
      TCadena borrar = cad;
      TCadena fin  = cad->ant;
      cad = cad->sig;
      cad->ant = cad->ant->ant;
      fin->sig = fin->sig->sig;
      liberarInfo(borrar->dato);
      delete borrar;
      fin = NULL;
      borrar = NULL;
    }else if (natInfo(cad->ant->dato) == natural){
      TCadena borrar = cad->ant;
      TCadena ant = cad->ant->ant;
      ant->sig = ant->sig->sig;
      cad->ant = cad->ant->ant;
      liberarInfo(borrar->dato);
      delete borrar;
      ant = NULL;
    }else{
      TCadena iter = cad;
      while (natInfo(iter->sig->dato) != natural){
        iter = iter->sig;
      }
      TCadena borrar = iter->sig;
      TCadena sig = iter->sig->sig;
      iter->sig = iter->sig->sig;
      sig->ant = sig->ant->ant;
      liberarInfo(borrar->dato);
      delete borrar;
      iter = NULL;
      sig = NULL;
    }
  }

  return cad;
}

void imprimirCadena(TCadena cad) {
 // printf("\n\n SE EJECUTA IMPRIMIRCADENA\n\n");
  if (cad != NULL){
    printf("(%d,%.2f)",natInfo(cad->dato),realInfo(cad->dato));
    if (cad->sig != NULL){
      TCadena aux = cad->sig;
      while (aux->dato != cad->dato){
      printf("(%d,%.2f)",natInfo(aux->dato),realInfo(aux->dato));
      aux = aux->sig;
      }
    }
  }
  printf("\n");  
}