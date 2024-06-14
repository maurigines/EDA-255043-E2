#include "TablaIntString.h"
#include <cstring> // para usar strcpy y strlen

#ifdef TABLA_INT_STRING_IMP

struct nodoTablaIntString {
    int clave;
    char* valor;
    nodoTablaIntString* sig;
};

struct _cabezalTablaIntString {
    nodoTablaIntString** tablaHash;
    unsigned int cantidadElementos;
    unsigned int largoTablaHash;
};

// Función de hash
unsigned int funcionHashIntString(int d, unsigned int largo) {
    return d % largo;
}

int stringLength(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void stringCopy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

TablaIntString crearTablaIntString(unsigned int esperados) {
    TablaIntString tabla = new _cabezalTablaIntString;
    tabla->cantidadElementos = 0;
    tabla->largoTablaHash = esperados;
    tabla->tablaHash = new nodoTablaIntString*[esperados];
    for (unsigned int i = 0; i < esperados; i++) {
        tabla->tablaHash[i] = NULL;
    }
    return tabla;
}

void redimensionarTabla(TablaIntString& t, unsigned int nuevoLargo) {
    TablaIntString nuevaTabla = crearTablaIntString(nuevoLargo);

    for (unsigned int i = 0; i < t->largoTablaHash; i++) {
        nodoTablaIntString* actual = t->tablaHash[i];
        while (actual != NULL) {
            agregar(nuevaTabla, actual->clave, actual->valor);
            nodoTablaIntString* aBorrar = actual;
            actual = actual->sig;
            delete[] aBorrar->valor;
            delete aBorrar;
        }
    }

    delete[] t->tablaHash;
    t->tablaHash = nuevaTabla->tablaHash;
    t->largoTablaHash = nuevoLargo;
    delete nuevaTabla;
}

void agregar(TablaIntString& t, int d, const char* r) {
    if (t->cantidadElementos > t->largoTablaHash * 0.75) {
        redimensionarTabla(t, t->largoTablaHash * 2);
    }

    unsigned int pos = funcionHashIntString(d, t->largoTablaHash);
    nodoTablaIntString* actual = t->tablaHash[pos];
    while (actual != NULL && actual->clave != d) {
        actual = actual->sig;
    }
    if (actual != NULL) {
        delete[] actual->valor;
        int largo = (stringLength(r) + 1);
        actual->valor = new char[largo];
        stringCopy(actual->valor, r);
    } else {
        nodoTablaIntString* nuevo = new nodoTablaIntString;
        nuevo->clave = d;
        nuevo->valor = new char[stringLength(r) + 1];
        stringCopy(nuevo->valor, r);
        nuevo->sig = t->tablaHash[pos];
        t->tablaHash[pos] = nuevo;
        t->cantidadElementos++;
    }
}

bool estaDefinida(TablaIntString t, int d) {
    unsigned int pos = funcionHashIntString(d, t->largoTablaHash);
    nodoTablaIntString* actual = t->tablaHash[pos];
    while (actual != NULL && actual->clave != d) {
        actual = actual->sig;
    }
    return actual != NULL;
}

const char* recuperar(TablaIntString t, int d) {
    unsigned int pos = funcionHashIntString(d, t->largoTablaHash);
    nodoTablaIntString* actual = t->tablaHash[pos];
    while (actual != NULL && actual->clave != d) {
        actual = actual->sig;
    }
    if (actual != NULL) {
        return actual->valor;
    }
    return "";
}

void borrar(TablaIntString& t, int d) {
    unsigned int pos = funcionHashIntString(d, t->largoTablaHash);
    nodoTablaIntString* actual = t->tablaHash[pos];
    nodoTablaIntString* anterior = NULL;
    while (actual != NULL && actual->clave != d) {
        anterior = actual;
        actual = actual->sig;
    }
    if (actual != NULL) {
        if (anterior == NULL) {
            t->tablaHash[pos] = actual->sig;
        } else {
            anterior->sig = actual->sig;
        }
        delete[] actual->valor;
        delete actual;
        t->cantidadElementos--;

        if (t->cantidadElementos < t->largoTablaHash * 0.25 && t->largoTablaHash > 11) {
            redimensionarTabla(t, t->largoTablaHash / 2);
        }
    }
}

int elemento(TablaIntString t) {
    for (unsigned int i = 0; i < t->largoTablaHash; i++) {
        if (t->tablaHash[i] != NULL) {
            return t->tablaHash[i]->clave;
        }
    }
    return 0; // Devuelve 0 si la tabla está vacía
}

bool esVacia(TablaIntString t) {
    return t->cantidadElementos == 0;
}

unsigned int cantidadElementos(TablaIntString t) {
    return t->cantidadElementos;
}

void destruir(TablaIntString& t) {
    for (unsigned int i = 0; i < t->largoTablaHash; i++) {
        nodoTablaIntString* actual = t->tablaHash[i];
        while (actual != NULL) {
            nodoTablaIntString* aBorrar = actual;
            actual = actual->sig;
            delete[] aBorrar->valor;
            delete aBorrar;
        }
    }
    delete[] t->tablaHash;
    delete t;
    t = NULL;
}

TablaIntString clon(TablaIntString t) {
    TablaIntString clon = crearTablaIntString(t->largoTablaHash);
    for (unsigned int i = 0; i < t->largoTablaHash; i++) {
        nodoTablaIntString* actual = t->tablaHash[i];
        while (actual != NULL) {
            agregar(clon, actual->clave, actual->valor);
            actual = actual->sig;
        }
    }
    return clon;
}

#endif
