#include "ListaPosInt.h"

#ifdef LISTA_POS_INT_IMP

struct _cabezalListaPosInt {
    int capacidad;
    int lUltimo;
    int contador;
    int* lElementos;


};

ListaPosInt crearListaPosInt(){
    
    ListaPosInt l = new _cabezalListaPosInt;
    l->capacidad = 10;
    l->lUltimo = 0;
    l->contador = 0;
    l->lElementos = new int[l->capacidad];
    return l;
        
}

void agregar(ListaPosInt& l, int e, unsigned int pos)
{
    if (l->contador == l->capacidad) {
        int* lElementos = new int[l->capacidad * 2];
        for (int i = 0; i < l->capacidad; i++) {
            lElementos[i] = l->lElementos[i];
        }
        delete[] l->lElementos;
        l->lElementos = lElementos;
        l->capacidad = l->capacidad * 2;
    }
    if (pos >= l->contador) {
        l->lElementos[l->contador] = e;
        l->contador++;
    }
    else {
        for (int i = l->contador; i > pos; i--) {
            l->lElementos[i] = l->lElementos[i - 1];
        }
        l->lElementos[pos] = e;
        l->contador++;
    }
    
}

void borrar(ListaPosInt& l, unsigned int pos)
{
    if (pos < l->contador) {
        for (int i = pos; i < l->contador - 1; i++) {
            l->lElementos[i] = l->lElementos[i + 1];
        }
        l->contador--;
    }
}

int elemento(ListaPosInt l, unsigned int pos)
{
    if (pos < l->contador) {
        return l->lElementos[pos];
    }
    else {
        return -1;
    }
    
}

bool esVacia(ListaPosInt l)
{
    if (l->contador == 0) {
        return true;
    }
    else {
        return false;
    }
    
}

unsigned int cantidadElementos(ListaPosInt l)
{
    return l->contador;
}

ListaPosInt clon(ListaPosInt l) {
    ListaPosInt l2 = new _cabezalListaPosInt;
    l2->capacidad = l->capacidad;
    l2->lUltimo = l->lUltimo;
    l2->contador = l->contador;
    l2->lElementos = new int[l2->capacidad];
    for (unsigned int i = 0; i < l2->contador; i++) {
        l2->lElementos[i] = l->lElementos[i];
    }
    return l2;
}

void destruir(ListaPosInt& l)
{
    delete[] l->lElementos;
    delete l;
}


#endif
