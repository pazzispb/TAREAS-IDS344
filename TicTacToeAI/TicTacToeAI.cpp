/*

TicTacToeAI.cpp
Materia - Estructuras de Datos y Algoritmos II

Asunto: 

Programar un juego de Tic Tac Toe contra una inteligencia artificial.

Autor:  Pazzis Paulino 1103790
        Huan Hao Wu 1104326
        Johan Contreras 1106473
        Luis Adames 1106170
        Paola Saldana 1104081
        
Fecha: 11 - Enero - 2023

*/

#include <iostream>
#include <math.h>
#include <windows.h> //HANDLE, COORD, SetConsoleCursorPosition, GetStdHandle
#include <cstdlib>
#include <time.h>
#include<conio.h>

using namespace std;

struct Posicion{
	int fila, columna;
};

//Variables globales

char jugada[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}}; // arreglo que almacenara los diferentes valores del juego
char simbolo = 'X'; //Variable que almacenara el simbolo del jugador en cada turno
bool empate = false; //bandera para saber si la jugada fue un empate
int turnoJugador = 0; //Variable que indica a cual jugador le toca
Posicion juego; //Posicion del arreglo jugadas
string nombreJugador1, nombreJugador2; //nombres de los jugadores
int contadorJugadas = 0;

bool AI = false; //Indica que esta jugando contra la AI

//Variables para determinar cual es el simbolo de la maquina y el del oponente
char maquina;
char oponente;


//Prototipo de metodos y funciones

//Funciones del funcionamiento del juego
void ComenzarJugada(); //Funcion para comenzar una jugada nueva
void SeleccionarPosicion(); //Funcion para asignar una posicion al tablero
void CambiarTurno(); //Funcion para cambiar el turno de un jugador a otro
int ExaminarJugada(); //devuelve un puntaje en funcion de la jugada realizada. +1 si gano la maquina o el jugador 2, -1 si gano el jugador 1, 0 si hay un empate

//Funciones para la Inteligencia Artificial
int MejorJugada(); //Funcion que determina la mejor jugada para la AI
int MiniMax(int nivel, bool isMaximizing); //Funcion que maximiza o minimiza una jugada

//Funciones para las salidas del juego
void Menu(); //Imprime el menu para decidir si jugar con la AI o con otro jugador
void Gotoxy(short x, short y); //Funcion para mover el cursor
void AsignarCoordenadas(int digito); //Funcion para asignar un simbolo a un posicion del arreglo jugadas
void ImprimirTablero(); //imprime el banner del tablero
void ValoresIniciales(); //resetea los valores iniciales del juego
void ImprimirResultadoJuego(); //Imprime el resultado del juego, si hubo un ganador o un empate
void ImprimirJuego(); //Imprime las posiciones del arreglo jugadas
string ImprimirNombreJugador(int numero); //Retorna el nombre del jugador en funcion de su turno

//Funciones de validacion de entrada
string CapturarEntrada(string mensaje, char tipo); //tipo especifica la validacion a realizar, n es numerico y a es alfabetico
bool ValidarEntrada(string entrada, char tipo);

//Funciones de validacion del juego
bool ValidarTableroLleno(); //Valida si ya todas las piezas del tablero fueron colocadas
bool ValidarPosicionVacia(int fila, int columna); //Valida si una posicion determinada esta ocupada
bool ValidarPosicionOcupada(); //Valida que la posicion en la que se quiere jugar no este ocupada


//funcion principal

int main(){
	do{
		Menu(); //Despliega el menu
		ComenzarJugada(); //Comienza la partida en funcion de la opcion escogida en el menu
		cout<<"\nSi desea jugar otra partida presione enter. De lo contrario, presione cualquier otra letra";
		char c = _getch(); //captura el caracter
		if(c == 10 || c == 13){//si es enter
			system("cls");
			ValoresIniciales(); //vuelve a los valores iniciales del juego
			continue; //da otra iteracion del bucle
		}
		else break;	
	}while(true);
	
	return 0;
}

