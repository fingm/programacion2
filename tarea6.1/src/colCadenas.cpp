/* 4913260 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colCadenas.h"

#include <assert.h>

struct _rep_colCadenas {
  nat tamanio;
  TCadena *lugar;
};

TColCadenas crearColCadenas(nat tamanio) {
  TColCadenas res = new _rep_colCadenas;  
  TCadena *arr;
  arr = new TCadena[tamanio];
  for (nat i = 0; i <= tamanio-1; i++){
    arr[i] = NULL;
  }
  res->tamanio = tamanio;
  res->lugar   = arr;
  return res;
}

void liberarColCadenas(TColCadenas col) {
  for (nat i = 0 ; i <= col->tamanio -1 ; i++){
    liberarCadena(col->lugar[i]);
  }
  delete[] col->lugar;
  delete col;

}

nat tamanioColCadenas(TColCadenas col) { 
  return col->tamanio;
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
  if (pos <= col->tamanio){
    if (col != NULL && col->lugar[pos] != NULL && estaEnCadena(natural,col->lugar[pos])){
      aux = true;
    }
  }
  return aux;
}

TColCadenas insertarEnColCadenas(nat natural, double real, nat pos,TColCadenas col) {
  assert(col == NULL);
  if (pos <= col->tamanio){
    col->lugar[pos] = insertarAlInicio(natural,real,col->lugar[pos]);  
  }
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