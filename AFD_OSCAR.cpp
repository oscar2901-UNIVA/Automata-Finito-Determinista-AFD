/*
* Nombre del programa: C++ - Autómata Finito Determinista
* Materia:Metodos formales
* Fecha:1 de agosto del 2020
* Proyecto final
* Profesor:Augusto Alberto Pacheco Comer
* Alumno:Oscar Javier Perez Torres
*/
#include <iostream>
#include <vector>
#include <ctype.h>
#include <sstream>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <iomanip>
#include <conio.h>
using namespace std;
struct conjuntoDeEstadosPosibles {
	string estadosPosiblesDatos;
	conjuntoDeEstadosPosibles* conjuntoDeEstadosPosiblesSiguientes;
};
struct principalMatriz {
	principalMatriz* matrizGsiguiente;
	principalMatriz* matrizGabajo;
	string matrizGdatos;
};
struct conjuntoDeEstadosDeAceptacion {
	string conjuntoDeEstadosDeAceptacionDatos;
	conjuntoDeEstadosDeAceptacion* conjuntoDeEstadosDeAceptacionSiguiente;
};
struct segundaMatriz {
	segundaMatriz* matrizTsiguiente;
	segundaMatriz* matrizTabajo;
	string matrizTdato;
};
struct alfabetosEntrada {
	string alfabetoDeEntradaDatos;
	alfabetosEntrada* alfabetoDeEntradaSiguiente;
};
struct alfabetosSalida {
	string alfabetoDeSalidaDatos;
	alfabetosSalida* siguienteAlfabetoSalida;
};
void fechaNombre();
void AlfabetoDeEntrada(alfabetosEntrada*&, string);
int alfabetosDeEntradaBusqueda(alfabetosEntrada*, string);
void alfabetoDeEntradaEliminar(alfabetosEntrada*&, string&);
void afdDeTraduccion();
int alfabetoDeEntradaPosicion(alfabetosEntrada*, string);
void AlfabetoDeEntradaActual(alfabetosEntrada*);
void insertarConjuntoEstados(conjuntoDeEstadosPosibles*&, string);
void afdDeValidacion();
void conjuntoDeEstadosPosiblesActual(conjuntoDeEstadosPosibles*);
int estadosPosiblesBusqueda(conjuntoDeEstadosPosibles*, string);
void estadosPosiblesEliminar(conjuntoDeEstadosPosibles*&, string&);
int estadosPosiblesPosicion(conjuntoDeEstadosPosibles*, string);
void insertarEstadosAceptacion(conjuntoDeEstadosDeAceptacion*&, string);
void estadosDeAceptacionEliminar(conjuntoDeEstadosDeAceptacion*&, string&);
void estadosDeAceptacionActual(conjuntoDeEstadosDeAceptacion*);
int estadosDeAceptacionBusqueda(conjuntoDeEstadosDeAceptacion*, string);
void AlfabetoDeSalidaActual(alfabetosSalida*);
int alfabetoDeSalidaBusqueda(alfabetosSalida*, string);
void AlfabetosDeSalida(alfabetosSalida*&, string);
void alfabetosDeSalidaEliminar(alfabetosSalida*&, string&);
string restriccionesParaLosAFDT();
string caracteresPermitidosMenu();
string nuevaPalabra();
conjuntoDeEstadosDeAceptacion* conjuntoDeEstadosDeAceptacionLista = NULL;
alfabetosSalida* alfabetosDeSalidaLista = NULL;
segundaMatriz* tMatriz = NULL;
conjuntoDeEstadosPosibles* conjuntoDeEstadosPosiblesLista = NULL;
alfabetosEntrada* alfabetosDeEntradaLista = NULL;
principalMatriz* gMatriz = NULL;
int rowCounter = 0;
int columnCounter = 0;
int counter = 0;
int totalnvalidWords = 0;
int AutomataFinitoDeterministaTotal = 0;
int totalTraslatedWord = 0;
int totalWordsValues = 0;
void fechaNombre() {
	system("cls");
	time_t t = time(0);
	tm* now = localtime(&t);
	cout << now->tm_mday << '/' << (now->tm_mon + 1) << '/' << (now->tm_year + 1900) << "\tOscar Javier Perez Torres \n\n\n";
}
int main(int argc, char** argv) {
	string verificar;
	int menu;
	do {
		fechaNombre();
		cout << "\n\t\t ----------------------M E N U-------------------\n\n";
		cout << "\n\t\t A U T O M A T A   F I N I T O   D E T E R M I N I S T A   E N   C + +\n\n";
		cout << "\n\t\t Programa elaborado por: Oscar Javier Perez Torres\n\n";
		cout << "\n\t\t Copyright 2021 Oscar Javier Perez Torres\n\n";
		cout << "\t 1. AFD Traductor\n";
		cout << "\t 2. AFD Validacion\n";
		cout << "\t 3. Salir\n";
		cout << "\t Ingrese la opcion deseada: ";
		verificar = caracteresPermitidosMenu();
		stringstream geek(verificar);
		geek >> menu;
		switch (menu) {
		case 1:
			system("cls");
			afdDeTraduccion();
			system("pause");
			system("cls");
			break;
		case 2:
			system("cls");
			afdDeValidacion();
			system("pause");
			system("cls");
			break;
		case 3:
			system("cls");
			fechaNombre();
			cout << "Total de automatas deterministas ingresados: " << AutomataFinitoDeterministaTotal << endl;
			cout << "Total de palabras validadas: " << totalWordsValues << endl;
			cout << "Total de palabras invalidadas: " << totalnvalidWords << endl;
			cout << "Total de palabras traducidas: " << totalTraslatedWord << endl;
			cout << "\nGracias por utilizar mi programa que tenga un bonito dia hasta luego :D\n" << endl;
			system("pause");
			break;
		default:
			cout << "\nPor favor seleccione una opcion del menu\n" << endl;
			system("pause");
			system("cls");
		}
	} while (menu != 3);
	return 0;
}
int alfabetosDeEntradaBusqueda(alfabetosEntrada* alfabetoDeEntradaLista, string x) {
	bool flag = false;
	alfabetosEntrada* present = new alfabetosEntrada();
	present = alfabetoDeEntradaLista;
	while ((present != NULL)) {
		if (present->alfabetoDeEntradaDatos == x) {
			flag = true;
		}
		present = present->alfabetoDeEntradaSiguiente;
	}
	if (flag == true) {

		return -1;
	}
	else {
		return 0;
	}
}
int estadosDeAceptacionBusqueda(conjuntoDeEstadosDeAceptacion* conjuntoDeEstadosDeAceptacionLista, string x) {
	bool flag = false;
	conjuntoDeEstadosDeAceptacion* present = new conjuntoDeEstadosDeAceptacion();
	present = conjuntoDeEstadosDeAceptacionLista;
	while ((present != NULL)) {
		if (present->conjuntoDeEstadosDeAceptacionDatos == x) {
			flag = true;
		}
		present = present->conjuntoDeEstadosDeAceptacionSiguiente;
	}
	if (flag == true) {
		return -1;
	}
	else {
		return 0;
	}
}
int estadosPosiblesBusqueda(conjuntoDeEstadosPosibles* conjuntoDeEstadosPosiblesLista, string x) {
	bool flag = false;
	conjuntoDeEstadosPosibles* present = new conjuntoDeEstadosPosibles();
	present = conjuntoDeEstadosPosiblesLista;
	while ((present != NULL)) {
		if (present->estadosPosiblesDatos == x) {
			flag = true;
		}
		present = present->conjuntoDeEstadosPosiblesSiguientes;
	}
	if (flag == true) {
		return -1;
	}
	else {
		return 0;
	}
}
int alfabetoDeSalidaBusqueda(alfabetosSalida* alfabetoDeSalidaLista, string x) {
	bool flag = false;
	alfabetosSalida* present = new alfabetosSalida();
	present = alfabetoDeSalidaLista;
	while ((present != NULL)) {
		if (present->alfabetoDeSalidaDatos == x) {
			flag = true;
		}
		present = present->siguienteAlfabetoSalida;
	}
	if (flag == true) {
		return -1;
	}
	else {
		return 0;
	}
}
string restriccionesParaLosAFDT() {
	string datoIngresado[255];
	string datoFinal;
	int contenidoIngresado = 0;
	bool maximo = false;
	char in;
	do {
		in = _getch();
		if (contenidoIngresado < 100) {
			if (isalpha(in) || isdigit(in) || in == '*') {
				_putch(in);
				datoIngresado[contenidoIngresado] = in;
				contenidoIngresado++;
			}if (in == '\xA5') {
				_putch('Ñ');
				datoIngresado[contenidoIngresado] = in;
				contenidoIngresado++;
			}if (in == '\xA4') {
				_putch('ñ');
				datoIngresado[contenidoIngresado] = in;
				contenidoIngresado++;
			}
		}
		if (in == '\x08') {
			if (contenidoIngresado != 0) {
				_putch(in);
				_putch(0);
				_putch(in);
				contenidoIngresado--;
				datoIngresado[contenidoIngresado] = "";
			}
		}
		if (contenidoIngresado > 0) {
			if (in == 13) {
				maximo = true;
			}
		}
	} while (maximo == false);
	for (int i = 0; i < contenidoIngresado + 1; i++) {
		datoFinal = datoFinal + datoIngresado[i];
	}
	return datoFinal;
}
void AlfabetoDeEntrada(alfabetosEntrada*& alfabetoDeEntradaLista, string x) {
	alfabetosEntrada* nodoNuevo = new alfabetosEntrada();
	nodoNuevo->alfabetoDeEntradaDatos = x;
	alfabetosEntrada* n1 = alfabetoDeEntradaLista;
	alfabetosEntrada* n2;
	while ((n1 != NULL)) {
		n2 = n1;
		n1 = n1->alfabetoDeEntradaSiguiente;
	}
	if (alfabetoDeEntradaLista == n1) {
		alfabetoDeEntradaLista = nodoNuevo;
	}
	else {
		n2->alfabetoDeEntradaSiguiente = nodoNuevo;
	}
	nodoNuevo->alfabetoDeEntradaSiguiente = n1;
	cout << "\nAgregado........\n" << endl;
	counter++;
}
void AlfabetosDeSalida(alfabetosSalida*& alfabetoDeSalidaLista, string x) {
	alfabetosSalida* nodoNuevo = new alfabetosSalida();
	nodoNuevo->alfabetoDeSalidaDatos = x;
	alfabetosSalida* n1 = alfabetoDeSalidaLista;
	alfabetosSalida* n2;
	while ((n1 != NULL)) {
		n2 = n1;
		n1 = n1->siguienteAlfabetoSalida;
	}
	if (alfabetoDeSalidaLista == n1) {
		alfabetoDeSalidaLista = nodoNuevo;
	}
	else {
		n2->siguienteAlfabetoSalida = nodoNuevo;
	}
	nodoNuevo->siguienteAlfabetoSalida = n1;
	cout << "\nAgregado........\n" << endl;
	counter++;
}
void insertarConjuntoEstados(conjuntoDeEstadosPosibles*& conjuntoDeEstadosPosiblesLista, string x) {
	conjuntoDeEstadosPosibles* nodoNuevo = new conjuntoDeEstadosPosibles();
	nodoNuevo->estadosPosiblesDatos = x;
	conjuntoDeEstadosPosibles* n1 = conjuntoDeEstadosPosiblesLista;
	conjuntoDeEstadosPosibles* n2;
	while ((n1 != NULL)) {
		n2 = n1;
		n1 = n1->conjuntoDeEstadosPosiblesSiguientes;
	}
	if (conjuntoDeEstadosPosiblesLista == n1) {
		conjuntoDeEstadosPosiblesLista = nodoNuevo;
	}
	else {
		n2->conjuntoDeEstadosPosiblesSiguientes = nodoNuevo;
	}
	nodoNuevo->conjuntoDeEstadosPosiblesSiguientes = n1;
	cout << "\nAgregado........\n" << endl;
	counter++;
}
void insertarEstadosAceptacion(conjuntoDeEstadosDeAceptacion*& conjuntoDeEstadosDeAceptacionLista, string x) {
	conjuntoDeEstadosDeAceptacion* nodoNuevo = new conjuntoDeEstadosDeAceptacion();
	nodoNuevo->conjuntoDeEstadosDeAceptacionDatos = x;
	conjuntoDeEstadosDeAceptacion* n1 = conjuntoDeEstadosDeAceptacionLista;
	conjuntoDeEstadosDeAceptacion* n2;
	while ((n1 != NULL)) {
		n2 = n1;
		n1 = n1->conjuntoDeEstadosDeAceptacionSiguiente;
	}
	if (conjuntoDeEstadosDeAceptacionLista == n1) {
		conjuntoDeEstadosDeAceptacionLista = nodoNuevo;
	}
	else {
		n2->conjuntoDeEstadosDeAceptacionSiguiente = nodoNuevo;
	}
	nodoNuevo->conjuntoDeEstadosDeAceptacionSiguiente = n1;
	cout << "\nAgregado........\n" << endl;
	counter++;
}
void AlfabetoDeEntradaActual(alfabetosEntrada* alfabetoDeEntradaLista) {
	alfabetosEntrada* present = new alfabetosEntrada();
	present = alfabetoDeEntradaLista;
	cout << "\n+++++++++Alfabetos de entrada actual: ";
	while (present != NULL) {
		cout << present->alfabetoDeEntradaDatos << " ";
		present = present->alfabetoDeEntradaSiguiente;
		columnCounter++;
	}
}
string nuevaPalabra() {
	char in;
	string datoIngresado[255];
	int contenidoIngresado = 0;
	bool maximo = false;
	string datoFinal;
	do {
		in = _getch();
		if (contenidoIngresado < 1) {
			if (in == 'N') {
				_putch('N');
				datoIngresado[contenidoIngresado] = in;
				contenidoIngresado++;
			}
			if (in == 'S') {
				_putch('S');
				datoIngresado[contenidoIngresado] = in;
				contenidoIngresado++;
			}
			if (in == 'n') {
				_putch('n');
				datoIngresado[contenidoIngresado] = in;
				contenidoIngresado++;
			}
			if (in == 's') {
				_putch('s');
				datoIngresado[contenidoIngresado] = in;
				contenidoIngresado++;
			}
		}
		if (in == '\x08') {
			if (contenidoIngresado != 0) {
				_putch(in);
				_putch(0);
				_putch(in);
				contenidoIngresado--;
				datoIngresado[contenidoIngresado] = "";
			}
		}
		if (contenidoIngresado > 0) {
			if (in == 13) {
				maximo = true;
			}
		}
	} while (maximo == false);
	for (int i = 0; i < contenidoIngresado + 1; i++) {
		datoFinal = datoFinal + datoIngresado[i];
	}
	return datoFinal;
}
void AlfabetoDeSalidaActual(alfabetosSalida* alfabetoDeSalidaLista) {
	alfabetosSalida* present = new alfabetosSalida();
	present = alfabetoDeSalidaLista;
	cout << "\n+++++++++Alfabetos de salida actual: ";
	while (present != NULL) {
		cout << present->alfabetoDeSalidaDatos << " ";
		present = present->siguienteAlfabetoSalida;
	}
}
void conjuntoDeEstadosPosiblesActual(conjuntoDeEstadosPosibles* conjuntoDeEstadosDeAceptacionLista) {
	conjuntoDeEstadosPosibles* present = new conjuntoDeEstadosPosibles();
	present = conjuntoDeEstadosDeAceptacionLista;
	cout << "\n+++++++++Conjunto de estados posibles actual: ";
	while (present != NULL) {
		cout << present->estadosPosiblesDatos << " ";
		present = present->conjuntoDeEstadosPosiblesSiguientes;
		rowCounter++;
	}
}
void estadosDeAceptacionActual(conjuntoDeEstadosDeAceptacion* conjuntoDeEstadosDeAceptacionLista) {
	conjuntoDeEstadosDeAceptacion* present = new conjuntoDeEstadosDeAceptacion();
	present = conjuntoDeEstadosDeAceptacionLista;
	cout << "\n+++++++++Conjunto de estados de aceptacion actual: ";
	while (present != NULL) {
		cout << present->conjuntoDeEstadosDeAceptacionDatos << " ";
		present = present->conjuntoDeEstadosDeAceptacionSiguiente;
	}
}
void alfabetoDeEntradaEliminar(alfabetosEntrada*& alfabetoDeEntradaLista, string& x) {
	alfabetosEntrada* n = alfabetoDeEntradaLista;
	x = n->alfabetoDeEntradaDatos;
	alfabetoDeEntradaLista = n->alfabetoDeEntradaSiguiente;
	delete n;
}
void alfabetosDeSalidaEliminar(alfabetosSalida*& alfabetoDeSalidaLista, string& x) {
	alfabetosSalida* n = alfabetoDeSalidaLista;
	x = n->alfabetoDeSalidaDatos;
	alfabetoDeSalidaLista = n->siguienteAlfabetoSalida;
	delete n;
}
void estadosPosiblesEliminar(conjuntoDeEstadosPosibles*& conjuntoDeEstadosPosiblesLista, string& x) {
	conjuntoDeEstadosPosibles* n = conjuntoDeEstadosPosiblesLista;
	x = n->estadosPosiblesDatos;
	conjuntoDeEstadosPosiblesLista = n->conjuntoDeEstadosPosiblesSiguientes;
	delete n;
}
void estadosDeAceptacionEliminar(conjuntoDeEstadosDeAceptacion*& conjuntoDeEstadosPosiblesLista, string& x) {
	conjuntoDeEstadosDeAceptacion* n = conjuntoDeEstadosPosiblesLista;
	x = n->conjuntoDeEstadosDeAceptacionDatos;
	conjuntoDeEstadosPosiblesLista = n->conjuntoDeEstadosDeAceptacionSiguiente;
	delete n;
}
int alfabetoDeEntradaPosicion(alfabetosEntrada* alfabetoDeEntradaLista, string x) {
	bool flag = false;
	int counter = 1;
	alfabetosEntrada* present = new alfabetosEntrada();
	present = alfabetoDeEntradaLista;
	while ((present != NULL)) {
		if (present->alfabetoDeEntradaDatos == x) {
			flag = true;
			break;
		}
		present = present->alfabetoDeEntradaSiguiente;
		counter++;
	}
	if (flag == true) {
		return counter;
	}
	else {
		return -1;
	}

}
int estadosPosiblesPosicion(conjuntoDeEstadosPosibles* conjuntoDeEstadosPosiblesLista, string x) {
	bool flag = false;
	int counter = 1;
	conjuntoDeEstadosPosibles* present = new conjuntoDeEstadosPosibles();
	present = conjuntoDeEstadosPosiblesLista;
	while ((present != NULL)) {
		if (present->estadosPosiblesDatos == x) {
			flag = true;
			break;
		}
		present = present->conjuntoDeEstadosPosiblesSiguientes;
		counter++;
	}
	if (flag == true) {
		return counter;
	}
	else {
		return -1;
	}
}
string caracteresPermitidosMenu() {
	string datoIngresado[255];
	string datoFinal;
	int contenidoIngresado = 0;
	bool maximo = false;
	char in;
	do {
		in = _getch();
		if (contenidoIngresado < 100) {
			if (isalpha(in) || isdigit(in)) {
				_putch(in);
				datoIngresado[contenidoIngresado] = in;
				contenidoIngresado++;
			}
			if (in == '\xA5') {
				_putch('Ñ');
				datoIngresado[contenidoIngresado] = in;
				contenidoIngresado++;
			}
			if (in == '\xA4') {
				_putch('ñ');
				datoIngresado[contenidoIngresado] = in;
				contenidoIngresado++;
			}
		}
		if (in == '\x08') {
			if (contenidoIngresado != 0) {
				_putch(in);
				_putch(0);
				_putch(in);
				contenidoIngresado--;
				datoIngresado[contenidoIngresado] = "";
			}
		}
		if (contenidoIngresado > 0) {
			if (in == 13) {
				maximo = true;
			}
		}
	} while (maximo == false);
	for (int i = 0; i < contenidoIngresado + 1; i++) {
		datoFinal = datoFinal + datoIngresado[i];
	}
	return datoFinal;
}
void afdDeTraduccion() {
	string alfabetoDeSimbolosDeEntrada;
	int conjuntoDeEstadosPosiblesValidos = 0;
	string alfabetoParaLosSimbolosDeSalida;
	int conjuntoDeEstadosInicialesValidos = 0;
	string estadosPosibles;
	int alfabetoDeEntradaValido = 0;
	string estadoInicialDeLaOperacion;
	int alfabetoDeSalidaValido = 0;
	string conjuntoDeEstadosDeAceptacion;
	int conjuntoDeEstadosDeAceptacionValido = 0;
	do {
		do {
			do {
				do {
					fechaNombre();
					cout << "\n-/-/-/-/-/-/-/-/-/-/-/A F D   T R A D U C T O R/-/-/-/-/-/-/-/-/-/-/- " << endl;
					cout << "\nIngrese un dato, al terminar de * y pulse enter para salir" << endl;
					cout << "\nAlfabeto de entrada: ";
					alfabetoDeSimbolosDeEntrada = restriccionesParaLosAFDT();
					if (alfabetoDeSimbolosDeEntrada.length() > 1) {
						cout << "\nERROR, por favor ingrese un alfabeto de entrada con cardinalidad 1 " << endl;
						system("pause");
						system("cls");
					}
				} while (alfabetoDeSimbolosDeEntrada.length() > 1);
				alfabetoDeEntradaValido = alfabetosDeEntradaBusqueda(alfabetosDeEntradaLista, alfabetoDeSimbolosDeEntrada);
				if (alfabetoDeEntradaValido == -1) {
					cout << "\nYa esta registrado ese valor, ingrese uno diferente." << endl;
					system("pause");
					system("cls");
				}
			} while (alfabetoDeEntradaValido != 0);
			if (alfabetoDeSimbolosDeEntrada != "*") {
				AlfabetoDeEntrada(alfabetosDeEntradaLista, alfabetoDeSimbolosDeEntrada);
				system("pause");
				system("cls");
			}
		} while (alfabetoDeSimbolosDeEntrada != "*");
		if (counter == 0) {
			cout << "\nNo se encontro ningun alfabeto de entrada por favor ingrese uno" << endl;
			system("pause");
			system("cls");
		}
	} while (counter == 0);
	counter = 0;
	columnCounter = 0;
	rowCounter = 0;
	system("cls");
	do {
		do {
			do {
				do {
					fechaNombre();
					cout << "\n-/-/-/-/-/-/-/-/-/-/-/A F D   T R A D U C T O R/-/-/-/-/-/-/-/-/-/-/- " << endl;
					AlfabetoDeEntradaActual(alfabetosDeEntradaLista);
					cout << "\nIngrese un dato, al terminar de * y pulse enter para salir" << endl;
					cout << "\nAlfabeto de simbolos de salida: ";
					alfabetoParaLosSimbolosDeSalida = restriccionesParaLosAFDT();
					if (alfabetoParaLosSimbolosDeSalida.length() > 1) {
						cout << "\nERROR, por favor ingrese un alfabeto de salida con cardinalidad 1" << endl;
						system("pause");
						system("cls");
					}
				} while (alfabetoParaLosSimbolosDeSalida.length() > 1);
				alfabetoDeSalidaValido = alfabetoDeSalidaBusqueda(alfabetosDeSalidaLista, alfabetoParaLosSimbolosDeSalida);
				if (alfabetoDeSalidaValido == -1) {
					cout << "\nYa esta registrado ese valor, ingrese uno diferente." << endl;
					system("pause");
					system("cls");
				}
			} while (alfabetoDeSalidaValido != 0);
			if (alfabetoParaLosSimbolosDeSalida != "*") {
				AlfabetosDeSalida(alfabetosDeSalidaLista, alfabetoParaLosSimbolosDeSalida);
				system("pause");
				system("cls");
			}
		} while (alfabetoParaLosSimbolosDeSalida != "*");
		if (counter == 0) {
			cout << "\nNo se encontro ningun alfabeto de salida por favor ingrese uno" << endl;
			system("pause");
			system("cls");
		}
	} while (counter == 0);
	counter = 0;
	columnCounter = 0;
	rowCounter = 0;
	system("cls");
	do {
		do {
			do {
				do {
					fechaNombre();
					cout << "\n-/-/-/-/-/-/-/-/-/-/-/A F D   T R A D U C T O R/-/-/-/-/-/-/-/-/-/-/- " << endl;
					AlfabetoDeEntradaActual(alfabetosDeEntradaLista);
					AlfabetoDeSalidaActual(alfabetosDeSalidaLista);
					cout << "\nIngrese un dato, al terminar de * y pulse enter para salir" << endl;
					cout << "\nConjunto de estado posibles: ";
					estadosPosibles = restriccionesParaLosAFDT();
					if (estadosPosibles.length() > 15) {
						cout << "\nERROR, por favor ingrese un conjunto de estado posible con cardinalidad 1" << endl;
						system("pause");
						system("cls");
					}
				} while (estadosPosibles.length() > 15);
				conjuntoDeEstadosPosiblesValidos = estadosPosiblesBusqueda(conjuntoDeEstadosPosiblesLista, estadosPosibles);
				if (conjuntoDeEstadosPosiblesValidos == -1) {
					cout << "\nYa esta registrado ese conjunto de estado posible, ingrese uno diferente." << endl;
					system("pause");
					system("cls");
				}
			} while (conjuntoDeEstadosPosiblesValidos != 0);
			if (estadosPosibles != "*") {
				insertarConjuntoEstados(conjuntoDeEstadosPosiblesLista, estadosPosibles);
				system("pause");
				system("cls");
			}
		} while (estadosPosibles != "*");
		if (counter == 0) {
			cout << "\nNo se encontro ningun conjunto de estados posible, por favor ingrese uno" << endl;
			system("pause");
			system("cls");
		}
	} while (counter == 0);
	counter = 0;
	columnCounter = 0;
	rowCounter = 0;
	system("cls");
	do {
		fechaNombre();
		cout << "\n-/-/-/-/-/-/-/-/-/-/-/A F D   T R A D U C T O R/-/-/-/-/-/-/-/-/-/-/- " << endl;
		AlfabetoDeEntradaActual(alfabetosDeEntradaLista);
		AlfabetoDeSalidaActual(alfabetosDeSalidaLista);
		conjuntoDeEstadosPosiblesActual(conjuntoDeEstadosPosiblesLista);
		cout << "\nIngrese un dato, al terminar de * y pulse enter para salir" << endl;
		cout << "\nEstado inicial de operacion: ";
		estadoInicialDeLaOperacion = caracteresPermitidosMenu();
		conjuntoDeEstadosInicialesValidos = estadosPosiblesBusqueda(conjuntoDeEstadosPosiblesLista, estadoInicialDeLaOperacion);
		if (conjuntoDeEstadosInicialesValidos == 0) {
			cout << "\nEl estado inicial de la operacion no pertenece al conjunto de estado posible, inserte uno diferente. " << endl;
			system("pause");
			system("cls");
		}
	} while (conjuntoDeEstadosInicialesValidos != -1);
	counter = 0;
	columnCounter = 0;
	rowCounter = 0;
	system("cls");
	do {
		do {
			do {
				fechaNombre();
				cout << "\n-/-/-/-/-/-/-/-/-/-/-/A F D   T R A D U C T O R/-/-/-/-/-/-/-/-/-/-/- " << endl;				
				AlfabetoDeEntradaActual(alfabetosDeEntradaLista);
				AlfabetoDeSalidaActual(alfabetosDeSalidaLista);
				conjuntoDeEstadosPosiblesActual(conjuntoDeEstadosPosiblesLista);
				cout << "\n+++++++++Estado inicial de operacion: " << estadoInicialDeLaOperacion;
				cout << "\nIngrese un dato, al terminar de * y pulse enter para salir" << endl;				
				cout << "\nConjunto de estados de aceptacion: ";
				conjuntoDeEstadosDeAceptacion = restriccionesParaLosAFDT();
				conjuntoDeEstadosPosiblesValidos = estadosPosiblesBusqueda(conjuntoDeEstadosPosiblesLista, conjuntoDeEstadosDeAceptacion);
				conjuntoDeEstadosDeAceptacionValido = estadosDeAceptacionBusqueda(conjuntoDeEstadosDeAceptacionLista, conjuntoDeEstadosDeAceptacion);
				
				if (conjuntoDeEstadosPosiblesValidos == 0 && conjuntoDeEstadosDeAceptacion != "*") {
					cout << "\nEl dato ingresado: '" + conjuntoDeEstadosDeAceptacion + " favor de ingresar uno distinto" << endl;
					system("pause");
					system("cls");
				}
				if (conjuntoDeEstadosDeAceptacionValido == -1 && conjuntoDeEstadosDeAceptacion != "*") {
					cout << "\nEl conjunto de estados de aceptacion ingresado  '" + conjuntoDeEstadosDeAceptacion + "' ya esta registaro. intente de nuevo" << endl;
					system("pause");
					system("cls");
				}
			} while ((conjuntoDeEstadosPosiblesValidos != -1 && conjuntoDeEstadosDeAceptacion != "*") || (conjuntoDeEstadosDeAceptacionValido == -1 && conjuntoDeEstadosDeAceptacion != "*"));
			if (conjuntoDeEstadosDeAceptacion != "*") {
				insertarEstadosAceptacion(conjuntoDeEstadosDeAceptacionLista, conjuntoDeEstadosDeAceptacion);
				system("pause");
				system("cls");
			}
		} while (conjuntoDeEstadosDeAceptacion != "*");
		if (counter == 0) {
			cout << "\nNo se encontro ningun conjunto de estados de aceptacion, por favor ingrese uno" << endl;
			system("pause");
			system("cls");
		}
	} while (counter == 0);
	counter = 0;
	columnCounter = 0;
	rowCounter = 0;
	AlfabetoDeEntradaActual(alfabetosDeEntradaLista);
	conjuntoDeEstadosPosiblesActual(conjuntoDeEstadosPosiblesLista);
	system("cls");
	int X;
	int	Y;
	X = rowCounter;
	Y = columnCounter;
	segundaMatriz* mat = new segundaMatriz();
	segundaMatriz* actual = mat;
	segundaMatriz* temporal = new segundaMatriz();
	temporal = NULL;
	conjuntoDeEstadosPosibles* actual2 = new conjuntoDeEstadosPosibles();
	actual2 = conjuntoDeEstadosPosiblesLista;
	string dato;
	for (int j = 0; j < X; j++) {
		alfabetosEntrada* actual3 = new alfabetosEntrada();
		actual3 = alfabetosDeEntradaLista;
		for (int i = 0; i < Y; i++) {
			do {
				counter = 0;
				columnCounter = 0;
				rowCounter = 0;
				system("cls");
				fechaNombre();
				cout << "\n-/-/-/-/-/-/-/-/-/-/-/A F D   T R A D U C T O R/-/-/-/-/-/-/-/-/-/-/- " << endl;
				AlfabetoDeEntradaActual(alfabetosDeEntradaLista);
				AlfabetoDeSalidaActual(alfabetosDeSalidaLista);
				conjuntoDeEstadosPosiblesActual(conjuntoDeEstadosPosiblesLista);
				cout << "\nEstado inicial de la operacion: " << estadoInicialDeLaOperacion;
				estadosDeAceptacionActual(conjuntoDeEstadosDeAceptacionLista);
				cout << "\n------------------------Capture la funcion de transicion------------------------------";
				cout << "\n[" << actual2->estadosPosiblesDatos << "] [" << actual3->alfabetoDeEntradaDatos << "] ";
				dato = caracteresPermitidosMenu();
				conjuntoDeEstadosPosiblesValidos = estadosPosiblesBusqueda(conjuntoDeEstadosPosiblesLista, dato);
				if (conjuntoDeEstadosPosiblesValidos == 0) {
					cout << "\n'" + dato + "' este dato no es valido, por favor ingresa otro " << endl;
					system("pause");
				}
			} while (conjuntoDeEstadosPosiblesValidos != -1);
			actual->matrizTdato = dato;
			if (temporal == NULL) {
				temporal = actual;
			}
			segundaMatriz* temp = new segundaMatriz();
			actual->matrizTsiguiente = temp;
			actual = temp;
			actual3 = actual3->alfabetoDeEntradaSiguiente;
			cout << "\n";
		}
		segundaMatriz* tempAbajo = new segundaMatriz();
		actual->matrizTabajo = tempAbajo;
		actual = tempAbajo;
		actual2 = actual2->conjuntoDeEstadosPosiblesSiguientes;
	}
	cout << "\n";
	principalMatriz* mat2 = new principalMatriz();
	principalMatriz* actual4 = mat2;
	principalMatriz* temporal2 = new principalMatriz();
	temporal2 = NULL;
	conjuntoDeEstadosPosibles* actual5 = new conjuntoDeEstadosPosibles();
	actual5 = conjuntoDeEstadosPosiblesLista;
	string h;
	for (int j = 0; j < X; j++) {

		alfabetosEntrada* actual6 = new alfabetosEntrada();
		actual6 = alfabetosDeEntradaLista;
		for (int i = 0; i < Y; i++) {
			do {
				counter = 0;
				columnCounter = 0;
				rowCounter = 0;
				system("cls");
				fechaNombre();
				cout << "\n-/-/-/-/-/-/-/-/-/-/-/A F D   T R A D U C T O R/-/-/-/-/-/-/-/-/-/-/- " << endl;
				AlfabetoDeEntradaActual(alfabetosDeEntradaLista);
				AlfabetoDeSalidaActual(alfabetosDeSalidaLista);
				conjuntoDeEstadosPosiblesActual(conjuntoDeEstadosPosiblesLista);
				cout << "\nEstado inicial de la operacion: " << estadoInicialDeLaOperacion;
				estadosDeAceptacionActual(conjuntoDeEstadosDeAceptacionLista);
				cout << "\nFuncion de transicion:";
				cout << "\nRegistrada...............";
				cout << "\n\------------------------Capture la funcion de traduccion------------------------------ " << endl;
				cout << "\n[" << actual5->estadosPosiblesDatos << "] [" << actual6->alfabetoDeEntradaDatos << "]";
				dato = caracteresPermitidosMenu();
				alfabetoDeSalidaValido = alfabetoDeSalidaBusqueda(alfabetosDeSalidaLista, dato);
				if (alfabetoDeSalidaValido == 0) {
					cout << "\n'" + dato + "' No es un valor valido, por favor ingresa otro." << endl;

					system("pause");
				}
			} while (alfabetoDeSalidaValido != -1);
			actual4->matrizGdatos = dato;
			if (temporal2 == NULL) {
				temporal2 = actual4;
			}
			principalMatriz* temp = new principalMatriz();
			actual4->matrizGsiguiente = temp;
			actual4 = temp;
			actual6 = actual6->alfabetoDeEntradaSiguiente;
			cout << "\n";
		}
		principalMatriz* tempAbajo = new principalMatriz();
		actual4->matrizGabajo = tempAbajo;
		actual4 = tempAbajo;
		actual5 = actual5->conjuntoDeEstadosPosiblesSiguientes;
	}
	counter = 0;
	columnCounter = 0;
	rowCounter = 0;
	system("cls");
	fechaNombre();
	cout << "\n-/-/-/-/-/-/-/-/-/-/-/A F D   T R A D U C T O R/-/-/-/-/-/-/-/-/-/-/- " << endl;
	AlfabetoDeEntradaActual(alfabetosDeEntradaLista);
	AlfabetoDeSalidaActual(alfabetosDeSalidaLista);
	conjuntoDeEstadosPosiblesActual(conjuntoDeEstadosPosiblesLista);
	cout << "\nEstado inicial de operacion: " << estadoInicialDeLaOperacion;
	estadosDeAceptacionActual(conjuntoDeEstadosDeAceptacionLista);
	cout << "\nFuncion de transicion................................................";
	cout << "\nRegistrado exitosamente.";
	cout << "\nFuncion de salida....................................................";
	cout << "\nRegistrada exitosamente.";
	cout << "\n\nEscriba la palabra a traducir. " << endl;
	string respuesta;
	int palabrasInvalidadas = 0;
	int palabrasValidadas = 0;
	int posicionDeAlfabetoDeEntrada = 0;
	int posicionDeEstadosPosibles = estadosPosiblesPosicion(conjuntoDeEstadosPosiblesLista, estadoInicialDeLaOperacion);
	int palabrasTraducidas = 0;
	int contador;
	int palabrasIngresadas = 0;
	do {
		contador = 0;
		columnCounter = 0;
		rowCounter = 0;
		system("cls");
		fechaNombre();
		cout << "\n-/-/-/-/-/-/-/-/-/-/-/A F D   T R A D U C T O R/-/-/-/-/-/-/-/-/-/-/- " << endl;
		AlfabetoDeEntradaActual(alfabetosDeEntradaLista);
		AlfabetoDeSalidaActual(alfabetosDeSalidaLista);
		conjuntoDeEstadosPosiblesActual(conjuntoDeEstadosPosiblesLista);
		cout << "\nEstado inicial de operacion: " << estadoInicialDeLaOperacion;
		estadosDeAceptacionActual(conjuntoDeEstadosDeAceptacionLista);
		cout << "\nFuncion de transicion................................................";
		cout << "\nRegistrado exitosamente.";
		cout << "\nFuncion de salida....................................................";
		cout << "\nRegistrada exitosamente.";
		string palabra;
		cout << "\nInserte la palabra a traducir: ";
		palabra = caracteresPermitidosMenu();
		cout << "\n";
		cout << "Palabra traducida: ";
		string intersectado;
		int	tamanoPalabra;
		bool encontrado = false;
		do {
			tamanoPalabra = palabra.length();
			for (int i = 1; i < tamanoPalabra + 1; i++) {
				string nuevaPalabra = palabra.substr(0, i);
				alfabetoDeEntradaValido = alfabetosDeEntradaBusqueda(alfabetosDeEntradaLista, nuevaPalabra);
				if (alfabetoDeEntradaValido == -1) {
					posicionDeAlfabetoDeEntrada = alfabetoDeEntradaPosicion(alfabetosDeEntradaLista, nuevaPalabra);
					segundaMatriz* prueba = new segundaMatriz();
					prueba = temporal;
					contador = 1;
					int res = (((posicionDeEstadosPosibles * Y) - Y) + posicionDeAlfabetoDeEntrada);
					while (prueba->matrizTsiguiente != NULL) {
						while (prueba->matrizTsiguiente != NULL) {
							if (prueba->matrizTsiguiente == NULL) {
							}
							else {
								if (res == contador) {
									intersectado = prueba->matrizTdato;
								}
								prueba = prueba->matrizTsiguiente;
							}
							contador++;
						}
						prueba = prueba->matrizTabajo;
					}
					principalMatriz* prueba2 = new principalMatriz();
					prueba2 = temporal2;
					contador = 1;
					while (prueba2->matrizGsiguiente != NULL) {
						while (prueba2->matrizGsiguiente != NULL) {
							if (prueba2->matrizGsiguiente == NULL) {
							}
							else {
								if (res == contador) {
									cout << prueba2->matrizGdatos;
								}
								prueba2 = prueba2->matrizGsiguiente;
							}
							contador++;
						}
						prueba2 = prueba2->matrizGabajo;
					}
					posicionDeEstadosPosibles = estadosPosiblesPosicion(conjuntoDeEstadosPosiblesLista, intersectado);
					palabra = palabra.substr(i, palabra.length());
					encontrado = true;
					break;
				}
				else {
					encontrado = false;
				}
			}
			if (encontrado == false) {
				break;
			}
		} while (encontrado == true && tamanoPalabra != 0);

		if (encontrado == false) {
			cout << "\n";
			cout << "   //ERROR, la traduccion no se completo de forma correcta favor de intentarlo nuevamente";
		}
		else {
			conjuntoDeEstadosDeAceptacionValido = estadosDeAceptacionBusqueda(conjuntoDeEstadosDeAceptacionLista, intersectado);
			if (conjuntoDeEstadosDeAceptacionValido == -1) {
				cout << "  -  CORRECTO PALABRA VALIDA" << endl;
				palabrasTraducidas++;
				totalTraslatedWord++;
				palabrasIngresadas++;
				palabrasValidadas++;
				totalWordsValues++;
			}
			else {
				cout << "   - ERROR PALABRA INVALIDA" << endl;
				palabrasTraducidas++;
				totalTraslatedWord++;
				palabrasIngresadas++;
				palabrasInvalidadas++;
				totalnvalidWords++;
			}
		}
		cout << "\n¿Le gustaria traducir otra palabra?";
		cout << "\n(s/n)";
		respuesta = nuevaPalabra();
		posicionDeEstadosPosibles = estadosPosiblesPosicion(conjuntoDeEstadosPosiblesLista, estadoInicialDeLaOperacion);
		posicionDeAlfabetoDeEntrada = 0;
	} while (respuesta == "s" || respuesta == "S");

	contador = 0;
	columnCounter = 0;
	rowCounter = 0;
	system("cls");
	fechaNombre();
	cout << "\n-/-/-/-/-/-/-/-/-/-/-/A F D   T R A D U C T O R/-/-/-/-/-/-/-/-/-/-/- " << endl;
	cout << "\nTotal de palabras AFD registrados: " << palabrasIngresadas << endl;
	cout << "Total de palabras traducidas: " << palabrasTraducidas << endl;
	cout << "Total de palabras validas: " << palabrasValidadas << endl;
	cout << "Total de palabras invalidas: " << palabrasInvalidadas << endl;
	while (alfabetosDeEntradaLista != NULL) {
		alfabetoDeEntradaEliminar(alfabetosDeEntradaLista, alfabetoDeSimbolosDeEntrada);
	}
	while (alfabetosDeSalidaLista != NULL) {
		alfabetosDeSalidaEliminar(alfabetosDeSalidaLista, alfabetoParaLosSimbolosDeSalida);
	}
	while (conjuntoDeEstadosPosiblesLista != NULL) {
		estadosPosiblesEliminar(conjuntoDeEstadosPosiblesLista, estadosPosibles);
	}
	while (conjuntoDeEstadosDeAceptacionLista != NULL) {
		estadosDeAceptacionEliminar(conjuntoDeEstadosDeAceptacionLista, conjuntoDeEstadosDeAceptacion);
	}
	for (int i = 0; i < contador; i++) {
		segundaMatriz* aux = new segundaMatriz();
		dato = aux->matrizTdato;
		mat = aux->matrizTsiguiente;
		delete aux;
	}
	for (int i = 0; i < contador; i++) {
		principalMatriz* aux = new principalMatriz();
		dato = aux->matrizGdatos;

		mat2 = aux->matrizGsiguiente;
		delete aux;
	}
	contador = 0;
	columnCounter = 0;
	rowCounter = 0;
	palabrasIngresadas = 0;
	palabrasTraducidas = 0;
	palabrasValidadas = 0;
	palabrasInvalidadas = 0;
	AutomataFinitoDeterministaTotal++;
}
void afdDeValidacion() {
	string alfabetoDeSimbolosDeEntrada;
	int alfabetoDeEntradaValido = 0;
	string alfabetoParaLosSimbolosDeSalida;
	string estadosPosibles;
	int conjuntoDeEstadosPosiblesValidos = 0;
	string estadoInicialDeLaOperacion;
	int conjuntoDeEstadosDeAceptacionValido = 0;
	string conjuntoDeEstadosDeAceptacion;
	int conjuntoDeEstadosInicialesValidos = 0;
	do {
		do {
			do {
				do {
					fechaNombre();
					cout << "\n-/-/-/-/-/-/-/-/-/-/-/A F D   D E  V A L I D A C I O N/-/-/-/-/-/-/-/-/-/-/- " << endl;
					cout << "\nIngrese un dato, al terminar de * y pulse enter para salir" << endl;
					cout << "\nAlfabeto de entrada: ";
					alfabetoDeSimbolosDeEntrada = restriccionesParaLosAFDT();
					if (alfabetoDeSimbolosDeEntrada.length() > 1) {
						cout << "\n ERROR, por favor ingrese un alfabeto de entrada con cardinalidad 1 " << endl;
						system("pause");
						system("cls");
					}
				} while (alfabetoDeSimbolosDeEntrada.length() > 1);
				alfabetoDeEntradaValido = alfabetosDeEntradaBusqueda(alfabetosDeEntradaLista, alfabetoDeSimbolosDeEntrada);
				if (alfabetoDeEntradaValido == -1) {
					cout << "\nYa esta registrado ese valor ingrese uno diferente." << endl;
					system("pause");
					system("cls");
				}
			} while (alfabetoDeEntradaValido != 0);
			if (alfabetoDeSimbolosDeEntrada != "*") {
				AlfabetoDeEntrada(alfabetosDeEntradaLista, alfabetoDeSimbolosDeEntrada);
				system("pause");
				system("cls");
			}
		} while (alfabetoDeSimbolosDeEntrada != "*");
		if (counter == 0) {
			cout << "\nNo se encontro ningun alfabeto de entrada por favor ingrese uno" << endl;
			system("pause");
			system("cls");
		}
	} while (counter == 0);
	counter = 0;
	columnCounter = 0;
	rowCounter = 0;
	system("cls");
	do {
		do {
			do {
				do {
					fechaNombre();
					cout << "\n-/-/-/-/-/-/-/-/-/-/-/A F D   D E  V A L I D A C I O N/-/-/-/-/-/-/-/-/-/-/- " << endl;
					AlfabetoDeEntradaActual(alfabetosDeEntradaLista);
					cout << "\nIngrese un dato, al terminar de * y pulse enter para salir" << endl;
					cout << "\nConjunto de estado posibles: ";
					estadosPosibles = restriccionesParaLosAFDT();
					if (estadosPosibles.length() > 15) {
						cout << "\nERROR, por favor ingrese un conjunto de estado posible con cardinalidad 1 " << endl;
						system("pause");
						system("cls");
					}
				} while (estadosPosibles.length() > 15);
				conjuntoDeEstadosPosiblesValidos = estadosPosiblesBusqueda(conjuntoDeEstadosPosiblesLista, estadosPosibles);
				if (conjuntoDeEstadosPosiblesValidos == -1) {
					cout << "\nYa esta registrado ese valor ingrese uno diferente." << endl;
					system("pause");
					system("cls");
				}
			} while (conjuntoDeEstadosPosiblesValidos != 0);
			if (estadosPosibles != "*") {
				insertarConjuntoEstados(conjuntoDeEstadosPosiblesLista, estadosPosibles);
				system("pause");
				system("cls");
			}
		} while (estadosPosibles != "*");
		if (counter == 0) {
			cout << "\nNo se encontro ningun conjunto de estado posible por favor ingrese uno" << endl;
			system("pause");
			system("cls");
		}
	} while (counter == 0);
	counter = 0;
	columnCounter = 0;
	rowCounter = 0;
	system("cls");
	do {
		fechaNombre();
		cout << "\n-/-/-/-/-/-/-/-/-/-/-/A F D   D E  V A L I D A C I O N/-/-/-/-/-/-/-/-/-/-/- " << endl;
		AlfabetoDeEntradaActual(alfabetosDeEntradaLista);
		conjuntoDeEstadosPosiblesActual(conjuntoDeEstadosPosiblesLista);
		cout << "\nIngrese un dato, al terminar de * y pulse enter para salir" << endl;
		cout << "\nEstado inicial de operacion: ";
		estadoInicialDeLaOperacion = caracteresPermitidosMenu();
		conjuntoDeEstadosInicialesValidos = estadosPosiblesBusqueda(conjuntoDeEstadosPosiblesLista, estadoInicialDeLaOperacion);
		if (conjuntoDeEstadosInicialesValidos == 0) {
			cout << "\nEl elemento de conjunto de estado de aceptacion no coincide, inserte uno diferente. " << endl;
			system("pause");
			system("cls");
		}
	} while (conjuntoDeEstadosInicialesValidos != -1);
	counter = 0;
	columnCounter = 0;
	rowCounter = 0;
	system("cls");
	do {
		do {
			do {
				fechaNombre();
				cout << "\n-/-/-/-/-/-/-/-/-/-/-/A F D   D E  V A L I D A C I O N/-/-/-/-/-/-/-/-/-/-/- " << endl;
				AlfabetoDeEntradaActual(alfabetosDeEntradaLista);
				conjuntoDeEstadosPosiblesActual(conjuntoDeEstadosPosiblesLista);
				cout << "\nEstado inicial de operacion: " << estadoInicialDeLaOperacion;
				cout << "\nIngrese un dato, al terminar de * y pulse enter para salir" << endl;
				cout << "\nConjunto de estado de aceptacion: ";
				conjuntoDeEstadosDeAceptacion = restriccionesParaLosAFDT();
				conjuntoDeEstadosPosiblesValidos = estadosPosiblesBusqueda(conjuntoDeEstadosPosiblesLista, conjuntoDeEstadosDeAceptacion);
				conjuntoDeEstadosDeAceptacionValido = estadosDeAceptacionBusqueda(conjuntoDeEstadosDeAceptacionLista, conjuntoDeEstadosDeAceptacion);
				if (conjuntoDeEstadosPosiblesValidos == 0 && conjuntoDeEstadosDeAceptacion != "*") {
					cout << "\nEl elemento de conjunto de estado de aceptacion '" + conjuntoDeEstadosDeAceptacion + "' no es valido por favor ingrese uno diferente" << endl;
					system("pause");
					system("cls");
				}
				if (conjuntoDeEstadosDeAceptacionValido == -1 && conjuntoDeEstadosDeAceptacion != "*") {
					cout << "\nEl elemento de conjunto de esta de aceptacion '" + conjuntoDeEstadosDeAceptacion + "' Ya esta registrado ese valor ingrese uno diferente." << endl;			
					system("pause");
					system("cls");
				}
			} while ((conjuntoDeEstadosPosiblesValidos != -1 && conjuntoDeEstadosDeAceptacion != "*") || (conjuntoDeEstadosDeAceptacionValido == -1 && conjuntoDeEstadosDeAceptacion != "*"));
			if (conjuntoDeEstadosDeAceptacion != "*") {
				insertarEstadosAceptacion(conjuntoDeEstadosDeAceptacionLista, conjuntoDeEstadosDeAceptacion);
				system("pause");
				system("cls");
			}
		} while (conjuntoDeEstadosDeAceptacion != "*");
		if (counter == 0) {
			cout << "\nNo se encontro ningun conjunto de estados de aceptacion, por favor ingrese uno" << endl;
			system("pause");
			system("cls");
		}
	} while (counter == 0);
	counter = 0;
	columnCounter = 0;
	rowCounter = 0;
	AlfabetoDeEntradaActual(alfabetosDeEntradaLista);
	conjuntoDeEstadosPosiblesActual(conjuntoDeEstadosPosiblesLista);
	system("cls");
	int X;
	int Y;
	X = rowCounter;
	Y = columnCounter;
	segundaMatriz* mat = new segundaMatriz();
	segundaMatriz* actual = mat;
	segundaMatriz* temporal = new segundaMatriz();
	temporal = NULL;
	conjuntoDeEstadosPosibles* actual2 = new conjuntoDeEstadosPosibles();
	actual2 = conjuntoDeEstadosPosiblesLista;
	string dato;
	for (int j = 0; j < X; j++) {
		alfabetosEntrada* actual3 = new alfabetosEntrada();
		actual3 = alfabetosDeEntradaLista;
		for (int i = 0; i < Y; i++) {
			do {
				counter = 0;
				columnCounter = 0;
				rowCounter = 0;
				system("cls");
				fechaNombre();
				cout << "\n-/-/-/-/-/-/-/-/-/-/-/A F D   D E  V A L I D A C I O N/-/-/-/-/-/-/-/-/-/-/- " << endl;
				AlfabetoDeEntradaActual(alfabetosDeEntradaLista);
				conjuntoDeEstadosPosiblesActual(conjuntoDeEstadosPosiblesLista);
				cout << "\nEstado inicial de la operacion: " << estadoInicialDeLaOperacion;
				estadosDeAceptacionActual(conjuntoDeEstadosDeAceptacionLista);
				cout << "\n-------------------------------Funcion de tarnsicion--------------------" << endl;
				cout << "\n[" << actual2->estadosPosiblesDatos << "] [" << actual3->alfabetoDeEntradaDatos << "]";
				dato = caracteresPermitidosMenu();
				conjuntoDeEstadosPosiblesValidos = estadosPosiblesBusqueda(conjuntoDeEstadosPosiblesLista, dato);
				if (conjuntoDeEstadosPosiblesValidos == 0) {
					cout << "\n'" + dato + "'no es un conjunto de estado valido, por favor ingrese otro." << endl;
					system("pause");
				}
			} while (conjuntoDeEstadosPosiblesValidos != -1);
			actual->matrizTdato = dato;
			if (temporal == NULL) {
				temporal = actual;
			}
			segundaMatriz* temp = new segundaMatriz();
			actual->matrizTsiguiente = temp;
			actual = temp;
			actual3 = actual3->alfabetoDeEntradaSiguiente;
			cout << "\n";
		}
		segundaMatriz* tempAbajo = new segundaMatriz();
		actual->matrizTabajo = tempAbajo;
		actual = tempAbajo;
		actual2 = actual2->conjuntoDeEstadosPosiblesSiguientes;
	}
	cout << "\n";
	counter = 0;
	columnCounter = 0;
	rowCounter = 0;
	system("cls");
	fechaNombre();
	cout << "\n-/-/-/-/-/-/-/-/-/-/-/A F D   D E  V A L I D A C I O N/-/-/-/-/-/-/-/-/-/-/- " << endl;
	AlfabetoDeEntradaActual(alfabetosDeEntradaLista);
	conjuntoDeEstadosPosiblesActual(conjuntoDeEstadosPosiblesLista);
	cout << "\nEstado inicial de operacion: " << estadoInicialDeLaOperacion;
	estadosDeAceptacionActual(conjuntoDeEstadosDeAceptacionLista);
	cout << "\nFuncion de transicion................................................";
	cout << "\nRegistrada exitosamente.";
	string respuesta;
	int palabrasIngresadas = 0;
	int palabrasValidadas = 0;
	int palabrasInvalidas = 0;
	int posicionDeEstadosPosibles = estadosPosiblesPosicion(conjuntoDeEstadosPosiblesLista, estadoInicialDeLaOperacion);
	int posicionDeAlfabetoDeEntrada = 0;
	int contador;
	do {
		contador = 0;
		columnCounter = 0;
		rowCounter = 0;
		system("cls");
		fechaNombre();
		cout << "\n-/-/-/-/-/-/-/-/-/-/-/A F D   D E  V A L I D A C I O N/-/-/-/-/-/-/-/-/-/-/- " << endl;
		AlfabetoDeEntradaActual(alfabetosDeEntradaLista);
		conjuntoDeEstadosPosiblesActual(conjuntoDeEstadosPosiblesLista);
		cout << "\nEstado inicial de operacion: " << estadoInicialDeLaOperacion;
		estadosDeAceptacionActual(conjuntoDeEstadosDeAceptacionLista);
		cout << "\nFuncion de transicion................................................";
		cout << "\nRegistrado exitosamente.";
		string palabra;
		cout << "\nEscribe la palabra a validar: ";
		palabra = caracteresPermitidosMenu();
		cout << "\n";
		string intersectado;
		int	tamanoPalabra;
		bool encontrado = false;
		do {
			tamanoPalabra = palabra.length();
			for (int i = 1; i < tamanoPalabra + 1; i++) {
				string nuevaPalabra = palabra.substr(0, i);
				alfabetoDeEntradaValido = alfabetosDeEntradaBusqueda(alfabetosDeEntradaLista, nuevaPalabra);
				if (alfabetoDeEntradaValido == -1) {
					posicionDeAlfabetoDeEntrada = alfabetoDeEntradaPosicion(alfabetosDeEntradaLista, nuevaPalabra);
					segundaMatriz* prueba = new segundaMatriz();
					prueba = temporal;
					contador = 1;
					int res = (((posicionDeEstadosPosibles * Y) - Y) + posicionDeAlfabetoDeEntrada);
					while (prueba->matrizTsiguiente != NULL) {
						while (prueba->matrizTsiguiente != NULL) {
							if (prueba->matrizTsiguiente == NULL) {
							}
							else {
								if (res == contador) {
									intersectado = prueba->matrizTdato;
								}
								prueba = prueba->matrizTsiguiente;
							}
							contador++;
						}
						prueba = prueba->matrizTabajo;
					}
					posicionDeEstadosPosibles = estadosPosiblesPosicion(conjuntoDeEstadosPosiblesLista, intersectado);
					palabra = palabra.substr(i, palabra.length());
					encontrado = true;
					break;
				}
				else {
					encontrado = false;
				}
			}
			if (encontrado == false) {
				break;
			}
		} while (encontrado == true && tamanoPalabra != 0);
		if (encontrado == false) {
			cout << endl << " ///////ERROR, la palabra no se pudo validar ya que no coincide con los valores registrados**********";
		}
		else {
			conjuntoDeEstadosDeAceptacionValido = estadosDeAceptacionBusqueda(conjuntoDeEstadosDeAceptacionLista, intersectado);
			if (conjuntoDeEstadosDeAceptacionValido == -1) {
				cout << endl<< " ----CORRECTO PALABRA VALIDA " << endl;
				palabrasIngresadas++;
				palabrasValidadas++;
				totalWordsValues++;
			}
			else {
				cout << endl << " ///////ERROR PALABRA INVALIDA" << endl;
				palabrasIngresadas++;
				palabrasInvalidas++;
				totalnvalidWords++;
			}
		}
		cout << "\n¿Le gustaria validar otra palabra?";
		cout << "\n(s/n)";
		respuesta = nuevaPalabra();
		posicionDeEstadosPosibles = estadosPosiblesPosicion(conjuntoDeEstadosPosiblesLista, estadoInicialDeLaOperacion);
		posicionDeAlfabetoDeEntrada = 0;
	} while (respuesta == "S" || respuesta == "s");
	contador = 0;
	columnCounter = 0;
	rowCounter = 0;
	system("cls");
	fechaNombre();
	cout << "\n-/-/-/-/-/-/-/-/-/-/-/A F D   D E  V A L I D A C I O N/-/-/-/-/-/-/-/-/-/-/- " << endl;
	cout << "\nTotal de AFD registrados: " << palabrasIngresadas << endl;
	cout << "Total de palabras validas: " << palabrasValidadas << endl;
	cout << "Total de palabras invalidas: " << palabrasInvalidas << endl;
	while (alfabetosDeEntradaLista != NULL) {
		alfabetoDeEntradaEliminar(alfabetosDeEntradaLista, alfabetoDeSimbolosDeEntrada);
	}
	while (conjuntoDeEstadosPosiblesLista != NULL) {
		estadosPosiblesEliminar(conjuntoDeEstadosPosiblesLista, estadosPosibles);
	}
	while (conjuntoDeEstadosDeAceptacionLista != NULL) {
		estadosDeAceptacionEliminar(conjuntoDeEstadosDeAceptacionLista, conjuntoDeEstadosDeAceptacion);
	}
	for (int i = 0; i < contador; i++) {
		segundaMatriz* aux = new segundaMatriz();
		dato = aux->matrizTdato;
		mat = aux->matrizTsiguiente;
		delete aux;
	}
	contador = 0;
	columnCounter = 0;
	rowCounter = 0;
	palabrasIngresadas = 0;
	palabrasValidadas = 0;
	palabrasInvalidas = 0;
	AutomataFinitoDeterministaTotal++;
}
