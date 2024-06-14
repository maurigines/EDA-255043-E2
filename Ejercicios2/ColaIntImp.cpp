#include "ColaInt.h"

#ifdef COLA_INT_IMP

struct NodoListaIntCola {
    int dato;
    NodoListaIntCola *sig;
    NodoListaIntCola() : dato(0), sig(NULL) {}
    NodoListaIntCola(int d) : dato(d), sig(NULL) {}
};

struct _cabezalColaInt {
    NodoListaIntCola* primero;
    NodoListaIntCola* ultimo;
    unsigned int cantidad;
};

ColaInt crearColaInt() {
    ColaInt nuevaCola = new _cabezalColaInt;
    nuevaCola->primero = NULL;
    nuevaCola->ultimo = NULL;
    nuevaCola->cantidad = 0;
    return nuevaCola;
}

void encolar(ColaInt& c, int e) {
    NodoListaIntCola* nuevoNodo = new NodoListaIntCola;
    nuevoNodo->dato = e;
    nuevoNodo->sig = NULL;
    if (c->cantidad == 0) {
        c->primero = nuevoNodo;
    }
    else {
        c->ultimo->sig = nuevoNodo;
    }
    c->ultimo = nuevoNodo;
    c->cantidad++;
}

int principio(ColaInt c) {
    return c->primero->dato;
}

void desencolar(ColaInt& c) {
    NodoListaIntCola* aBorrar = c->primero;
    c->primero = c->primero->sig;
    delete aBorrar;
    c->cantidad--;
    if (c->cantidad == 0) {
        c->ultimo = NULL;
    }
}

bool esVacia(ColaInt c) {
    return c->cantidad == 0;
}

unsigned int cantidadElementos(ColaInt c) {
    return c->cantidad;
}

ColaInt clon(ColaInt c) {
    ColaInt nuevaCola = crearColaInt();
    NodoListaIntCola* actual = c->primero;
    while (actual != NULL) {
        encolar(nuevaCola, actual->dato);
        actual = actual->sig;
    }
    return nuevaCola;
}

void destruir(ColaInt& c) {
    while (!esVacia(c)) {
        desencolar(c);
    }
    delete c;
}

#endif
