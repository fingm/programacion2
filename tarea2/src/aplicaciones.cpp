/* 4913260 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
#include "../include/cadena.h"
#include "../include/iterador.h"
#include <assert.h>

TCadena insertarAlFinal(nat natural, double real, TCadena cad) {
  if(cad == NULL){
    cad = crearCadena();
    cad = insertarAlInicio(natural,real,cad);
  }else{
    cad = insertarAlInicio(natural,real,cad);
    cad = cadenaSiguiente( cad);
  }
return cad;
}

TCadena removerPrimero(TCadena cad) {
  if (cantidadEnCadena(cad) == 1){
    liberarCadena(cad);
    return NULL;
  }else{
    cad =  removerDeCadena(natInfo(primeroEnCadena(cad)),cad);

    return cad;
  }
}


TCadena copiaCadena(TCadena cad) {
if(cad != NULL){
  TCadena nueva = crearCadena();
  TCadena aux = cad;
  nueva = insertarAlInicio(natInfo(primeroEnCadena(cad)),realInfo(primeroEnCadena(cad)),nueva);
  aux = cadenaSiguiente(aux);
  while (aux  != cad){
    nueva = insertarAlFinal(natInfo(primeroEnCadena(aux)),realInfo(primeroEnCadena(aux)),nueva);
    aux = cadenaSiguiente(aux);
  }
  return nueva;
  }else{
    return NULL;
  }
}

TIterador pasoRecursivo(TIterador entrada,TIterador salida,nat s){
  if (estaDefinidaActual(entrada)){
    s = actualEnIterador(entrada);
    avanzarIterador(entrada);
    pasoRecursivo(entrada,salida,s);
    agregarAIterador(s,salida);
  }
  return salida;
}

TIterador reversoDeIterador(TIterador iter) {
  TIterador res = crearIterador();
  reiniciarIterador(iter);
  nat s = 0;
  res = pasoRecursivo(iter,res,s);
  return res;
}

