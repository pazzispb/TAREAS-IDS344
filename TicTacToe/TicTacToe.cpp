/*

TicTacToe.cpp
Materia - Estructuras de Datos y Algoritmos II

Asunto: 

Realizar un programa que simule el juego de Tic Tac Toe.

Autor:  Pazzis Paulino 1103790
        Huan Hao Wu 1104326
        Johan Contreras 1106473
        Luis Adames 1106170
        Paola Saldana 1104081
        
Fecha: 08 - Diciembre - 2022

*/

#include <iostream>
#include <math.h>
#include <windows.h> //HANDLE, COORD, SetConsoleCursorPosition, GetStdHandle
#include <cstdlib>
#include <time.h>

using namespace std;

//Variables globales

char jugada[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}}; // arreglo que almacenara los diferentes valores del juego
char simbolo = 'X'; //Variable que almacenara el simbolo del jugador en cada turno
bool empate = false; //bandera para saber si la jugada fue un empate
int turnoJugador = 0; //Variable que indica a cual jugador le toca
int fila = 0, columna = 0; //Posicion de una jugada
string nombreJugador1, nombreJugador2; //nombres de los jugadores
int contadorJugadas = 0;

//prototipo de metodos y funciones
string ImprimirNombreJugador(int numero);
void ComenzarJugada();
void ImprimirJuego(); //imprime las posiciones del arreglo
void ImprimirTablero(); //imprime el banner del tablero
void SeleccionarPosicion();
void CambiarTurno();
bool ExaminarJugada(); //devuelve true si hubo un empato o un ganador, false si todavía no se determina un ganador o empate
void ImprimirResultadoJuego();

void Gotoxy(short x, short y);
string CapturarEntrada(string mensaje, char tipo); //tipo especifica la validacion a realizar, n es numerico y a es alfabetico
bool ValidarEntrada(string entrada, char tipo);

//funcion principal

int main(){
	ComenzarJugada();
    return 0;
}

// definiciones de funciones


void ComenzarJugada(){
	nombreJugador1 = CapturarEntrada("Introduzca el nombre del primer jugador: ", 'a');

    nombreJugador2 = CapturarEntrada("Introduzca el nombre del segundo jugador: ", 'a');
    
	srand((unsigned) time(NULL)); //Seed para comenzar a generar números aleatorios

	int moneda = 1 + rand() % 2; //Simula el lanzamiento de una moneda. Genera 1 --> Cara, 2 --> Cruz
	
	if(moneda == 1){
		turnoJugador = moneda;
		cout << "El jugador 1 "<< nombreJugador1 << " comenzara a jugar con el simbolo X" << endl;
		cout << "El jugador 2 "<< nombreJugador2 << " le seguira con el simbolo O" << endl;
	}
	else{
		turnoJugador = moneda;
		cout << "El jugador 2 "<< nombreJugador2 << " comenzara a jugar con el simbolo X" << endl;
		cout << "El jugador 1 "<< nombreJugador1 << " le seguira con el simbolo O" << endl;
	}
	system("pause");
    bool fin = false; //variable para indicar si el juego se acabo
    while(true){ // Se repetira hasta que haya un empate o un ganador
        ImprimirTablero();
        SeleccionarPosicion();
		fin = ExaminarJugada(); //verifica si el juego finalizo
		if(!fin){
			CambiarTurno();	
		}
		else{
			break; //para finalizar la partida
		}    
    }
    system("cls");
    ImprimirTablero();
	ImprimirResultadoJuego();
}


void ImprimirTablero(){
	system("cls");
	Gotoxy(0,0);
	cout << "______________________" << endl;
	cout << "|    TIC  TAC TOE    |" << endl;
	cout << "|____________________|" << endl;
	cout << "|      |      |      |" << endl;
	cout << "|______|______|______|" << endl;
	cout << "|      |      |      |" << endl;
	cout << "|______|______|______|" << endl;
	cout << "|      |      |      |" << endl;
	cout << "|______|______|______|" << endl;
	ImprimirJuego();
}

void Gotoxy(short x, short y) // se invoca la funcion GoToXY la cual admite dos valores enteros uno para X y otro para Y
{
	HANDLE hConsoleOutput;
	COORD Cursor_Pos = {x, y};

	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_Pos);
}

void ImprimirJuego(){ // Funcion que muestra la formadel juego
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //toma control de la consola

	for (int i = 0; i < 3; i++){ //recorre las posiciones de la matriz
		for (int j = 0; j < 3; j++){
			Gotoxy(3 + i*7,3 + j*2);
			if(jugada[j][i] == 'O') SetConsoleTextAttribute(h, 2); //Verde
			else if(jugada[j][i] == 'X') SetConsoleTextAttribute(h, 4); //Rojo
			else SetConsoleTextAttribute(h, 7); //Blanco
			cout << jugada[j][i];
		}	
	}
	SetConsoleTextAttribute(h, 7); //Blanco
	Gotoxy(0,10);
}
string ImprimirNombreJugador(int numero){
	if(numero == 1) return nombreJugador1; //retorna el nombre del jugador 1
	else return nombreJugador2; //retorna el nombre del jugador 2
}