// definiciones de funciones
void Menu(){
	bool continuar = false;
	do{
		string mensaje = "MENU\n1. Jugar con otro jugador\n2. Jugar con la AI\n3. Salir del Programa\nSeleccione la opcion deseada: ";
		int opcion = stoi(CapturarEntrada(mensaje, 'n'));
		switch(opcion){
			case 1:{
				AI = false; //se jugara contra otro jugador
				break;
			}
			case 2:{
				AI = true; //se jugara contra la AI
				break;
			}
			case 3:{
				cout<<"Programa finalizado";
				exit(0);
				break;
			}
			default:{
				cout<<"Opcion no valida";
				continuar = true;
				system("pause");
				break;
			}
		}	
	}while(continuar); //se continuara mientras sea true
}
void ValoresIniciales(){
	
	int contador = 1;
	for(int i = 0; i < 3; i++){ //limpiar arreglo jugada
		for(int j = 0; j < 3; j++){
			jugada[i][j] = contador + '0';
			contador++;
		}
	}
	 // arreglo que almacenara los diferentes valores del juego
	
	simbolo = 'X'; //Variable que almacenara el simbolo del jugador en cada turno
	empate = false; //bandera para saber si la jugada fue un empate
	AI = false;
	turnoJugador = 0; //Variable que indica a cual jugador le toca
	juego.fila = 0;
	juego.columna = 0;
	nombreJugador1 = "";
	nombreJugador2 = "";
	contadorJugadas = 0;
	
}
void ComenzarJugada(){
	nombreJugador1 = CapturarEntrada("Introduzca el nombre del primer jugador: ", 'a');

    if(AI == false) nombreJugador2 = CapturarEntrada("Introduzca el nombre del segundo jugador: ", 'a'); //si no se juega contra la AI pide el nombre del otro jugador
    else nombreJugador2 = "Inteligencia Artificial";
    
	srand((unsigned) time(NULL)); //Seed para comenzar a generar n�meros aleatorios

	int moneda = 1 + rand() % 2; //Simula el lanzamiento de una moneda. Genera 1 --> Cara, 2 --> Cruz
	
	if(moneda == 1){
		turnoJugador = moneda;
		cout << "El jugador 1, "<< nombreJugador1 << ", comenzara a jugar con el simbolo X" << endl;
		cout << "El jugador 2, "<< nombreJugador2 << ", le seguira con el simbolo O" << endl;
		if(AI == true){ //si se juega con la inteligencia artifical se especifican esos valores para MiniMax
			oponente = 'X';
			maquina = 'O';	
		}
	}
	else{
		turnoJugador = moneda;
		cout << "El jugador 2, "<< nombreJugador2 << ", comenzara a jugar con el simbolo X" << endl;
		cout << "El jugador 1, "<< nombreJugador1 << ", le seguira con el simbolo O" << endl;
		if(AI == true){ //si se juega con la inteligencia artifical se especifican esos valores para MiniMax
			oponente = 'O';
			maquina = 'X';
		}
	}
	system("pause");
    int fin; //variable para almacenar el puntaje de una partida
    while(true){ // Se repetira hasta que haya un empate o un ganador
        ImprimirTablero();
        SeleccionarPosicion();
		fin = ExaminarJugada(); //verifica si el juego finalizo
		if(fin == 0 && empate == false){ //mientras no se haya determinado un ganador o un empate
			CambiarTurno();	//se cambia el turno
		}
		else{
			break; //para finalizar la partida
		}    
    }
    system("cls"); //borra la pantalla
    ImprimirTablero(); //imprime el tablero con la posicion final
	ImprimirResultadoJuego(); //imprime el resultado de la partida
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
			Gotoxy(3 + j*7,3 + i*2);
			if(jugada[i][j] == 'O') SetConsoleTextAttribute(h, 2); //Verde
			else if(jugada[i][j] == 'X') SetConsoleTextAttribute(h, 4); //Rojo
			else SetConsoleTextAttribute(h, 7); //Blanco
			cout << jugada[i][j];
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
	int digito;
	
	if (AI == true && turnoJugador == 2) { //si es el turno de la Inteligencia Artificial
		digito = MejorJugada(); //se retorna la mejor posicion
		string mensaje = ImprimirNombreJugador(turnoJugador) + ", jugara en la posicion: " + char(digito + '0') + '\n';
		cout << mensaje;
		system("pause");
		AsignarCoordenadas(digito); //se asignan calcula posicion del arreglo en funcion del digito
	}
	else{ //si no es el turno de la AI
		do{
			string mensaje = ImprimirNombreJugador(turnoJugador) + ", indique la posicion en donde desea jugar: ";
			digito = stoi(CapturarEntrada(mensaje, 'n')); //captura la posicion numerica	
			
			AsignarCoordenadas(digito); //se asignan calcula posicion del arreglo en funcion del digito
			
		}while(ValidarPosicionOcupada()); //se repite mientras la posicion escogida no este ocupada
	}
	
	jugada[juego.fila - 1][juego.columna - 1] = simbolo; //se coloca el simbolo en la posicion escogida por el jugador
	contadorJugadas++;
}

