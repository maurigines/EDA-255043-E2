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

//PRE: Recibe un puntero a un nodo y un entero
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

//PRE: Recibe un puntero a un nodo
//POS: Retorna el valor mÌnimo del ·rbol
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

//PRE: Recibe un puntero a un nodo
//POS: Retorna el valor m·ximo del ·rbol
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

//PRE: Recibe un puntero a un nodo y un entero
//POS: Borra un nodo con el entero del ·rbol
void borrarNodo(NodoListaOrdInt*& nodo, int e) {
    if (nodo == NULL) return;
    if (e == nodo->valor) {
        if (nodo->repeticiones > 1) {
            nodo->repeticiones--;
        }
        else if (nodo->izquierda == NULL && nodo->derecha == NULL) {
            delete nodo;
            nodo = NULL;
        }
        else if (nodo->izquierda == NULL) {
            NodoListaOrdInt* temp = nodo;
            nodo = nodo->derecha;
            delete temp;
        }
        else if (nodo->derecha == NULL) {
            NodoListaOrdInt* temp = nodo;
            nodo = nodo->izquierda;
            delete temp;
        }
        else {
            NodoListaOrdInt* minNode = nodo->derecha;
            while (minNode->izquierda != NULL) {
                minNode = minNode->izquierda;
            }
            nodo->valor = minNode->valor;
            nodo->repeticiones = minNode->repeticiones;
            borrarNodo(nodo->derecha, minNode->valor);
        }
    }
    else if (e < nodo->valor) {
        borrarNodo(nodo->izquierda, e);
    }
    else {
        borrarNodo(nodo->derecha, e);
    }
}


void borrar(ListaOrdInt& l, int e) {
    if (l == NULL || l->totalNodos == 0) return;
    borrarNodo(l->raiz, e);
    l->totalNodos--;
}

// PRE: Recibe un puntero a un nodo
// POS: Retorna el mÌnimo del ·rbol
int minimoNodo(NodoListaOrdInt* nodo) {
    if (nodo->izquierda == NULL) return nodo->valor;
    return minimoNodo(nodo->izquierda);
}

int minimo(ListaOrdInt l) {
    return minimoNodo(l->raiz);
}

// PRE: Recibe un puntero a un nodo
// POS: Retorna el m·ximo del ·rbol
int maximoNodo(NodoListaOrdInt* nodo) {
    if (nodo->derecha == NULL) return nodo->valor;
    return maximoNodo(nodo->derecha);
}

int maximo(ListaOrdInt l) {
    return maximoNodo(l->raiz);
}

// PRE: Recibe un puntero a un nodo
// POS: Retorna si existe un nodo con el entero en el ·rbol
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


// PRE: Recibe un puntero a un nodo
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

// PRE: Recibe un puntero a un nodo
// POS: Destruye el ·rbol
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
