/*

ProblemaNReinas.cpp
Materia - Estructuras de Datos y Algoritmos II

Asunto: Realizar un programa que resuelva el problema de las N-Reinas.

Autor:  Pazzis Paulino 1103790
        Huan Hao Wu 1104326
        Johan Contreras 1106473
        Luis Adames 1106170
        Paola Saldana 1104081
        
Fecha: 5 - enero - 2023

*/

#include <iostream>
#include <math.h>

using namespace std;

//prototipo de funciones
bool ComprobarPosicion(int reinas[], int cantidadReinas, int nivelArbol); //funcion para validar que las reinas no se ataquen
void Nreinas(int reinas[], int cantidadReinas, int nivelArbol); //Funcion recursiva para obtener las soluciones
bool ValidarEntrada(string entrada);
string CapturarEntrada(string mensaje);

int cantidadSoluciones = 0; //declaramos e inicializamos un contador para las soluciones del problema

//funcion principal
int main(){
	
	int nivelArbol = 0; // punto de partida, siendo el nivel 0 del arbol, es decir, la raiz
	int cantidadReinas; //Variable para la cantidad de reinas a colocar
	
	cantidadReinas = stoi(CapturarEntrada("Ingrese la cantidad de reinas: "));	
	
	int *reinas = new int[cantidadReinas]; // declaramos el arreglo para almacenar la posicion de las reinas
	
	for(int i = 0; i < cantidadReinas; i++){ // nos setea el arreglo en su forma incial
		reinas[i] = -1; // llenamos nuestro arreglo con -1 en todas las posiciones EJEMPLO: reinas[4] = {-1,-1,-1,-1} es decir no se han colocado reinas
	}
	
	Nreinas(reinas, cantidadReinas, nivelArbol); // nuestra funcion recursiva que calcula todas las soluciones posibles
	
	return 0;	
}

void Nreinas(int reinas[], int cantidadReinas, int nivelArbol){
	
	if(nivelArbol == cantidadReinas){ //encontraremos una solucion cuando hayamos llegado al ultimo nivel de nuestro arbol
		cantidadSoluciones++; //aumenta el contador de soluciones global
		cout<<"Solucion "<<cantidadSoluciones<< ": [ "; //imprime el numero de la solucion
		
		for(int i = 0; i<cantidadReinas; i++){  //recorre el arreglo
			cout << reinas[i]; //imprime la fila de la reina
			
			if( i+1 <cantidadReinas ) cout<<" , "; //si todavia no se llega a la ultima posicion, coloca la coma para separar
			else cout<<" ]";
		}	
		cout<<endl<<endl;	
	}
	//de lo contrario, si no se completa el caso base debe seguir buscando (moviendose de manera horizontal en el arbol de busqueda)
	//hasta que el nivel del arbol sea igual a cantidad de reinas-1 
	else{
		for(reinas[nivelArbol] = 0; reinas[nivelArbol]<cantidadReinas; reinas[nivelArbol]++){
			
			if(ComprobarPosicion(reinas, cantidadReinas, nivelArbol)){ //comprobamos que la posicion donde colocamos a la nueva reina es valida
				
				//cada vez que llamamos a la funcion recursiva es que aparecera un nuevo nodo en el arbol de busqueda
				Nreinas(reinas, cantidadReinas,nivelArbol+1); //llamamos a la funcion recursiva y aumentamos el nivel de profundidad del arbol
			}		
		}
	}	
}

//A continuacion comprobamos si la reina esta colocado en una posicion valida
//para que la posicion sea valida las reinas no deben en la misma columna
//y tampoco pueden estar en la misma fila, ni diagonal
bool ComprobarPosicion(int reinas[], int cantidadReinas, int nivelArbol){
	int i;
	for(i=0; i<nivelArbol; i++){
		
		if((reinas[i]==reinas[nivelArbol]) or (abs(nivelArbol-i)==abs(reinas[nivelArbol]-reinas[i])) ){ //primero comprobamos que no esten en una misma fila luego 
																										//si no se atacan en diagonal
			return false;
		}
	}
	return true;	
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
	if(stoi(entrada) < 4){ //El minimo de reinas debe ser 4 para que exista una solucion
		cout << "El minimo de reinas debe ser 4 para que exista una solucion" << endl;
		return false; //si no es una entrada numeerica return falso
	}
	
	return true;		
}

