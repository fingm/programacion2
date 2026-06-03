/* 4913260 */ 

#include "../include/colCadenas.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include <assert.h>

struct _rep_colCadenas {
  TCadena lugar[CANT_CADS+1];
};

TColCadenas crearColCadenas() {
  return NULL;
}

void liberarColCadenas(TColCadenas col) {
  if (col != NULL){
    for (int i = 0; i<= CANT_CADS-1; i++){
      liberarCadena(col->lugar[i]);
    }
    delete col;
  }
}

TCadena cadenaDeColCadenas(nat pos, TColCadenas col) {
  if (col != NULL){
    TCadena res = col->lugar[pos];
    return res;
  }else{
    return NULL;
  }
}

nat cantidadColCadenas(nat pos, TColCadenas col) {
  if (col == NULL || col->lugar[pos] == NULL){
    return 0;
  }else{
    return cantidadEnCadena(col->lugar[pos]);
  }
}

bool estaEnColCadenas(nat natural, nat pos, TColCadenas col) {
  bool aux = false;
  if (col != NULL && col->lugar[pos] != NULL && estaEnCadena(natural,col->lugar[pos])){
    aux = true;
  }
  return aux;
}

TColCadenas insertarEnColCadenas(nat natural, double real, nat pos,TColCadenas col) {
  if (col == NULL){
    col = new _rep_colCadenas;
    for (nat i =0; i<= CANT_CADS-1; i++){
      col->lugar[i] = NULL;
    }
  }
  col->lugar[pos] = insertarAlInicio(natural,real,col->lugar[pos]);  
  return col;
}

TInfo infoEnColCadenas(nat natural, nat pos, TColCadenas col) {
    TInfo res = infoCadena(natural,col->lugar[pos]);
    return res;
}

TColCadenas removerDeColCadenas(nat natural, nat pos, TColCadenas col) {
  if (cantidadColCadenas(pos,col) == 1){
    liberarCadena(col->lugar[pos]);
    col->lugar[pos] = NULL;
  }else{
      col->lugar[pos] = removerDeCadena(natural,col->lugar[pos]);
  }
  return col;
}
