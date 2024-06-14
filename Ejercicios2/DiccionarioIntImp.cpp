#include "DiccionarioInt.h"

#ifdef DICCIONARIO_INT_IMP

struct nodoLista {
    int dato;
    nodoLista* sig;
};

struct _cabezalDiccionarioInt {
    nodoLista** tablaHash;
    unsigned int cantidadElementos;
    unsigned int largoTablaHash;
};

DiccionarioInt crearDiccionarioInt(unsigned int esperados) {
    DiccionarioInt diccionario = new _cabezalDiccionarioInt;
    diccionario->cantidadElementos = 0;
    diccionario->largoTablaHash = esperados;
    diccionario->tablaHash = new nodoLista*[esperados];
    for (unsigned int i = 0; i < esperados; i++) {
        diccionario->tablaHash[i] = NULL;
    }
    return diccionario;
}

unsigned int funcionHash(int e, unsigned int largo) {
    return e % largo;
}

void redimensionarDiccionario(DiccionarioInt& d, unsigned int nuevoLargo) {
    DiccionarioInt nuevaTabla = crearDiccionarioInt(nuevoLargo);

    for (unsigned int i = 0; i < d->largoTablaHash; i++) {
        nodoLista* actual = d->tablaHash[i];
        while (actual != NULL) {
            agregar(nuevaTabla, actual->dato);
            nodoLista* aBorrar = actual;
            actual = actual->sig;
            delete aBorrar;
        }
    }

    delete[] d->tablaHash;
    d->tablaHash = nuevaTabla->tablaHash;
    d->largoTablaHash = nuevoLargo;
    delete nuevaTabla;
}

void agregar(DiccionarioInt& d, int e) {
    if (d->cantidadElementos > d->largoTablaHash * 0.75) {
        redimensionarDiccionario(d, d->largoTablaHash * 2);
    }

    unsigned int pos = funcionHash(e, d->largoTablaHash);
    nodoLista* actual = d->tablaHash[pos];
    while (actual != NULL) {
        if (actual->dato == e) {
            return;
        }
        actual = actual->sig;
    }
    nodoLista* nuevo = new nodoLista;
    nuevo->dato = e;
    nuevo->sig = d->tablaHash[pos];
    d->tablaHash[pos] = nuevo;
    d->cantidadElementos++;
}

void borrar(DiccionarioInt& d, int e) {
    unsigned int pos = funcionHash(e, d->largoTablaHash);
    nodoLista* actual = d->tablaHash[pos];
    nodoLista* anterior = NULL;
    while (actual != NULL && actual->dato != e) {
        anterior = actual;
        actual = actual->sig;
    }
    if (actual != NULL) {
        if (anterior == NULL) {
            d->tablaHash[pos] = actual->sig;
        } else {
            anterior->sig = actual->sig;
        }
        delete actual;
        d->cantidadElementos--;

        if (d->cantidadElementos < d->largoTablaHash * 0.25 && d->largoTablaHash > 11) {
            redimensionarDiccionario(d, d->largoTablaHash / 2);
        }
    }
}

bool pertenece(DiccionarioInt d, int e) {
    unsigned int pos = funcionHash(e, d->largoTablaHash);
    nodoLista* actual = d->tablaHash[pos];
    while (actual != NULL && actual->dato != e) {
        actual = actual->sig;
    }
    return actual != NULL;
}

int elemento(DiccionarioInt d) {
    for (unsigned int i = 0; i < d->largoTablaHash; i++) {
        if (d->tablaHash[i] != NULL) {
            return d->tablaHash[i]->dato;
        }
    }
    return 0;
}

bool esVacio(DiccionarioInt d) {
    return d->cantidadElementos == 0;
}

unsigned int cantidadElementos(DiccionarioInt d) {
    return d->cantidadElementos;
}

DiccionarioInt clon(DiccionarioInt d) {
    DiccionarioInt clon = crearDiccionarioInt(d->largoTablaHash);
    for (unsigned int i = 0; i < d->largoTablaHash; i++) {
        nodoLista* actual = d->tablaHash[i];
        while (actual != NULL) {
            agregar(clon, actual->dato);
            actual = actual->sig;
        }
    }
    return clon;
}

void destruir(DiccionarioInt& d) {
    for (unsigned int i = 0; i < d->largoTablaHash; i++) {
        nodoLista* actual = d->tablaHash[i];
        while (actual != NULL) {
            nodoLista* aBorrar = actual;
            actual = actual->sig;
            delete aBorrar;
        }
    }
    delete[] d->tablaHash;
    delete d;
    d = NULL;
}

#endif
