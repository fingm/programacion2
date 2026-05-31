/* 4913260 */ 

#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include <assert.h>

// los elementos se mantienen entre 0 y cantidad - 1, incluidos
struct _rep_cadena {
  TInfo dato[L+1];
  nat longitud;
};

static bool esVaciaCadena(TCadena cad);


TCadena crearCadena() {
  TCadena nueva = new _rep_cadena;
  nueva->longitud = 0;
  return nueva;
}

/* en siguientes tareas
void liberarCadena(TCadena cad) {
}
*/

nat cantidadEnCadena(TCadena cad) {
  if (!esVaciaCadena(cad)){
    return cad->longitud;
  }else{
    return 0;
  }
}

bool esVaciaCadena(TCadena cad){
  return cad->longitud == 0;
} 

bool estaEnCadena(nat natural, TCadena cad) {
  bool aux = false;  
  if (!esVaciaCadena(cad)){
    if (natInfo(cad->dato[0])== natural){
      aux = true;
    }else{
      nat i=0;
      aux = false;
      while (i <= cad->longitud-1 && !aux){
        if(natInfo(cad->dato[i]) == natural){
          aux = true;
        }
        i++;
      }
    }
  }
  return aux;
}

TCadena insertarAlInicio(nat natural, double real, TCadena cad) {
    cad->longitud = cad->longitud +1;
    if (!esVaciaCadena(cad)){
      for (int i = cad->longitud; i>=0; i--){
        cad->dato[i] = cad->dato[i-1];
      }
    }
    cad->dato[0] = crearInfo(natural,real);
  return cad;
}

TInfo infoCadena(nat natural, TCadena cad) {
  nat contador = 0;
  bool encontrado = false;
  while (contador <= cad->longitud-1){
    if (natInfo(cad->dato[contador]) == natural && !encontrado){
      encontrado = true;
      return copiaInfo(cad->dato[contador]);
    }
    contador ++;
  }
  return NULL;
}

TCadena removerDeCadena(nat natural, TCadena cad) {
  if (!esVaciaCadena(cad)){
    nat contador =0;
    bool encontrado = false;
    while (!encontrado){
      if (natInfo(cad->dato[contador]) == natural){
        encontrado = true;
        for (nat cont = contador; cont <= cad->longitud-1; cont++ ){
          cad->dato[cont] = cad->dato[cont+1];
        }
      }
      contador++;
    }
  }
  cad->longitud--;
  return cad;
}

void imprimirCadena(TCadena cad){
  if (!esVaciaCadena(cad)){       
    for (nat i=0 ; i<=cad->longitud-1; i++){
      printf("(%d,%4.2lf)",natInfo(cad->dato[i]),realInfo(cad->dato[i]));
    }
    printf("\n");
  }else{
    printf("\n");
  }
}
 