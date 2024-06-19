// Mauricio Gines Martinez Miglionico 255043
#include "ListaOrdInt.h"

#ifdef LISTA_ORD_INT_IMP_2

struct NodoListaOrdInt {
    int valor;
    int repeticiones;
    NodoListaOrdInt* izquierda;
    NodoListaOrdInt* derecha;

    NodoListaOrdInt(int val) : valor(val), repeticiones(1), izquierda(NULL), derecha(NULL) {}
};

struct _cabezalListaOrdInt {
    NodoListaOrdInt* raiz;
    int totalNodos;

    _cabezalListaOrdInt() : raiz(NULL), totalNodos(0) {}
};

ListaOrdInt crearListaOrdInt() {
    return new _cabezalListaOrdInt();
}

//PRE: -
//POS: Agrega un nodo con el entero al ·rbol
void agregarNodo(NodoListaOrdInt*& nodo, int e) {
    if (nodo == NULL) {
        nodo = new NodoListaOrdInt(e);
    }
    else if (e == nodo->valor) {
        nodo->repeticiones++;
    }
    else if (e < nodo->valor) {
        agregarNodo(nodo->izquierda, e);
    }
    else {
        agregarNodo(nodo->derecha, e);
    }
}

void agregar(ListaOrdInt& l, int e) {
    agregarNodo(l->raiz, e);
    l->totalNodos++;
}

//PRE: -
//POS: Retorna el valor mÌnimo del arbol
void borrarMinimoNodo(NodoListaOrdInt*& nodo) {
    if (nodo == NULL) return;
    if (nodo->izquierda == NULL) {
        if (nodo->repeticiones > 1) {
            nodo->repeticiones--;
        }
        else if (nodo->derecha == NULL) {
            delete nodo;
            nodo = NULL;
        }
        else {
            NodoListaOrdInt* temp = nodo;
            nodo = nodo->derecha;
            delete temp;
        }
    }
    else {
        borrarMinimoNodo(nodo->izquierda);
    }
}

void borrarMinimo(ListaOrdInt& l) {
    if (l == NULL || l->totalNodos == 0) return;
    borrarMinimoNodo(l->raiz);
    l->totalNodos--;
}

//PRE: -
//POS: Retorna el valor maximo del arbol
void borrarMaximoNodo(NodoListaOrdInt*& nodo) {
    if (nodo == NULL) return;
    if (nodo->derecha == NULL) {
        if (nodo->repeticiones > 1) {
            nodo->repeticiones--;
        }
        else if (nodo->izquierda == NULL) {
            delete nodo;
            nodo = NULL;
        }
        else {
            NodoListaOrdInt* temp = nodo;
            nodo = nodo->izquierda;
            delete temp;
        }
    }
    else {
        borrarMaximoNodo(nodo->derecha);
    }
}

void borrarMaximo(ListaOrdInt& l) {
    if (l == NULL || l->totalNodos == 0) return;
    borrarMaximoNodo(l->raiz);
    l->totalNodos--;
}

//PRE:
//POS: Borra un nodo con el entero del arbol
void borrarNodo(NodoListaOrdInt*& nodo, int e, bool& eliminado) {
    if (nodo == NULL) return;
    if (e == nodo->valor) {
        if (nodo->repeticiones > 1) {
            nodo->repeticiones--;
            eliminado = true;
        } else if (nodo->izquierda == NULL && nodo->derecha == NULL) {
            delete nodo;
            nodo = NULL;
            eliminado = true;
        } else if (nodo->izquierda == NULL) {
            NodoListaOrdInt* temp = nodo;
            nodo = nodo->derecha;
            delete temp;
            eliminado = true;
        } else if (nodo->derecha == NULL) {
            NodoListaOrdInt* temp = nodo;
            nodo = nodo->izquierda;
            delete temp;
            eliminado = true;
        } else {
            NodoListaOrdInt* minNode = nodo->derecha;
            while (minNode->izquierda != NULL) {
                minNode = minNode->izquierda;
            }
            nodo->valor = minNode->valor;
            nodo->repeticiones = minNode->repeticiones;
            borrarNodo(nodo->derecha, minNode->valor, eliminado);
            eliminado = true;
        }
    } else if (e < nodo->valor) {
        borrarNodo(nodo->izquierda, e, eliminado);
    } else {
        borrarNodo(nodo->derecha, e, eliminado);
    }
}

void borrar(ListaOrdInt& l, int e) {
    if (l == NULL || l->totalNodos == 0) return;
    bool eliminado = false;
    borrarNodo(l->raiz, e, eliminado);
    if (eliminado) {
        l->totalNodos--;
    }
}

// PRE: -
// POS: Retorna el mÌnimo del arbol
int minimoNodo(NodoListaOrdInt* nodo) {
    if (nodo->izquierda == NULL) return nodo->valor;
    return minimoNodo(nodo->izquierda);
}

int minimo(ListaOrdInt l) {
    return minimoNodo(l->raiz);
}

// PRE: -
// POS: Retorna el maximo del arbol
int maximoNodo(NodoListaOrdInt* nodo) {
    if (nodo->derecha == NULL) return nodo->valor;
    return maximoNodo(nodo->derecha);
}

int maximo(ListaOrdInt l) {
    return maximoNodo(l->raiz);
}

// PRE: -
// POS: Retorna si existe un nodo con el entero en el arbol
bool existeNodo(NodoListaOrdInt* nodo, int e) {
    if (nodo == NULL) return false;
    if (e == nodo->valor) return true;
    if (e < nodo->valor) return existeNodo(nodo->izquierda, e);
    return existeNodo(nodo->derecha, e);
}

 
bool existe(ListaOrdInt l, int e) {
    if (l == NULL || l->totalNodos == 0) return false;
    return existeNodo(l->raiz, e);
}

bool esVacia(ListaOrdInt l) {
    return l == NULL || l->totalNodos == 0;
}

unsigned int cantidadElementos(ListaOrdInt l) {
    return l == NULL ? 0 : l->totalNodos;
}


// PRE: -
// POS: Retorna la cantidad de nodos del ·rbol
NodoListaOrdInt* clonNodo(NodoListaOrdInt* nodo) {
    if (nodo == NULL) return NULL;
    NodoListaOrdInt* cl = new NodoListaOrdInt(nodo->valor);
    cl->repeticiones = nodo->repeticiones;
    cl->izquierda = clonNodo(nodo->izquierda);
    cl->derecha = clonNodo(nodo->derecha);
    return cl;
}


ListaOrdInt clon(ListaOrdInt l) {
    if (l == NULL) return NULL;
    ListaOrdInt cl = new _cabezalListaOrdInt();
    cl->raiz = clonNodo(l->raiz);
    cl->totalNodos = l->totalNodos;
    return cl;
}


// PRE: -
// POS: Destruye el arbol
void destruirNodo(NodoListaOrdInt*& nodo) {
    if (nodo == NULL) return;
    destruirNodo(nodo->izquierda);
    destruirNodo(nodo->derecha);
    delete nodo;
    nodo = NULL;
}

void destruir(ListaOrdInt& l) {
    if (l == NULL) return;
    destruirNodo(l->raiz);
    delete l;
    l = NULL;
}




#endif