bool ValidarPosicionOcupada(){
	if(isalpha(jugada[juego.fila-1][juego.columna-1])){ //si la posicion posee un caracter alfabetico X o O, significa que esta ocupada
		if(AI == false)	cout<<"La posicion esta ocupada, intente otra." << endl;
		return true;
	}
	else{
		return false;
	}
}

bool ValidarPosicionVacia(int fila, int columna){ //se utiliza para MinMax
	if(isdigit(jugada[fila][columna])){ //si la posicion posee un numerico, significa que esta vacia
		return true;
	}
	else{
		return false;
	}
}

void AsignarCoordenadas(int digito){
	if(digito > 6){
		juego.fila = 3;
		juego.columna = digito - 6;	
	}
	else if(digito > 3){
		juego.fila = 2;
		juego.columna = digito - 3;
	}
	else{
		juego.fila = 1;
		juego.columna = digito;
	}
}

bool ValidarTableroLleno(){
	for(int i = 0; i < 3; i++){ //recorre todo el arreglo en busca de una posicion vacia
		for(int j = 0; j < 3; j++){
			if(ValidarPosicionVacia(i,j)){
				return false; //si hay una posicion vacia, retorna que no esta lleno
			}
		}
	}
	return true; //si llega a este punto significa que esta lleno
}
int MiniMax(int nivel, bool isMaximizing){
	
	int puntaje = ExaminarJugada(); //Se retorna un puntaje para esa jugada
	
	if(puntaje == 10) return puntaje; //Si gana la maquina
	
	if(puntaje == -10) return puntaje; //Si gana el oponente
	
	if(ValidarTableroLleno()) return 0; //si es un empate
	
	if(isMaximizing){ //si se esta maximizando, significa que esta jugando la maquina
		int mejorScore = -1000; //sera -1000 porque es un valor menor que los posibles del juego
		for(int i = 0; i < 3; i++){ //recorre el arreglo jugada
			for(int j = 0; j < 3; j++){
				if(ValidarPosicionVacia(i,j)){ //si la posicion esta vacia
					char digito = jugada[i][j]; //guarda el numero de esta posicion
					jugada[i][j] = maquina; //asigna el simbolo de la maquina a esa posicion
					
					mejorScore = max(mejorScore, MiniMax(nivel + 1, !isMaximizing)); //Calcula el mejorScore y llamando a la funcion MiniMax
								//Se niega isMaximizing para cambiar de turno en el algoritmo
								//Se aumenta un nivel en profundidad
					
					jugada[i][j] = digito; //se deshace la jugada
					
				}
			}
		}
		return mejorScore; //se retorna el mejorScore
	}
	else{
		int mejorScore = 1000; //sera -1000 porque es un valor menor que los posibles del juego
		for(int i = 0; i < 3; i++){ //recorre el arreglo
			for(int j = 0; j < 3; j++){
				if(ValidarPosicionVacia(i,j)){ //Valida que la posicion este vacia
					char digito = jugada[i][j]; //almacena el digito de la posicion
					jugada[i][j] = oponente; //asigna a la posicion el simbolo del oponente
					
					mejorScore = min(mejorScore, MiniMax(nivel + 1, !isMaximizing)); //Se elige el minimo en funcion del mejorScore y la funci�n MiniMax
						//Se niega isMaximizing para cambiar de turno en el algoritmo
						//Se aumenta un nivel en profundidad
					jugada[i][j] = digito; //se deshace la jugada

				}
			}
		}
		return mejorScore;  //se retorna el mejorScore
	}
}

