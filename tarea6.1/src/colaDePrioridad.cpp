/* 4913260 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colaDePrioridad.h"
#include "../include/info.h"

struct _rep_colaDePrioridad {
  TInfo *heap;
  nat tope;
  nat tamanio;
  nat *pos;
  bool inverso;
};

static void filtradoAscendente( TColaDePrioridad &cp , nat pos);
static void filtradoDescendente( TColaDePrioridad &cp , nat pos);
TColaDePrioridad crearCP(nat N) {
  TColaDePrioridad res = new _rep_colaDePrioridad;
  res->inverso = false;
  res->tamanio = N;
  res->tope = 0;
  res->pos = new nat[N+1];
  for(nat i = 0 ; i <= N ; i++){
    res->pos[i] = 0;
  } 
  res->heap = new TInfo[N+1];
  return res;
}

void consHeapAs(TColaDePrioridad &cp){
  for (nat i = 1 ; i<=cp->tope ; i++){
    filtradoAscendente(cp,i);
  }
}

void consHeapDs(TColaDePrioridad &cp){
  for (nat i = cp->tope/2 ; i>=1 ; i--){
    filtradoDescendente(cp,i);
  }
}

TColaDePrioridad invertirPrioridad(TColaDePrioridad cp) {
  if (!cp->inverso){
    cp->inverso = true;
    if (cp->tope > 0){
      consHeapAs(cp);
    }
  }else{
    cp->inverso = false;
    if (cp->tope > 0){
      consHeapDs(cp);
    }
  }
  return cp;
}
  
void liberarCP(TColaDePrioridad cp) {
  if (cp != NULL){//modifique, antes iba hasta el tope
    for (nat i = 0 ; i <= cp->tamanio ; i++){
      if (cp->pos[i] > 0){
        liberarInfo(cp->heap[cp->pos[i]]);
      }
    }
    delete [] cp->heap;
    delete [] cp->pos;
    delete cp;
  }
}

void filtradoAscendente( TColaDePrioridad &cp , nat pos){
  if (!cp->inverso){
    while ((pos > 1) && (realInfo(cp->heap[pos/2]) > realInfo(cp->heap[pos]))){
      TInfo swap = cp->heap[pos];
    
      nat pos_padre = natInfo(cp->heap[pos/2]);
      nat pos_hijo  = natInfo(cp->heap[pos]); 
    
      cp->heap[pos]   = cp->heap[pos/2];
      cp->heap[pos/2] = swap;
      
      nat aux = cp->pos[pos_padre];
      cp->pos[pos_padre] = cp->pos[pos_hijo];
      cp->pos[pos_hijo]  = aux;
      pos /=2;
    }
  }else{
    while ((pos > 1) && (realInfo(cp->heap[pos/2]) < realInfo(cp->heap[pos]))){
      TInfo swap = cp->heap[pos];
    
      nat pos_padre = natInfo(cp->heap[pos/2]);
      nat pos_hijo  = natInfo(cp->heap[pos]); 
    
      cp->heap[pos]   = cp->heap[pos/2];
      cp->heap[pos/2] = swap;
      
      nat aux = cp->pos[pos_padre];
      cp->pos[pos_padre] = cp->pos[pos_hijo];
      cp->pos[pos_hijo]  = aux;
      pos /=2;
    }
  }
}

void filtradoDescendente( TColaDePrioridad &cp , nat pos){
  if (!cp->inverso){
    TInfo swap = cp->heap[pos];
    if (2*pos <= cp->tope){//si tengo hjo izquierdo
      do{
        nat pos_hijo = 2*pos;
        if ((2*pos+1) <= cp->tope && realInfo(cp->heap[2*pos+1]) < realInfo(cp->heap[2*pos])){
          pos_hijo = 2*pos+1;
        }
        if (realInfo(swap) > realInfo(cp->heap[pos_hijo])){
          cp->heap[pos] = cp->heap[pos_hijo];
          cp->pos[natInfo(cp->heap[pos_hijo])] = pos;
          pos = pos_hijo;
        }
      }while ((2*pos <= cp->tope) && realInfo(swap) > realInfo(cp->heap[2*pos]));
      cp->heap[pos] = swap;
      cp->pos[natInfo(swap)] =pos;
    }
  }else{
    TInfo swap = cp->heap[pos];
    if (2*pos <= cp->tope){//si tengo hjo izquierdo
      do{
        nat pos_hijo = 2*pos;
        if ((2*pos+1) <= cp->tope && realInfo(cp->heap[2*pos+1]) > realInfo(cp->heap[2*pos])){
          pos_hijo = 2*pos+1;
        }
        if (realInfo(swap) < realInfo(cp->heap[pos_hijo])){
          cp->heap[pos] = cp->heap[pos_hijo];
          cp->pos[natInfo(cp->heap[pos_hijo])] = pos;
          pos = pos_hijo;
        }
      }while ((2*pos <= cp->tope) && realInfo(swap) < realInfo(cp->heap[2*pos]));
      cp->heap[pos] = swap;
      cp->pos[natInfo(swap)] =pos;
    }
  }
}


void modificarOrden(nat dato , float orden , TColaDePrioridad &cp){
  nat pos  = cp->pos[dato]; //obtengo la posicion pos en el heap
  float orden_ant = realInfo(cp->heap[pos]);
  TInfo aux = crearInfo(dato,orden);
  liberarInfo(cp->heap[pos]);
  cp->heap[pos] = aux;
  if(!cp->inverso){
    if (orden > orden_ant){
        filtradoDescendente(cp , pos);
    }else{
        filtradoAscendente(cp , pos);
    }
  }
}

TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp) {
  if (elem <= cp->tamanio && elem > 0 && cp->tope <= cp->tamanio){
    if (cp->pos[elem] == 0){
      cp->tope++;
      TInfo i = crearInfo(elem,valor);
      cp->heap[cp->tope] = i;
      cp->pos[elem] = cp->tope;
      if (cp->tope > 1){
        filtradoAscendente( cp , cp->tope);
      }
    }else{
      modificarOrden(elem , valor , cp);
    }
  }
  return cp;
}

bool estaVaciaCP(TColaDePrioridad cp) {
   bool res = true;
   if (cp != NULL){
    res = cp->tope == 0;
   }
   return res; 
}

nat prioritario(TColaDePrioridad cp)  { 
  return natInfo(cp->heap[1]);
}

TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp)  {
  if (cp->tope > 0){
    if(cp->tope == 1){
      cp->pos[natInfo(cp->heap[1])] = 0;
      cp->tope--;
      liberarInfo(cp->heap[1]);
    }else{
      cp->pos[natInfo(cp->heap[1])] = 0;
      nat pos_tope = natInfo(cp->heap[cp->tope]);//pos de  tope
      liberarInfo(cp->heap[1]);
        cp->heap[1] = cp->heap[cp->tope];
      cp->pos[pos_tope] = 0;
      cp->pos[natInfo(cp->heap[1])] = 1;  
      cp->tope --;
      if (cp->tope > 1 ){
        filtradoDescendente(cp,1);
      }
    }
  }
  return cp;
}


bool estaEnCP(nat elem, TColaDePrioridad cp)  {
  bool res = false;
  if ((cp != NULL) && (elem <= cp->tamanio) && (cp->pos[elem] > 0)){
    res = true;
  }
  return res;
}

double prioridad(nat elem, TColaDePrioridad cp)  {
  return realInfo(cp->heap[cp->pos[elem]]);
}
