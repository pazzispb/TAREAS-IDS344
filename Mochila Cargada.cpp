/*

Mochila Cargada.cpp
Materia - Estructuras de Datos y Algoritmos II

Asunto: 

Realizar un programa que busque la forma mas optima de obtener beneficios de una mochila.

Autor:  Pazzis Paulino 1103790
        Huan Hao Wu 1104326
        Johan Contreras 1106473
        Luis Adames 1106170
        Paola Saldana 1104081
        
Fecha: 15 - Diciembre - 2022

*/

#include <iostream>

using namespace std;

// Estructura de la mochila
struct mochila{
    int peso;
    int beneficio;
      
};

//Variables globales
float capacidad; //capacidad maxima que soporta la mochila
int n; //cantidad de paquetes a acomodar en la mochila

//prototipo de metodos y funciones
int Particion(mochila arr[], int bajo, int alto);
void Quicksort(mochila arr[], int bajo, int alto);
void Greedy(int n, mochila elemento[]);
string CapturarEntrada(string mensaje);
bool ValidarEntrada(string entrada);
float CalcularGanancia(mochila x); // funcion para el calculo de la ganencia por kilogramo del paquete

int main(){
    
	capacidad = stoi(CapturarEntrada("\nIngrese la capacidad maxima de la mochila en kilogramos: "));
	
    n = stoi(CapturarEntrada("\nIngrese la cantidad de elementos a comprobar: ")); //paquetes que iran en la mochila

    mochila elemento[n]; //arreglo con los paquetes de la mochila
	
	cout<<"\n\n----------INTRODUZCA LOS DATOS DE LOS PAQUETES---------------"<<endl;
    for(int i = 0; i < n; i++){ //bucle para ingresar los pesos y beneficios de los paquetes a introducir en la mochila
        cout << "Paquete N. "<<i+1;
		elemento[i].peso = stoi(CapturarEntrada("\nIntroduzca el peso: "));
        
        elemento[i].beneficio = stoi(CapturarEntrada("Introduzca el beneficio: "));
    }
    
	Quicksort(elemento, 0, n - 1); //ordena el arreglo elementos, pasandole la posicion inicial y la final
	
    Greedy(n, elemento); //Funcion de factibilidad para obtener la solucion optima

    return 0;
}

int Particion(mochila arr[], int bajo, int alto){ 
    mochila pivote = arr[alto]; //elegimos el pivote como la utlima posicion del arreglo
    int i = (bajo - 1); //el elemento i sera el bajo -1

    for(int j = bajo; j < alto; j++){ //vamos a recorrer el arreglo desde la posicion mas baja hasta la mas alta
        
        if(CalcularGanancia(arr[j]) <= CalcularGanancia(pivote)){ //si el paquete de la posicion j tiene menor ganancia que el pivote
            i++;
            mochila temporal = arr[i]; //lo que tiene la posicion i se almacena en una posicion temporal
            arr[i] = arr[j]; //asigna lo que tiene la posicion j a la i
            arr[j] = temporal; //se coloca en la posicion j lo que tiene la posicion temporal
        }
    }
    mochila temporal = arr[i + 1]; //se coloca en una posicion temporal lo que que la posicion i+1
    arr[i + 1] = arr[alto]; //se coloca en la posicion i+1 la posicion del pivote
    arr[alto] = temporal; //en la posicion del pivote se coloca la temporal
    return (i + 1); //retorna la posicion i+1
}

void Quicksort(mochila arr[], int bajo, int alto){ // metodo para el ordenamiento de los paquetes en funcion de su ganancia
    if(bajo < alto){
        int p = Particion(arr, bajo, alto);

        Quicksort(arr, bajo, p - 1); //ordena el subarreglo izquierdo
        Quicksort(arr, p + 1, alto); //ordena el subarreglo izquierdo
    }
}

float CalcularGanancia(mochila x) //calcula la ganancia por kg del paquete
{ 
	return (float)x.beneficio / (float)x.peso;
} 

void Greedy(int n, mochila elemento[]){
    float maxGanancia = 0; //ganancia maxima
    int i = n; //cantidad de paquetes de la mochila
	cout << "-----------------RESULTADOS--------------------"<<endl;
    while(capacidad > 0 && --i >= 0){ //mientras que capacidad sea mayor que 0 y la cantidad de paquetes restantes se mayor o igual que 0
        if(capacidad >= elemento[i].peso){ // si la capacidad sigue siendo mayor al peso del elemento
            maxGanancia += elemento[i].beneficio; // se le suma a la ganancia maxima
            capacidad -= elemento[i].peso; // se va restando el espacio de la mochila
            cout << "\n Peso del paquete:" << elemento[i].peso << "\t Beneficio del paquete:" << elemento[i].beneficio; 
        }
        else{ //si el la capacidad de la mochila es menor que el peso del elemento
            maxGanancia += CalcularGanancia(elemento[i]) * capacidad; // En caso de que se tenga que fraccionar los item para mejor optimizacion
            cout << "\n Peso fraccionado del paquete de "<< elemento[i].peso <<" kg:" << capacidad << "\t Beneficio del paquete:" << CalcularGanancia(elemento[i]) * capacidad;
            capacidad = 0; //se fracciona el paquete en base a lo que queda de capacidad en la mochila
            break;
        }
    }
    cout << "\n\n El beneficio maximo para la mochila es: " << maxGanancia << endl;
    system("pause");
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