int MejorJugada(){
	int mejorScore = -1000; //como se busca elegir una posicion de la maquina, se quiere maximizar
	int mejorPosicion = -1; //digito de la mejor posicion
	for(int i = 0; i < 3; i++){ //se recorre el arreglo
		for(int j = 0; j < 3; j++){
			if(ValidarPosicionVacia(i,j)){ //si la posicion no esta vacia
				
				char digito = jugada[i][j]; //se guarda el digito de la posicion
				
				jugada[i][j] = maquina; //se asigna el simbolo de la maquina a esa posicion

				int scorePosicion = MiniMax(0, false); //se retorna el score de esta posicion con la funcion MiniMax
				
				jugada[i][j] = digito; //Se deshace la jugada
				
				if(scorePosicion > mejorScore){ //si el score de la posicion es mayor que el mejor score actual
					mejorScore = scorePosicion; //se asigna ese nuevo score como el mejor
					mejorPosicion = (char)(digito - '0'); //se guarda el digito de esa posicion como la mejor posicion
				}
			}
		}
	}
	return mejorPosicion; //se retorna la posicion
}
void CambiarTurno(){
    if(simbolo == 'X'){ // si el jugador actual es la X
        simbolo = 'O'; // el simbolo O cambia para poder usarlo con el siguiente jugador
        if(turnoJugador == 1) turnoJugador = 2; //se especifica el cambio de turno
        else turnoJugador = 1;
    }
    else{
    	simbolo = 'X';
    	if(turnoJugador == 1) turnoJugador = 2; //se especifica el cambio de turno
        else turnoJugador = 1;
	}
}

int ExaminarJugada(){
	for(int i = 0; i < 3; i++){
        if(jugada[i][0] == jugada[i][1] && jugada[i][0] == jugada[i][2]){ //verifica si hay combinaciones en vertical
            if(AI == true){ //si juga la AI, es importante saber el puntaje del ganador
            	if(oponente == jugada[i][0]) return -10; //si gano el oponente
            	else if(maquina == jugada[i][0]) return 10; //si gano la maquina
			}
			else return 1; //retorna que hubo un ganador, no es importante conocer un puntaje para el ganador
        }
        
		if(jugada[0][i] == jugada[1][i] && jugada[1][i] == jugada[2][i]){ //verifica si hay combinaciones en horizontal
            if(AI == true){ //si juga la AI, es importante saber el puntaje del ganador
				if(oponente == jugada[0][i]) return -10; // si gano el oponente
	            else if(maquina == jugada[0][i]) return 10;  //si gano la maquina          	
			}
			else return 1; //retorna que hubo un ganador, no es importante conocer un puntaje para el ganador
        }
    }
    
	if(jugada[0][0] == jugada[1][1] && jugada[1][1] == jugada[2][2]){
        // Para verificar de forma diagonal si se ha logrado alguna combinacion
    	if(AI == true){ //si juga la AI, es importante saber el puntaje del ganador
    		if(oponente == jugada[0][0]) return -10;
        	else if(maquina == jugada[0][0]) return 10;
		}
		else return 1; //retorna que hubo un ganador, no es importante conocer un puntaje para el ganador

	}
	
	if(jugada[0][2] == jugada[1][1] && jugada[1][1] == jugada[2][0]){
        // Para verificar de forma diagonal si se ha logrado alguna combinacion
    	if(AI == true){ //si juga la AI, es importante saber el puntaje del ganador
	    	if(oponente == jugada[0][2]) return -10;
	        else if(maquina == jugada[0][2]) return 10;	
		}
		else return 1; //retorna que hubo un ganador, no es importante conocer un puntaje para el ganador
	}
    
	if(contadorJugadas == 9){ //si ya se ocuparon todas las casillas y no se ha retornado la funcion significa que es un empate
		empate = true;
	}
	
	return 0; //no se decidio un ganador o hubo un empate
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
		if(entrada.length() == 0) return false;
		for(int i = 0; i < entrada.length(); i++) //recorre todas las posiciones del string de entrada
		{
			if(isalpha(entrada[i]) == false){
				cout << "La entrada solo debe poseer caracteres alfabeticos y estar compuesta por una sola palabra" << endl;
				return false; //si no es un caracter alfabetico o un espacio return falso
			}
		}
		return true;
	}	
}