void SeleccionarPosicion(){ // Funcion donde indicamos en que posicion el jugador quiere jugar
	string mensaje = ImprimirNombreJugador(turnoJugador) + ", indique la posicion en donde desea jugar: ";
	int digito;
	do{	
		digito = stoi(CapturarEntrada(mensaje, 'n')); //captura la posicion numerica
		if(digito > 6){
			fila = 3;
			columna = digito - 6;	
		}
		else if(digito > 3){
			fila = 2;
			columna = digito - 3;
		}
		else{
			fila = 1;
			columna = digito;
		}
		
		if(isalpha(jugada[fila-1][columna-1])){ //si la posicion posee un caracter alfabetico X o O, significa que esta ocupada
			cout<<"La posicion esta ocupada, intente otra." << endl;
			continue;
		}
		else{
			break;
		}	
	}while(true);
	jugada[fila - 1][columna - 1] = simbolo;
	contadorJugadas++;
}

void CambiarTurno(){
    if(simbolo == 'X'){ // si la posicion no esta ocupada, entonces colocamos la x
        simbolo = 'O'; // el valor del simbolo cambia para poder usarlo con el siguiente jugador
        if(turnoJugador == 1) turnoJugador = 2; //se especifica el cambio de turno
        else turnoJugador = 1;
    }
    else{
    	simbolo = 'X';
    	if(turnoJugador == 1) turnoJugador = 2; //se especifica el cambio de turno
        else turnoJugador = 1;
	}
}

bool ExaminarJugada(){
	for(int i = 0; i < 3; i++){
        if(jugada[i][0] == jugada[i][1] && jugada[i][0] == jugada[i][2] || //verifica si hay combinaciones en horizontal
			jugada[0][i] == jugada[1][i] && jugada[0][i] == jugada[2][i]){ //verifica si hay combinaciones en vertical
            return true; //en caso de existir una combinacion, se retorna true
        }
    }
    
	if(jugada[0][0] == jugada[1][1] && jugada[1][1] == jugada[2][2] || 
		jugada[0][2] == jugada[1][1] && jugada[1][1] == jugada[2][0]){
        return true; // Para verificar de forma diagonal si se ha logrado alguna combinacion, en caso de existir una combinacion, se retorna true
    }
    
	for(int i = 0; i < 3; i++){ //recorre todo el tablero
        for(int j = 0; j < 3; j++){
            if(isdigit(jugada[j][i])){ // si algun campo aun ocupa la posicion significa que esta vacio, se continua con el programa retornando false
                return false;
            }
        }
    }
    
	if(contadorJugadas == 9){ //si ya se ocuparon todas las casillas y no se ha retornado la funcion significa que es un empate
		empate = true;
		return empate;
	}
}

void ImprimirResultadoJuego(){ // funcion para determinar el ganador o si quedo empate

    if(empate){
    	cout << "Vaya vaya, es un empate. " << nombreJugador1 << " y " << nombreJugador2 << " Ambos son buenos jugadores."<< endl << endl;
	}
	else{
		cout << "Wow!, " << ImprimirNombreJugador(turnoJugador) << " eres el ganador/a del juego. Felicidades!"<< endl << endl;
	}
    system("pause");
}

string CapturarEntrada(string mensaje, char tipo) //tipo == n -- si la entrada en numerica, tipo == a si la entrada es alfabetica  
{
	string entrada; //variable para almacenar la entrada
	bool correcta; //variable para verificar si la entrada es valida
	do{
	//se repetira hasta que el usuario ingrese una entrada valida 
		cout << mensaje;
		getline(cin, entrada); //Tome la entrada por pantalla
		correcta = ValidarEntrada(entrada, tipo); //Llama a la funcion para validar la entrada
		if(correcta == false) //si no es valida
		{
			cout << "Entrada no valida." << endl;
			system("pause");
		}
		cout << endl;
	} while (correcta == false); //repetir mientras que la entrada no sea valida
	return entrada; //retorna la entrada
}

bool ValidarEntrada(string entrada, char tipo){ //true - es valida       false - no es valida 
												//tipo == n -- si la entrada en numerica, tipo == a si la entrada es alfabetica 
	if(tipo == 'n'){ //validar una entrada numerica
		if(entrada.length() > 1){
			cout << "Excede la entrada esperada es solo un digito del 1 al 9" << endl;
			return false;
		}
		else{
			if(isdigit(entrada[0]) == false){
				cout << "La entrada debe ser un caracter numerico del 1 al 9" << endl;
				return false; //si no es un digito ni es el signo de '-'
			}
			
			if(entrada[0] - '0' < 1 ) { //valida el 0
				cout << "La entrada debe ser un caracter numerico del 1 al 9" << endl;
				return false; //si el digito no esta entre 1 y 9 retorna falso
			}
		}
		return true;
		
	}
	else{ //validar una entrada alfabetica
		
		for(int i = 0; i < entrada.length(); i++) //recorre todas las posiciones del string de entrada
		{
			if(isalpha(entrada[i]) == false && entrada[i] != ' '){
				cout << "La entrada solo debe poseer caracteres alfabeticos" << endl;
				return false; //si no es un caracter alfabetico o un espacio return falso
			}
		}
		
		return true;
	}	
}
