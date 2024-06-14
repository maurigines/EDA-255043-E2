#include "PilaInt.h"

#ifdef PILA_INT_IMP

struct NodoListaIntPila {
    int dato;
    NodoListaIntPila *sig;
    NodoListaIntPila() : dato(0), sig(NULL) {}
    NodoListaIntPila(int d) : dato(d), sig(NULL) {}
};

struct _cabezalPilaInt {
    NodoListaIntPila* tope;
    unsigned int contador;
};


PilaInt crearPilaInt(){
    PilaInt p = new _cabezalPilaInt;
    p->tope = NULL;
    p->contador = 0;
    return p;
}

void push(PilaInt& p, int e) {
    NodoListaIntPila* nuevo = new NodoListaIntPila;
    nuevo->dato = e;
    nuevo->sig = p->tope;
    p->tope = nuevo;
    p->contador++;
}

int top(PilaInt p) {
    
    return p->tope->dato;
}

void pop(PilaInt& p) {
    
    NodoListaIntPila* temp = p->tope;
    p->tope = p->tope->sig;
    delete temp;
    p->contador--;
}

unsigned int cantidadElementos(PilaInt p) {
    return p->contador;
}

bool esVacia(PilaInt p) {
    return p->tope == NULL;
}

PilaInt clon(PilaInt p) {
    PilaInt nuevaPila = crearPilaInt();
    NodoListaIntPila* actual = p->tope;
    NodoListaIntPila* previo = NULL;
    NodoListaIntPila* nuevo;

    
    while (actual != NULL) {
        nuevo = new NodoListaIntPila;
        nuevo->dato = actual->dato;
        nuevo->sig = previo;
        previo = nuevo;
        actual = actual->sig;
    }

    
    actual = previo;
    while (actual != NULL) {
        push(nuevaPila, actual->dato);
        NodoListaIntPila* temp = actual;
        actual = actual->sig;
        delete temp;
    }

    return nuevaPila;
}

void destruir(PilaInt& p) {
    while (!esVacia(p)) {
        pop(p);
    }
    delete p;
    p = NULL;
}


#endif

