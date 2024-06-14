#include "MultisetInt.h"

#ifdef MULTISET_INT_IMP

struct nodoMultisetInt {
    int elemento;
    unsigned int ocurrencias;
    nodoMultisetInt* sig;
};

struct _cabezalMultisetInt {
    nodoMultisetInt** tablaHash;
    unsigned int cantidadElementos;
    unsigned int largoTablaHash;
};

unsigned int funcionHashInt(int d, unsigned int largo) {
    return d % largo;
}

void redimensionarTabla(MultisetInt& s, unsigned int nuevoLargo) {
    MultisetInt nuevaTabla = new _cabezalMultisetInt;
    nuevaTabla->cantidadElementos = 0;
    nuevaTabla->largoTablaHash = nuevoLargo;
    nuevaTabla->tablaHash = new nodoMultisetInt*[nuevoLargo];
    for (unsigned int i = 0; i < nuevoLargo; i++) {
        nuevaTabla->tablaHash[i] = NULL;
    }

    for (unsigned int i = 0; i < s->largoTablaHash; i++) {
        nodoMultisetInt* actual = s->tablaHash[i];
        while (actual != NULL) {
            agregar(nuevaTabla, actual->elemento, actual->ocurrencias);
            nodoMultisetInt* aBorrar = actual;
            actual = actual->sig;
            delete aBorrar;
        }
    }
    delete[] s->tablaHash;
    s->tablaHash = nuevaTabla->tablaHash;
    s->largoTablaHash = nuevoLargo;
    delete nuevaTabla;
}


MultisetInt crearMultisetInt() {
    MultisetInt s = new _cabezalMultisetInt;
    s->cantidadElementos = 0;
    s->largoTablaHash = 11;
    s->tablaHash = new nodoMultisetInt*[s->largoTablaHash];
    for (unsigned int i = 0; i < s->largoTablaHash; i++) {
        s->tablaHash[i] = NULL;
    }
    return s;
}

void agregar(MultisetInt& s, int e, unsigned int ocurrencias) {
    if (s->cantidadElementos > s->largoTablaHash * 0.75) {
        redimensionarTabla(s, s->largoTablaHash * 2);
    }

    unsigned int pos = funcionHashInt(e, s->largoTablaHash);
    nodoMultisetInt* actual = s->tablaHash[pos];
    while (actual != NULL && actual->elemento != e) {
        actual = actual->sig;
    }
    if (actual != NULL) {
        actual->ocurrencias += ocurrencias;
    } else {
        nodoMultisetInt* nuevo = new nodoMultisetInt;
        nuevo->elemento = e;
        nuevo->ocurrencias = ocurrencias;
        nuevo->sig = s->tablaHash[pos];
        s->tablaHash[pos] = nuevo;
        s->cantidadElementos++;
    }
}


void borrar(MultisetInt& s, int e) {
    unsigned int pos = funcionHashInt(e, s->largoTablaHash);
    nodoMultisetInt* actual = s->tablaHash[pos];
    nodoMultisetInt* anterior = NULL;
    while (actual != NULL && actual->elemento != e) {
        anterior = actual;
        actual = actual->sig;
    }
    if (actual != NULL) {
        if (actual->ocurrencias > 1) {
            actual->ocurrencias--;
        } else {
            if (anterior == NULL) {
                s->tablaHash[pos] = actual->sig;
            } else {
                anterior->sig = actual->sig;
            }
            delete actual;
            s->cantidadElementos--;

            if (s->cantidadElementos < s->largoTablaHash * 0.25 && s->largoTablaHash > 11) {
                redimensionarTabla(s, s->largoTablaHash / 2);
            }
        }
    }
}

bool pertenece(MultisetInt s, int e) {
    unsigned int pos = funcionHashInt(e, s->largoTablaHash);
    nodoMultisetInt* actual = s->tablaHash[pos];
    while (actual != NULL && actual->elemento != e) {
        actual = actual->sig;
    }
    return actual != NULL;
}

MultisetInt unionConjuntos(MultisetInt s1, MultisetInt s2) {
    MultisetInt result = crearMultisetInt();

    for (unsigned int i = 0; i < s1->largoTablaHash; i++) {
        nodoMultisetInt* actual = s1->tablaHash[i];
        while (actual != NULL) {
            agregar(result, actual->elemento, actual->ocurrencias);
            actual = actual->sig;
        }
    }

    for (unsigned int i = 0; i < s2->largoTablaHash; i++) {
        nodoMultisetInt* actual = s2->tablaHash[i];
        while (actual != NULL) {
            unsigned int pos = funcionHashInt(actual->elemento, result->largoTablaHash);
            nodoMultisetInt* temp = result->tablaHash[pos];
            bool encontrado = false;
            while (temp != NULL) {
                if (temp->elemento == actual->elemento) {
                    encontrado = true;
                    if (temp->ocurrencias < actual->ocurrencias) {
                        temp->ocurrencias = actual->ocurrencias;
                    }
                    break;
                }
                temp = temp->sig;
            }
            if (!encontrado) {
                agregar(result, actual->elemento, actual->ocurrencias);
            }
            actual = actual->sig;
        }
    }

    return result;
}







