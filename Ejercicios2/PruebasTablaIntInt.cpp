#include "PruebasTablaIntInt.h"

void pruebasTablaIntIntNoAcotada(Prueba* pruebaConcreta);


void pruebasTablaIntInt(Prueba* pruebaConcreta) {
	pruebaConcreta->mImpresion.iniciarSeccion("PRUEBAS TablaIntInt");
	pruebasTablaIntIntNoAcotada(pruebaConcreta);
	pruebaConcreta->mImpresion.cerrarSeccion("PRUEBAS TablaIntInt");
}

void pruebasTablaIntIntNoAcotada(Prueba* pruebaConcreta) {

	TablaIntInt tabla = crearTablaIntInt(5);
	agregar(tabla, 1, 5);
	agregar(tabla, 2, 1);
	agregar(tabla, 3, -45);
	agregar(tabla, 4, 99);
	agregar(tabla, 5, 99);
	agregar(tabla, 5, -99);

	cout << "Largo de la tabla: " << cantidadElementos(tabla) << endl;
	pruebaConcreta->ver3("Imprimio largo luego de agregar 5 elementos");


	TablaIntInt clonTabla = clon(tabla);

	cout << "Largo del clon: " << cantidadElementos(tabla) << endl;
	pruebaConcreta->ver3("Imprimio largo del clon luego de clonar la tabla");

	NodoListaInt* lord = NULL;

	while (!esVacia(clonTabla)) {
		int elem = elemento(clonTabla);
		FrameworkA1::agregarOrd(lord, elem );
		borrar(clonTabla, elem);
	}

	char* salida = FrameworkA1::serializar(lord);
	FrameworkA1::destruir(lord);
	cout << "Elementos del dominio del Clon de la tabla: " << salida << endl;

	delete[] salida;

	pruebaConcreta->ver3("Clono e imprimo");
	cout << "Largo de clon luego de vaciarlo: " << cantidadElementos(clonTabla) << endl;
	cout << "Largo de Tabla luego de vaciar clon: " << cantidadElementos(tabla) << endl;
	pruebaConcreta->ver3("Verifico que se modifique el clon y no el original");



	agregar(tabla, 7, -20);

	agregar(tabla, 23, 66);

	cout << "Largo de la tabla luego de agregar dos elemento :" << cantidadElementos(tabla)<<endl;
	pruebaConcreta->ver3("Verifico que se agregue los elementos a la tabla");


	string estaDefinidoElemento = estaDefinida(tabla, 7)? " si ":" no ";

	cout << "El 7 " << estaDefinidoElemento << " esta definido en la tabla" << endl;
	pruebaConcreta->ver3("Verifico que el elemento 7 esta definido");

	int elementoRecuperado = recuperar(tabla,7);
	cout << "El elemento  de dominio 7 le corresponde : " << elementoRecuperado << endl;
	pruebaConcreta->ver3("Verifico que el elemento 7 tenga datos asociados");

	borrar(tabla, 7);
	estaDefinidoElemento = estaDefinida(tabla, 7) ? " si " : " no ";

	cout << "El 7 " << estaDefinidoElemento << " esta definido en la tabla" << endl;
	pruebaConcreta->ver3("Verifico que el elemento 7 no esta definido");

	TablaIntInt tabla2 = crearTablaIntInt(5);
	agregar(tabla2, 1, -5);
	int elem = elemento(tabla2);
	cout << "Consigo un dominio cualquiera de la tabla : " << elem << endl;
	destruir(tabla2);
	pruebaConcreta->ver3("Verifico que la tabla me devuelva un dominio cualquiera");

	string vacia = esVacia(tabla) ? " si " : " no ";
	cout << "La tabla " << vacia << " es vacia" << endl;
	pruebaConcreta->ver3("Verifico que la tabla no sea vacia");

	destruir(tabla);
	destruir(clonTabla);

	pruebaConcreta->ver3("Libero memoria");
}
