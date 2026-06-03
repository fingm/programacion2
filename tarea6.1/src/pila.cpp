/* 4913260 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/pila.h"
#include "../include/cadena.h"
#include <assert.h>

struct _rep_pila {
    TCadena cad;
    nat tope;
};

TPila crearPila() {
    TPila res = new _rep_pila;
    res->tope = 0;
    res->cad = crearCadena();
    return res;
}

void liberarPila(TPila p) {
    if (p != NULL){
        liberarCadena(p->cad);
        delete p;
    }
}

nat cantidadEnPila(TPila p) {
    if (p == NULL){
        return 0;
    }else{
        return p->tope;
    }
}

TPila apilar(TInfo info, TPila p) {
    if (p == NULL){
        p = new _rep_pila;
        p->cad = insertarAlInicio(natInfo(info) , realInfo(info) , p->cad);
        p->tope ++;
    }else{
        p->cad = insertarAlInicio(natInfo(info) , realInfo(info) , p->cad);
        p->tope ++;
    }
    return p;
}

TInfo cima(TPila p) {
    return primeroEnCadena(p->cad);
}

TPila desapilar(TPila p) {
    p->cad = removerPrimero(p->cad);
    p->tope--;
    return p;
}