MultisetInt interseccionConjuntos(MultisetInt s1, MultisetInt s2) {
    MultisetInt result = crearMultisetInt();
    for (unsigned int i = 0; i < s1->largoTablaHash; i++) {
        nodoMultisetInt* actual = s1->tablaHash[i];
        while (actual != NULL) {
            unsigned int ocurrencias = 0;
            nodoMultisetInt* temp = s2->tablaHash[funcionHashInt(actual->elemento, s2->largoTablaHash)];
            while (temp != NULL) {
                if (temp->elemento == actual->elemento) {
                    ocurrencias = (actual->ocurrencias < temp->ocurrencias) ? actual->ocurrencias : temp->ocurrencias;
                    break;
                }
                temp = temp->sig;
            }
            if (ocurrencias > 0) {
                agregar(result, actual->elemento, ocurrencias);
            }
            actual = actual->sig;
        }
    }
    return result;
}

MultisetInt diferenciaConjuntos(MultisetInt s1, MultisetInt s2) {
    MultisetInt result = crearMultisetInt();
    for (unsigned int i = 0; i < s1->largoTablaHash; i++) {
        nodoMultisetInt* actual = s1->tablaHash[i];
        while (actual != NULL) {
            unsigned int ocurrencias = actual->ocurrencias;
            nodoMultisetInt* temp = s2->tablaHash[funcionHashInt(actual->elemento, s2->largoTablaHash)];
            while (temp != NULL) {
                if (temp->elemento == actual->elemento) {
                    ocurrencias = (actual->ocurrencias > temp->ocurrencias) ? (actual->ocurrencias - temp->ocurrencias) : 0;
                    break;
                }
                temp = temp->sig;
            }
            if (ocurrencias > 0) {
                agregar(result, actual->elemento, ocurrencias);
            }
            actual = actual->sig;
        }
    }
    return result;
}

bool contenidoEn(MultisetInt s1, MultisetInt s2) {
    for (unsigned int i = 0; i < s1->largoTablaHash; i++) {
        nodoMultisetInt* actual = s1->tablaHash[i];
        while (actual != NULL) {
            nodoMultisetInt* temp = s2->tablaHash[funcionHashInt(actual->elemento, s2->largoTablaHash)];
            while (temp != NULL) {
                if (temp->elemento == actual->elemento) {
                    if (temp->ocurrencias < actual->ocurrencias) {
                        return false;
                    }
                    break;
                }
                temp = temp->sig;
            }
            if (temp == NULL) {
                return false;
            }
            actual = actual->sig;
        }
    }
    return true;
}

int elemento(MultisetInt s) {
    for (unsigned int i = 0; i < s->largoTablaHash; i++) {
        if (s->tablaHash[i] != NULL) {
            return s->tablaHash[i]->elemento;
        }
    }
    return 0;
}

bool esVacio(MultisetInt s) {
    return s->cantidadElementos == 0;
}

unsigned int cantidadElementos(MultisetInt s) {
    unsigned int count = 0;
    for (unsigned int i = 0; i < s->largoTablaHash; i++) {
        nodoMultisetInt* actual = s->tablaHash[i];
        while (actual != NULL) {
            count += actual->ocurrencias;
            actual = actual->sig;
        }
    }
    return count;
}

void destruir(MultisetInt& s) {
    for (unsigned int i = 0; i < s->largoTablaHash; i++) {
        nodoMultisetInt* actual = s->tablaHash[i];
        while (actual != NULL) {
            nodoMultisetInt* aBorrar = actual;
            actual = actual->sig;
            delete aBorrar;
        }
    }
    delete[] s->tablaHash;
    delete s;
    s = NULL;
}

MultisetInt clon(MultisetInt s) {
    MultisetInt copy = crearMultisetInt();
    for (unsigned int i = 0; i < s->largoTablaHash; i++) {
        nodoMultisetInt* actual = s->tablaHash[i];
        while (actual != NULL) {
            for (unsigned int j = 0; j < actual->ocurrencias; j++) {
                agregar(copy, actual->elemento, 1);
            }
            actual = actual->sig;
        }
    }
    return copy;
}





#endif
