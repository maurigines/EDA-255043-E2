// Mauricio Gines Martinez Miglionico 255043
#include "Ejercicios.h"

//PRE: -
// POS: realiza el recorrido en orden y anade elementos a la lista
void recorrerIOyA(NodoABInt* nodo, ListaOrdInt& lista) {
    if (nodo == NULL) {
        return;      }

    recorrerIOyA(nodo->izq, lista);
    agregar(lista, nodo->dato);
    recorrerIOyA(nodo->der, lista);
}

ListaOrdInt Enlistar(NodoABInt* a) {
    ListaOrdInt lista = crearListaOrdInt();
    recorrerIOyA(a, lista);
    return lista;
}

ListaOrdInt UnionListaOrd(ListaOrdInt l1, ListaOrdInt l2)
{
    ListaOrdInt copiaL1 = clon(l1);
    ListaOrdInt copiaL2 = clon(l2);

    ListaOrdInt listaUnion = crearListaOrdInt();

   while (!esVacia(copiaL1) && !esVacia(copiaL2)) {
        if (minimo(copiaL1) < minimo(copiaL2)) {
            agregar(listaUnion, minimo(copiaL1));
            borrarMinimo(copiaL1);
        }
        else {
            agregar(listaUnion, minimo(copiaL2));
            borrarMinimo(copiaL2);
        }
    }

    while (!esVacia(copiaL1)) {
        agregar(listaUnion, minimo(copiaL1));
        borrarMinimo(copiaL1);
    }
    while (!esVacia(copiaL2)) {
        agregar(listaUnion, minimo(copiaL2));
        borrarMinimo(copiaL2);
    }

    destruir(copiaL1);
    destruir(copiaL2);

    return listaUnion;
}

bool EstaContenida(PilaInt p1, PilaInt p2) {
    
    if (esVacia(p1)) {
        return true;
    }

    
    PilaInt clonP1 = clon(p1);
    PilaInt clonP2 = clon(p2);

    while (!esVacia(clonP1)) {
        int elem = top(clonP1);
        unsigned int cuentaEnP1 = 0;
        unsigned int cuentaEnP2 = 0;

        PilaInt tempP1 = clon(clonP1);
        while (!esVacia(tempP1)) {
            if (top(tempP1) == elem) {
                cuentaEnP1++;
            }
            pop(tempP1);
        }
        destruir(tempP1);

       
        PilaInt tempP2 = clon(clonP2);
        while (!esVacia(tempP2)) {
            if (top(tempP2) == elem) {
                cuentaEnP2++;
            }
            pop(tempP2);
        }
        destruir(tempP2);

        if (cuentaEnP2 < cuentaEnP1) {
            destruir(clonP1);
            destruir(clonP2);
            return false;
        }

       while (!esVacia(clonP1) && top(clonP1) == elem) {
            pop(clonP1);
        }
    }

    destruir(clonP1);
    destruir(clonP2);
    return true;
}




ListaOrdInt ObtenerRepetidos(MultisetInt m) {
    ListaOrdInt lista = crearListaOrdInt();
    MultisetInt copiaM = clon(m);

    while (!esVacio(copiaM)) {
        int elem = elemento(copiaM);
        unsigned int ocurrencias = 0;

        MultisetInt temp = clon(copiaM);
        while (pertenece(temp, elem)) {
            ocurrencias++;
            borrar(temp, elem);
        }
        destruir(temp);

        if (ocurrencias > 1 && !existe(lista, elem)) {
            agregar(lista, elem);
        }

        while (pertenece(copiaM, elem)) {
            borrar(copiaM, elem);
        }
    }

    destruir(copiaM);
    return lista;
}

MultisetInt Xor(MultisetInt m1, MultisetInt m2) {
    MultisetInt resultado = crearMultisetInt();
    MultisetInt copiaM1 = clon(m1);
    MultisetInt copiaM2 = clon(m2);

    while (!esVacio(copiaM1)) {
        int elem = elemento(copiaM1);
        unsigned int ocurrencias1 = 0;

        MultisetInt temp = clon(copiaM1);
        while (pertenece(temp, elem)) {
            ocurrencias1++;
            borrar(temp, elem);
        }
        destruir(temp);

        unsigned int ocurrencias2 = 0;
        temp = clon(copiaM2);
        while (pertenece(temp, elem)) {
            ocurrencias2++;
            borrar(temp, elem);
        }
        destruir(temp);

        if (ocurrencias1 != ocurrencias2) {
            int diferencia = abs((int)ocurrencias1 - (int)ocurrencias2);
            agregar(resultado, elem, diferencia);
        }

        while (pertenece(copiaM1, elem)) {
            borrar(copiaM1, elem);
        }

        while (pertenece(copiaM2, elem)) {
            borrar(copiaM2, elem);
        }
    }

    while (!esVacio(copiaM2)) {
        int elem = elemento(copiaM2);
        unsigned int ocurrencias2 = 0;

        MultisetInt temp = clon(copiaM2);
        while (pertenece(temp, elem)) {
            ocurrencias2++;
            borrar(temp, elem);
        }
        destruir(temp);

        if (!pertenece(m1, elem)) {
            agregar(resultado, elem, ocurrencias2);
        }

        while (pertenece(copiaM2, elem)) {
            borrar(copiaM2, elem);
        }
    }

    destruir(copiaM1);
    destruir(copiaM2);
    return resultado;
}

ColaPrioridadInt MenorPrioridad(ColaPrioridadInt c) {
    if (esVacia(c)) {
        return crearColaPrioridadInt(0);
    }

    int menorPrioridad = principioPrioridad(c);
    ColaPrioridadInt temp = clon(c);
    desencolar(temp);
    while (!esVacia(temp)) {
        if (principioPrioridad(temp) < menorPrioridad) {
            menorPrioridad = principioPrioridad(temp);
        }
        desencolar(temp);
    }
    destruir(temp);

    unsigned int numElementosMenorPrioridad = 0;
    temp = clon(c);
    while (!esVacia(temp)) {
        if (principioPrioridad(temp) == menorPrioridad) {
            numElementosMenorPrioridad++;
        }
        desencolar(temp);
    }
    destruir(temp);

    ColaPrioridadInt resultado = crearColaPrioridadInt(numElementosMenorPrioridad);

    temp = clon(c);
    while (!esVacia(temp)) {
        if (principioPrioridad(temp) == menorPrioridad) {
            encolar(resultado, principio(temp), principioPrioridad(temp));
        }
        desencolar(temp);
    }
    destruir(temp);

    return resultado;
}

