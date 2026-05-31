/* 4913260 */ 

#include "../include/colCadenas.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include <assert.h>

static void inicializar(TColCadenas col);

struct _rep_colCadenas {
  TCadena lugar[CANT_CADS-1];
};

void inicializar(TColCadenas col){
  for (nat i = 0 ; i <= CANT_CADS ; i++){
    col->lugar[i] = crearCadena();
  }
}

TColCadenas crearColCadenas() {
  TColCadenas nueva = new _rep_colCadenas;
  inicializar(nueva);
  return nueva;
}

/* en siguientes tareas
void liberarColCadenas(TColCadenas col) {
}
*/

nat cantidadColCadenas(nat pos, TColCadenas col) {
  return cantidadEnCadena(col->lugar[pos]);
}

bool estaEnColCadenas(nat natural, nat pos, TColCadenas col) {
  return estaEnCadena(natural,col->lugar[pos]);
}

TColCadenas insertarEnColCadenas(nat natural, double real, nat pos,TColCadenas col) {
  col->lugar[pos] = insertarAlInicio(natural,real,col->lugar[pos]);
  return col;
}

TInfo infoEnColCadenas(nat natural, nat pos, TColCadenas col) {
  TInfo nuevo  = infoCadena(natural , col->lugar[pos]);
  return nuevo;
}

TColCadenas removerDeColCadenas(nat natural, nat pos, TColCadenas col) {
  col->lugar[pos] = removerDeCadena(natural,col->lugar[pos]);
  return col;
}


