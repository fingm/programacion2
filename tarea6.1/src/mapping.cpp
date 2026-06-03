/* 4913260 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/mapping.h"
#include "../include/cadena.h"
#include "../include/colCadenas.h"
#include <assert.h>

struct _rep_mapping {
    TCadena *arr; 
    nat tamanio;
    nat cantidad;
};

TMapping crearMap(nat M) {
    TMapping map = new _rep_mapping;
    map->tamanio = M;
    map->cantidad = 0;
    map->arr = new TCadena[M];
    for (nat i = 0; i <= M-1 ; i++){
        map->arr[i] = crearCadena();
    }
    return map;
}

bool esVacioMap(TMapping m){
    return m == NULL;
}

void liberarMap(TMapping map) {
    if (map != NULL){
        for (nat i = 0 ; i<= map->tamanio -1 ; i++){
            if (map->arr[i] != NULL){
                liberarCadena(map->arr[i]);
            }
        }
        delete [] map->arr;
        delete map;
    }
}

nat funcionHash(nat clave , TMapping map){
    nat pos;
    if (clave <= map->tamanio){
        pos = clave % map->tamanio;  
    }else{
        pos = clave % 7;
    }
    return pos;
}

TMapping asociarEnMap(nat clave, double valor, TMapping map) {
    if (map != NULL){
        nat pos = funcionHash(clave , map);
        map->arr[pos] = insertarAlFinal(clave , valor ,map->arr[pos]);
        map->cantidad++;
    }
    return map;
}

TMapping desasociarEnMap(nat clave, TMapping map) {
    if (map != NULL){
        nat pos = funcionHash(clave , map);
        map->arr[pos] = removerPrimero( map->arr[pos]);
        map->cantidad--;
    }
    return map;
}

bool esClaveEnMap(nat clave, TMapping map) { 
    nat pos = funcionHash(clave , map);
    return map->arr[pos] != NULL;
}

double valorEnMap(nat clave, TMapping map) {
    nat pos = funcionHash(clave , map);
    return realInfo(primeroEnCadena(map->arr[pos]));
}

bool estaLlenoMap(TMapping map) {
    return map->cantidad == map->tamanio;
}


