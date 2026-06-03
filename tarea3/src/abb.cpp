/* 4913260 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/abb.h"

struct _rep_abb {
    TInfo dato;
    TAbb izq;
    TAbb der;
};

TAbb crearAbb(){
     return NULL;
}

void liberarAbb(TAbb abb) {
    if (abb != NULL){
        liberarAbb(abb->izq);
        liberarAbb(abb->der);
        liberarInfo(abb->dato);
        delete abb;
        abb = NULL;
    }
}

bool esVacioAbb(TAbb abb) {
    return abb == NULL;
}

TAbb buscarSubarbol(nat elem, TAbb abb) {
    if (abb == NULL){
        return NULL;
    }else{
        if (natInfo(abb->dato) == elem){
            return abb;
        }else{
            while (abb != NULL && natInfo(abb->dato) != elem){
                if (elem < natInfo(abb->dato)){
                    abb = abb->izq;
                }else{
                    abb = abb->der;
                }
            }if (abb != NULL){
                return abb;
            }else{
                return NULL;
            }
        }
    }
}

TInfo raiz(TAbb abb) {
    if (abb != NULL){
        return abb->dato;
    }else{
        return NULL;
    }
}

TAbb izquierdo(TAbb abb) {
    if (abb->izq != NULL){
        return abb->izq;
    }else{
        return NULL;
    }
}

TAbb derecho(TAbb abb) {
   if (abb->der != NULL){
    return abb->der;         
   }else{
       return NULL;
   }
}

bool esHoja(TAbb abb){
    if (abb != NULL && derecho(abb) == NULL &&  izquierdo(abb) == NULL){
        return true;
    }else{
        return false;
    }
}

TInfo menorEnAbb(TAbb abb) {
    while (abb->izq != NULL){
        abb = abb->izq;
    }
    return abb->dato;
}

TInfo mayorEnAbb(TAbb abb) {
    while (abb->der != NULL){
        abb = abb->der;
    }
    return abb->dato;
}

TAbb consAbb(TInfo dato, TAbb izq, TAbb der) { 
    TAbb res = new _rep_abb;
    res->dato = dato;
    res->izq = izq;
    res->der = der;
    return res;
}

void insertarEnAbbAux(TInfo dato, TAbb &a){
    if (esVacioAbb(a)){
        a = new _rep_abb;
        a->dato = dato;
        a->der = a->izq = NULL;
    }else if (natInfo(dato) <  natInfo(a->dato)){
        insertarEnAbbAux(dato,a->izq);
    }else if (natInfo(dato) >  natInfo(a->dato)){
        insertarEnAbbAux(dato,a->der);
    }
}

TAbb insertarEnAbb(TInfo dato, TAbb abb) {
    insertarEnAbbAux(dato,abb);
    return abb;
}

TAbb concatenar (TAbb abb){
    TAbb aux_iz = izquierdo(abb);
    TAbb aux_dr = derecho(abb);
        if (aux_iz->dato == mayorEnAbb(aux_iz)){
        liberarInfo(abb->dato);
        delete abb;
        abb = NULL;
        abb = aux_iz;
        abb->der = aux_dr;
    }else{
        TAbb anterior = aux_iz;
        while (aux_iz->dato != mayorEnAbb(abb->izq)){
            anterior = aux_iz;
            aux_iz = aux_iz->der; 
        }
        if (aux_iz->izq == NULL){
            liberarInfo(raiz(abb));
            delete abb;
            abb = crearAbb();
            aux_iz->der = aux_dr;
            abb = aux_iz;
            anterior->der = NULL;
            abb->izq = anterior;
        }else{
            liberarInfo(raiz(abb));
            delete abb;
            abb = crearAbb();
            anterior->der = aux_iz->izq;
            abb = aux_iz;
            abb->izq = anterior;
            abb->der = aux_dr;
        }
    }
    return abb;
}

TAbb removerDeAbb(nat clave, TAbb abb) {
    if (natInfo(raiz(abb)) == clave){//--------------el nodo a borrar es la raiz---------
        if (esHoja(abb)){//--------------Si el arbol es hoja---------
            liberarInfo(raiz(abb));
            delete abb;
            abb = NULL;
        }else if (izquierdo(abb) == NULL){
            TAbb aux = derecho(abb);
            liberarInfo(raiz(abb));
            delete abb;
            abb = NULL;
            abb = aux;
        }else if (derecho(abb) == NULL){
            TAbb aux = izquierdo(abb);
            if (aux->dato == mayorEnAbb(aux)){
                liberarInfo(abb->dato);
                delete abb;
                abb = NULL;
                abb = aux;
            }else{
                TAbb anterior = aux;
                while (aux->dato != mayorEnAbb(abb->izq)){
                    anterior = aux;
                    aux = aux->der; 
                }
                liberarInfo(abb->dato);
                delete abb;
                abb = NULL;
                anterior->der = NULL;
                abb = aux;
                aux->izq = anterior;
            }
        }else if (derecho(abb) != NULL && izquierdo(abb) != NULL){
            abb = concatenar(abb);
        }
    }else{
        //--------------------No se encuentra en la raiz del arbol > entonces buscamos
        TAbb actual   = abb;//------comienza algoritmo de busqueda------------
        TAbb anterior = abb;
        while ( natInfo(raiz(actual)) != clave){
            anterior = actual;
            if (clave < natInfo(raiz(actual))){
                actual = izquierdo(actual);
            }else{
                actual = derecho(actual);
            }
        }//-------------------fin algoritmo busqueda------------------
        if (esHoja(actual)){//-----------si el elemento es hoja--------------
            if (raiz(izquierdo(anterior)) == raiz(actual)){
                anterior->izq = NULL;
                liberarInfo(raiz(actual));
                delete actual;
            }else if (raiz(derecho(anterior)) == raiz(actual)){
                anterior->der = NULL;
                liberarInfo(raiz(actual));
                delete actual;
            }
        }else{//---------No es hoja--- evaluamos los casos----------
            if (derecho(actual) == NULL || izquierdo(actual) == NULL){
                if (derecho(actual) == NULL){
                    if (anterior->der == actual){
                        anterior->der = actual->izq;
                        liberarInfo(raiz(actual));
                        delete actual;
                    }else if (anterior->izq == actual){
                        anterior->izq = actual->izq;
                        liberarInfo(raiz(actual));
                        delete actual;
                    }
                }else if (izquierdo(actual) == NULL){
                    if (anterior->der == actual){
                        anterior->der = actual->der;
                        liberarInfo(raiz(actual));
                        delete actual;
                    }else if (anterior->izq == actual){
                        anterior->izq = actual->der;
                        liberarInfo(raiz(actual));
                        delete actual;
                    }
                }
            }else if (derecho(actual) != NULL && izquierdo(actual) != NULL){
                TAbb i = actual->izq;
                TAbb d = actual->der;
                if (esHoja(actual->der) && esHoja(actual->izq)){
                    if (anterior->izq == actual){
                        anterior->izq = d;
                        d->izq = i;
                    }else if (anterior->der == actual){
                        anterior->der = i;
                        i->der = d;
                    }
                    liberarInfo(actual->dato);
                    delete actual;
                }else{
                    if (anterior->der == actual){
                        anterior->der = concatenar(actual);
                    }else if (anterior->izq == actual){
                        anterior->izq = concatenar(actual);
                    } 
                }
            }
        }
    }
    return abb;
}

TAbb copiaAux(TAbb i , TAbb o){
    if (!esVacioAbb(i)){
       o = insertarEnAbb(copiaInfo(i->dato),o);
       copiaAux(izquierdo(i),o);
       copiaAux(derecho(i),o);
    }
    return o;    
}

TAbb copiaAbb(TAbb abb) {
    if (abb != NULL){
        if (esHoja(abb)){
            TAbb res = new _rep_abb;
            res->dato = copiaInfo(abb->dato);
            res->izq = abb->izq;
            res->der = abb->der;
            return res;
        }else{
            TAbb res = NULL;
            res = copiaAux(abb , res);
            return res;
        }
    }else{
        return NULL;
    }
}