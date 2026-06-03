/* 4913260 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
#include <string.h>

bool estaOrdenada(TCadena cad) {
  bool res = true;
  if (cad != NULL){
    TCadena iter = cad;
    nat inicio = natInfo(primeroEnCadena(cad));
    cad = cadenaSiguiente(cad);
    if (natInfo(primeroEnCadena(cad)) == inicio){
      if (cantidadEnCadena(cad) > 1){
        res = false;
      }
    }else{//caso con mas elementos
      bool ordenado = true;
      if (natInfo(primeroEnCadena(cad)) <= natInfo(primeroEnCadena(iter))){
        res = false;
      }else{
        while((natInfo(primeroEnCadena(cad)) != inicio) && ordenado){
          iter = cad;
          cad = cadenaSiguiente(cad);
          if (natInfo(primeroEnCadena(cad)) != inicio){
            if (natInfo(primeroEnCadena(iter)) >= natInfo(primeroEnCadena(cad))){
              ordenado = false;
              res = false;
            }
            cad = cadenaSiguiente(cad); 
          }
        }
      }      
    }
  }
  return res;
}

bool menor (TCadena cad1 , TCadena cad2){
  if (natInfo(primeroEnCadena(cad1)) < natInfo(primeroEnCadena(cad2))){
    return true;
  }else{
    return false;
  }
}

bool iguales (TCadena cad1 , TCadena cad2){
  return natInfo(primeroEnCadena(cad1)) == natInfo(primeroEnCadena(cad2));
}

nat natural (TCadena cad){
  return natInfo(primeroEnCadena(cad));
}

double real (TCadena cad){
  return realInfo(primeroEnCadena(cad));
}

void mezclaCadenasAux(TCadena &res , TCadena cad1, TCadena cad2){
  int cota1 = cantidadEnCadena(cad1);
  int cota2 = cantidadEnCadena(cad2);
  while (cota1 > 0 || cota2 > 0){
    if (cota1 > 0 && cota2 > 0){
      if (iguales(cad1 , cad2)){
        res = insertarAlFinal(natural(cad1) , real(cad1) , res);
        cad1 = cadenaSiguiente(cad1);
        cad2 = cadenaSiguiente(cad2);
        cota1--;
        cota2--;
      }else if (natural(cad1) < natural(cad2)){
        res = insertarAlFinal(natural(cad1) , real(cad1) , res);
        cad1 = cadenaSiguiente(cad1);
        cota1--;
      }else if (natural(cad1) > natural(cad2)){
        res = insertarAlFinal(natural(cad2) , real(cad2) , res);
        cad2 = cadenaSiguiente(cad2);
        cota2--;
      }
    }else if (cota1 == 0 && cota2 > 0){
      res = insertarAlFinal(natural(cad2) , real(cad2) , res);
      cad2 = cadenaSiguiente(cad2);
      cota2--;
    }else if (cota1 > 0 && cota2 == 0){
      res = insertarAlFinal(natural(cad1) , real(cad1) , res);
      cad1 = cadenaSiguiente(cad1);
      cota1--;
    }
  }
}

TCadena mezclaCadenas(TCadena cad1, TCadena cad2) {
  TCadena res;
  if (cad1 == NULL && cad2 == NULL){
    res = NULL;
  }else if (cad2 == NULL){
    res = crearCadena();
    res = copiaCadena(cad1);
  }else if (cad1 == NULL){
    res = crearCadena();
    res = copiaCadena(cad2);
  }else{
    res = crearCadena();
    mezclaCadenasAux(res , cad1 , cad2);
  }
  return res;
}

void crearBalanceadoAux(TAbb &a , TInfo *arreglo , int inf , int sup){
  if (inf <= sup){
    int medio = (inf + sup)/2;
    a = insertarEnAbb(copiaInfo(arreglo[medio]) , a);
    crearBalanceadoAux(a , arreglo , inf , medio-1);
    crearBalanceadoAux(a , arreglo , medio + 1 , sup);
  }
}

TAbb crearBalanceado(TInfo *arreglo, nat n) { 
  TAbb res;
  if (n == 0 ){
    res = NULL;
  }else{
    res = crearAbb();
    crearBalanceadoAux(res , arreglo , 0 , n-1);
  }
  return res;
}

int cantNodos(TAbb a){
  if (a == NULL){   // si el arbol es vacio
      return 0;
  }else{
      return 1 + cantNodos(izquierdo(a)) + cantNodos(derecho(a));    
  }
}

nat naturalABB(TAbb a){
  return natInfo(raiz(a));
}

TAbb unionAbbs(TAbb abb1, TAbb abb2) {
  TAbb res = crearAbb();
  if (abb1 == NULL && abb2 == NULL){
    res = NULL;
  }else{
    TCadena cad1  = linealizacion(abb1);
    TCadena cad2  = linealizacion(abb2);

    TCadena cadres = mezclaCadenas(cad1 , cad2);
    nat cantCadenas = cantidadEnCadena(cadres);
    TInfo arr1[cantCadenas];
    nat contador = 0;
    while(contador <= cantCadenas-1){
      arr1[contador] = primeroEnCadena(cadres);
      cadres = cadenaSiguiente(cadres);
      contador ++;
    }
    res = crearBalanceado(arr1 , cantCadenas);
    liberarCadena(cadres);   
    liberarCadena(cad1);
    liberarCadena(cad2);     
  }
  return res;
}

TCola ordenadaPorModulo(nat p, TCadena cad) {
  TCola res = crearCola();
  nat cant_cad = cantidadEnCadena(cad);
  nat cont = cant_cad ;
  cad = cadenaSiguiente(cad);
  while (cont > 0){
    res = encolar(primeroEnCadena(cad) , res);
    cont--;
  }
  return res;
  
}

TPila menoresQueElResto(TCadena cad, nat cantidad) { return NULL; }

TCadena linealizacionAux(TAbb a , TCadena &cad){
  if (!esVacioAbb(a)){
    nat natural =  natInfo(raiz(a));
    double real = realInfo(raiz(a));
    linealizacionAux(derecho(a),cad);
    cad = insertarAlInicio(natural,real,cad);
    linealizacionAux(izquierdo(a),cad);
  }
  return cad;
}

TCadena linealizacion(TAbb abb) {
  if (!esVacioAbb(abb)){
    TCadena res = crearCadena();
    if (esVacioAbb(derecho(abb)) && esVacioAbb(izquierdo(abb))){
      res = insertarAlInicio(natInfo(raiz(abb)),realInfo(raiz(abb)),res);
    }else{
      res = linealizacionAux(abb , res);
    }
    return res;
  }else{
    return NULL;
  }
}

int maximo (int a , int b){
  if (a >= b){
    return a;
  }else{
    return b;
  }
}

int altura (TAbb a){
  if (esVacioAbb(a)){
    return 0;
  }else{
    return 1 + maximo(altura(izquierdo(a)),altura(derecho(a)));
  }
}

void imprimirAbbAux(TAbb abb, int alt, int max, TAbb muestra) {
  if (!esVacioAbb(abb)){
    alt ++;
    imprimirAbbAux(derecho(abb), alt , max , muestra);
    for (int i =1 ; i <= alt ; i++){
      printf("-");
    }
    printf("(%d,%.2f)\n",natInfo(raiz(abb)),realInfo(raiz(abb)));
    imprimirAbbAux(izquierdo(abb), alt, max,muestra);
  }
}

void imprimirAbb(TAbb abb) {
  if (!esVacioAbb(abb)){
    int alt = -1;
    TAbb aux = abb;
    imprimirAbbAux(abb , alt, altura(abb)-1,aux);  
  }
}

bool esperfectoAux(TAbb abb){
  if (esVacioAbb(abb)){
    return true;
  }else{
    if (altura(izquierdo(abb)) == altura(derecho(abb))){
      return esperfectoAux(izquierdo(abb)) && esperfectoAux(derecho(abb));
    }else{
      return false;
    }
  }
}

bool esPerfecto(TAbb abb) {
  bool aux = false;
  if (esVacioAbb(abb)){
    aux = true;
  }else if (!esVacioAbb(abb) && esVacioAbb(izquierdo(abb)) && esVacioAbb(derecho(abb))){
    aux = true;
  }else if (!esVacioAbb(abb) && !esVacioAbb(izquierdo(abb)) && !esVacioAbb(derecho(abb))){
    aux = esperfectoAux(abb);
  }
  return aux;
}

TAbb menores(double limite, TAbb abb){
    TAbb izq , der , res;
    if ( abb == NULL){
        res = NULL;
    }else{
        izq = menores(limite , izquierdo(abb));
        der = menores(limite , derecho(abb));
        TInfo aux = raiz(abb);
        if (realInfo(aux) < limite){
          res = consAbb(copiaInfo(aux) , izq ,der );
        } else if  (izq == NULL){
          res = der;
        } else if (der == NULL){
          res = izq;
        }else{
          TInfo mayor = copiaInfo(mayorEnAbb(izq));
          izq = removerDeAbb(natInfo(mayor) , izq);
          res = crearAbb();
          res = consAbb(copiaInfo(mayor) ,izq, der);
          liberarInfo(mayor);
        }
    }
    return res;
}

void caminoAscendenteAux(nat clave, nat k, TAbb abb , bool &activado , nat &contador , TIterador res){
  if (abb != NULL ){
    nat aux = natInfo(raiz(abb));
    if (clave < natInfo(raiz(abb))){
      caminoAscendenteAux(clave , k , izquierdo(abb) , activado , contador , res);
    }
    if (clave > natInfo(raiz(abb))){
      caminoAscendenteAux(clave , k , derecho(abb) , activado , contador , res);
    }
    if ( natInfo(raiz(abb)) == clave ){
      activado = true;
    }
    if (activado == true && contador < k ){
      agregarAIterador(aux , res);
      contador ++;
    }
  }
}

TIterador caminoAscendente(nat clave, nat k, TAbb abb) {
   TIterador res = crearIterador();
   if (!esVacioAbb(abb) && k > 0){
    if (natInfo(raiz(abb)) == clave && k > 0){
      agregarAIterador(natInfo(raiz(abb)) , res);
    }else{
      bool aux_bool = false;
      nat contador = 0;
      caminoAscendenteAux(clave , k , abb , aux_bool , contador , res);
    } 
   }
  return res;
}

void imprimirString(char s[] , nat cont){
  if (strlen (s) - cont <= cont){
    for (nat i = cont ; i <= strlen(s)-1  ; i++){
      printf("%c", s[i]);
    }
    printf("\n");
  }
}

void imprimirPalabrasCortasAux(nat k, TPalabras palabras , char a[] , int cont){
  if (letra(palabras) == '\0'){
    a[k] = '\0';
    imprimirString(a , cont);
  }else{
    a[k] = letra(palabras);
    imprimirPalabrasCortasAux(k+1 , subarboles(palabras) , a , cont);  
  }
  if (siguientes(palabras) != NULL){
    imprimirPalabrasCortasAux(k , siguientes(palabras) , a , cont);
  }
}

void imprimirPalabrasCortas(nat k, TPalabras palabras){
 if (palabras != NULL){
    char a[k];
    for (nat i = 0; i <= k-1 ; i++ ){
      a[i] = '-';
    }
    int cont = k ;
    imprimirPalabrasCortasAux(k , subarboles (palabras) , a, cont);
  }
}

bool esprefijo (TPalabras palabras , char prefijo[] , nat c , bool &activado , nat &cont_saltos , bool &no_subarboles){
  if (palabras != NULL){
    while (palabras != NULL && letra(palabras) == prefijo[c] && prefijo[c] != '\0'){
      if (letra(palabras) == prefijo[c]){
        c++;
        palabras = subarboles(palabras);
      }
      if (letra(palabras) != prefijo[c] && siguientes(palabras) != NULL && prefijo[c] != '\0'){
        if (subarboles(palabras) == NULL || letra (subarboles(palabras)) == '\0'){
          no_subarboles = true;
        }
        cont_saltos ++;
        activado = true;
        palabras = siguientes(palabras);
      }
    }
  }
  return prefijo[c] == '\0' || palabras == NULL;
}

TPalabras rec(TPalabras palabras , char prefijo[] , nat c){
  if ( palabras != NULL){
    TPalabras res = palabras;
    bool activado = false;
    bool no_subarboles = false;
    nat cont_saltos = 0;
    if (esprefijo(palabras , prefijo , c , activado , cont_saltos , no_subarboles)){
      if (strlen(prefijo) > 1){
        if (activado ){
          if (cont_saltos == 1){
            if (no_subarboles){
              res = subarboles(res);
              res = siguientes(res); 
            }else{
              res = subarboles(res);
              res = subarboles(res);
              res = siguientes(res);
            }
          }else{
            res = subarboles(res);
          }
        }else{
          for (nat i = 0 ; i <= strlen(prefijo)-2 ; i++){
            res = subarboles(res);
          } 
        }
      }
      return res;
    }else{
      return NULL;
    }
  }else{
    return NULL;
  }
}

TPalabras buscarFinPrefijo(ArregloChars prefijo, TPalabras palabras) {
  TPalabras res = NULL;
  palabras = subarboles(palabras);
  while (palabras != NULL && letra(palabras) != prefijo[0]){
    palabras = siguientes(palabras);
  }
  nat cont =0;
  res = rec(palabras , prefijo , cont);
  return res;
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
