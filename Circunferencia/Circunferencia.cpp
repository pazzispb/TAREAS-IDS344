/*
Circunferencia.cpp
Materia - Estructuras de Datos y Algoritmos II
Asunto: 
Realizar un programa que trace la forma de un circulo al ingresar el radio del mismo
Autor:  Pazzis Paulino 1103790
        Huan Hao Wu 1104326
        Johan Contreras 1106473
        Luis Adames 1106170
        Paola Saldana 1104081
        
Fecha: 15 - Diciembre - 2022
*/
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>

using namespace std;

string CapturarEntrada(string mensaje);
bool ValidarEntrada(string entrada);
int CalcularX(int r, int ang);
int CalcularY(int r, int ang);
void Gotoxy(int x, int y);

// Maximo radio del circulo
const int radio_maximo = 20;

int main() {
    // input del radio
    int radio;
    radio = stoi(CapturarEntrada("Entra el radio del circulo: "));
	system("cls");
    // Comprobar sea positivo y menor al maximo
    if (radio <= 0 || radio > radio_maximo) {
        cout << "Error, el numero no se encuentra en el rango recomendado para dibujar un circulo en consola" << endl;
        return 1;
    }

    for (int i = 1; i <= 360; i++) {//recorremos los angulos de la circunferencia
        Gotoxy(CalcularX(radio, i), CalcularY(radio, i));
        cout<<"*";
    }
    Gotoxy(0,2*radio + 1);   
    return 0;
}

string CapturarEntrada(string mensaje)  
{
	string entrada; //variable para almacenar la entrada
	bool correcta; //variable para verificar si la entrada es valida
	do{
	//se repetira hasta que el usuario ingrese una entrada valida 
		cout << mensaje;
		cin >> entrada; //Tome la entrada por pantalla
		correcta = ValidarEntrada(entrada); //Llama a la funcion para validar la entrada
		if(correcta == false) //si no es valida
		{
			cout << "Entrada no valida." << endl;
			system("pause");
		}
		cout << endl;
	} while (correcta == false); //repetir mientras que la entrada no sea valida
	return entrada; //retorna la entrada
}

bool ValidarEntrada(string entrada){ //true - es valida       false - no es valida 

	for(int i = 0; i < entrada.length(); i++) //recorre todas las posiciones del string de entrada
	{
		if(isdigit(entrada[i]) == false){
				cout << "La entrada debe ser numerica" << endl;
				return false; //si no es una entrada numeerica return falso
		}
	}
	return true;
}

int CalcularX(int r, int ang){
	return round(r * cos(ang*(M_PI)/180.0)) + r; //se le suma el radio para que no de negativo
}
int CalcularY(int r, int ang){
	return round(r * sin(ang*(M_PI)/180.0)) + r; //se le suma el radio para que no de negativo
}

void Gotoxy(int x, int y) // se invoca la funcion GoToXY la cual admite dos valores enteros uno para X y otro para Y
{
	HANDLE hcon;  
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD dwPos;  
    dwPos.X = x;  
    dwPos.Y= y;  
    SetConsoleCursorPosition(hcon,dwPos);  
}
