#include "ColaPrioridadInt.h"

#ifdef COLAPRIORIDAD_INT_IMP

struct Elemento {
    int valor;
    int prioridad;
};

struct _cabezalColaPrioridadInt {
    Elemento* elementos;
    unsigned int capacidad;
    unsigned int cantidad;
};

ColaPrioridadInt crearColaPrioridadInt(unsigned int cota) {
    ColaPrioridadInt cola = new _cabezalColaPrioridadInt;
    cola->elementos = new Elemento[cota];
    cola->capacidad = cota;
    cola->cantidad = 0;
    return cola;
}

void encolar(ColaPrioridadInt& c, int e, int p) {
    if (esLlena(c)) return;

    // Insertar el elemento al final del arreglo
    int i = c->cantidad - 1;
    while (i >= 0 && c->elementos[i].prioridad < p) {
        c->elementos[i + 1] = c->elementos[i];
        i--;
    }
    c->elementos[i + 1].valor = e;
    c->elementos[i + 1].prioridad = p;
    c->cantidad++;
}

int principio(ColaPrioridadInt c) {
    if (esVacia(c)) return 0;
    return c->elementos[0].valor;
}

int principioPrioridad(ColaPrioridadInt c) {
    if (esVacia(c)) return 0;
    return c->elementos[0].prioridad;
}

void desencolar(ColaPrioridadInt& c) {
    if (esVacia(c)) return;

    for (unsigned int i = 0; i < c->cantidad - 1; i++) {
        c->elementos[i] = c->elementos[i + 1];
    }
    c->cantidad--;
}

bool esVacia(ColaPrioridadInt c) {
    return c->cantidad == 0;
}

bool esLlena(ColaPrioridadInt c) {
    return c->cantidad == c->capacidad;
}

unsigned int cantidadElementos(ColaPrioridadInt c) {
    return c->cantidad;
}

ColaPrioridadInt clon(ColaPrioridadInt c) {
    ColaPrioridadInt copia = crearColaPrioridadInt(c->capacidad);
    for (unsigned int i = 0; i < c->cantidad; i++) {
        copia->elementos[i] = c->elementos[i];
    }
    copia->cantidad = c->cantidad;
    return copia;
}

void destruir(ColaPrioridadInt& c) {
    delete[] c->elementos;
    delete c;
    c = NULL;
}

#endif
