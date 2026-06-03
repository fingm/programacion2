/* 4913260 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cola.h"
#include "../include/cadena.h"

struct nodoCola{
    TInfo dato;
    nodoCola *sig;
};

typedef nodoCola *nodo;

struct _rep_cola {
    nodo primero;
    nodo ultimo;
    nat cant;
};

TCola crearCola() {
    TCola res = new _rep_cola;
    res->primero = res->ultimo = NULL;
    res->cant = 0;
    return res;
}

void liberarCola(TCola c) {
    if (c != NULL){
        while (c->cant > 0){
            nodo borrar = c->primero;
            liberarInfo(borrar->dato);
            c->primero = c->primero->sig;
            delete borrar;
            c->cant--;
        }
        c->primero = NULL;
        c->ultimo = NULL;
        delete c;
    }
}

nat cantidadEnCola(TCola c) {
    if (c == NULL){
        return 0 ;
    }else{
        return c->cant;
    }
}

TCola encolar(TInfo info, TCola c) {
    nodo nuevo = new nodoCola;
    nuevo->dato = copiaInfo(info);
    nuevo->sig = NULL;
    if (c->cant == 0){
        c->primero = nuevo;
        c->ultimo = nuevo;
    }else{
        c->ultimo->sig = nuevo;
        c->ultimo = nuevo;
    }
    c->cant++;
    return c;
}

TInfo frente(TCola c) {
    return c->primero->dato;
}

TCola desencolar(TCola c) {
    nodo borrar = c->primero;
    c->primero = c->primero->sig;
    if (c->primero == NULL){
        c->ultimo = NULL;
    }
    c->cant--;
    liberarInfo(borrar->dato);
    delete borrar;
    return c;
}
