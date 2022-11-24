/*

NumerosEnPalabras.cpp
Materia - Estructuras de Datos y Algoritmos II

Asunto: 

Realizar un programa C++ que lea un n�mero real (correspondiente a un monto) y convertir
este monto a palabra. El programa debe tener las siguientes restricciones:
- El # tiene mascara 999999999.99
- Si el grupo determina puede variar el alcance del algoritmo.
- Solo llevar a palabras la parte entera del n�mero.
- Utilizar el enfoque de divide y venceras.

Autor:  Pazzis Paulino 1103790
        Huan Hao Wu 1104326
        Johan Contreras 1106473
        Luis Adames 1106170
        Paola Saldana 1104081
        
Fecha: 17 - Octubre - 2022

*/

#include <iostream>

using namespace std;

//estructuras de datos

string unidades[10]  = {"cero", "uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve"}; //digitos del 0 al 9 escritos en letras

string decenas[10]  = {"diez", "viente", "treinta", "cuarenta", "cincuenta", "sesenta", "setenta", "ochenta", "noventa"}; //del 10 al 90 escritos en letras

//prototipo de metodos y funciones
string ConvertirPalabras(int numero, bool terminacion); //Convertir un grupo de 3 o menos digitos a palabras
int DescomponerNumero(int numero); //Obtiene los tres ultimos tres digitos del numero
bool ValidarEntrada(string entrada); //Valida que la entrada que cumpla con la mascara 999 999 999.99
void CapturarEntrada(string mensaje, string resultado [2]); //captura el numero a convertir y almacena la parte entera [0] y decimal [1] 
															//en un arreglo que se introduce por parametros
string SepararEntrada(string entrada, bool entero); //retorna la parte entera o decimal del numero
string EscribirNumero(int numero); //retorna el numero completo en palabras
string ObtenerTerminacion(int clave, bool plural); //devuelve la terminacion de mil (1) o millon (2) o millones si es plural
string ObtenerCasoEspacialDecena(int clave); //devuelve en palabras el caso espacial entre 11 y 15 
string ObtenerCasoEspacialCentena(int clave); //devuelve en palabras el caso espacial para el 500, 700 y 900

//funcion principal
int main(){
	string entrada[2]; //arreglo para almacenar la entrada
	string continuar = "";
	do{
		CapturarEntrada("Ingrese el numero a convertir: ", entrada); //captura el numero
	
		int numero = stoi(entrada[0]); //convierte la parte entera del numero a formato numerico
		
		string resultado = EscribirNumero(numero); //retorna el numero en letras
		
		if(entrada[1] != "") resultado += "con " + entrada[1]; // si se introdujo una parte decimal al numero al resultado, agregalo
		
		resultado[0] = toupper(resultado[0]); //Pone en mayusculas la primera palabra
		
		cout<< "El numero indicado transformado a palabras es: " << endl << resultado << endl;
		
		cout<<"Desea continuar? (S/N): ";
		cin>>continuar;
		cout<<endl<<endl<<endl;
		
	} while(continuar=="S" || continuar=="s");
	
	return 0;
}

//definicion de metodos y funciones

string EscribirNumero(int numero){ //retorna el numero completo en palabras
	int auxiliar = numero;
	int contador = 0;
	string resultado = "";
	string auxiliarPalabra = "";

	while(auxiliar > 0){ //mientras que todavia hayan grupos de digitos de 3 por nombrar
	
		int caso = DescomponerNumero(auxiliar); //obten los tres ultimos digitos del numero
		
		if(caso != 0){ //si el grupo de digitos obtenidos no equivalen a 0
			
			auxiliarPalabra = resultado;
			bool plural = false;
			
			if(contador == 2 && caso > 1){ //si el caso a tomar en cuenta es mayor que 1, significa que la terminacion de millones sera en plural
				plural = true;
			}
			
			resultado = ConvertirPalabras(caso, (bool)contador) + ObtenerTerminacion(contador, plural) + auxiliarPalabra;
			
			//si contador es mayor que 0, significa que se necesita una terminacion de mil o millon dependiendo del valor que posea
			//si el numero posee un residuo (auxiliar%100) luego de dividir, significa que en la terminacion de millon sera en plural 2%100 == 2 -> 2 millones
			//Convierte los 3 digitos a palabras, agregale la terminacion correspondiente y concatenale el auxiliar
		}
		auxiliar /= 1000; //se corre el punto 3 posiciones a la izquierda
		contador++; //se aumenta el contador de la cantidad de grupos de digitos nombrados
	}
	
	return resultado; //retorna el numero completamente nombrado
}

int DescomponerNumero(int numero){ //retorna los tres ultimos digitos del numero
	return numero % 1000;
}

string ConvertirPalabras(int numero, bool terminacion){ 
	int divisor = 100; //variable para almacenar la cantidad entre la cual se va a dividir el numero
	int clave = 0; //variable para almacenar el izquierda del numero
	int auxiliar = numero; //variable auxiliar para el bucle
	string resultado = ""; 
	
	while(divisor > 0 && auxiliar > 0){ //mientras que el divisor y el numero a nombrar sean mayor que 0
		clave = auxiliar / divisor; //digito de la izquierda del numero
		
		if(divisor == 100 && clave > 0){ //si el numero tiene 3 digitos y la centena es mayor que 0
			if(clave == 5 || clave == 7 || clave == 9){ //si es un caso especial de 3 digitos
				resultado += ObtenerCasoEspacialCentena(clave) + " ";
			}
			else if(clave == 1){ //si la centena es 1
				if(auxiliar % 100 == 0) resultado += "cien "; //si no posee mas digitos a la derecha
				else resultado += "ciento "; //si posee mas digitos a la derecha
			}
			else{
				resultado += unidades[clave] + "cientos "; //buscar los nombres de las unidades y concatenar la palabra cientos
			}			
		}
		if(divisor == 10 && clave > 0){ //el numero tiene 2 digitos y la decena es mayor que 0
			if(auxiliar % 10 == 0){ //si la unidad que acompa�a a la decena es 0
				resultado += decenas[clave - 1] + " "; //10 diez, 20 veinte, 30 treinta, ...
				break;	
			}
			else{
				if (clave == 1){ //si la decena es 1
					if(auxiliar % 10 > 5) resultado += "dieci"; //si la unidad que acompa�a a la decena es mayor que 5, es decir, 16, 17, 18, ...
					else { //de lo contrario escribe el caso espacial
						resultado += ObtenerCasoEspacialDecena(auxiliar % 10)  + " "; //11 once, 12 doce, 13 trece, ...
						break;
					}
				}
				
				if (clave == 2){ //si la decena es 2
					resultado += "veinti"; //seguira el patron veinti + unidad
				}
			
				if (clave > 2){ //si la decena es mayor que 2, se sigue un patron en la escritura
					resultado += decenas[clave - 1] + " y "; //treinta y unidad, cuarenta y unidad, ...
				}
			}
		}
		if(divisor == 1 && clave > 0){ //si tiene un solo digito y es diferente de 0
			if(clave == 1){ //si el digito es 1
				if(terminacion) //si le sigue una terminacion al 1
					if(resultado == "") return ""; //para retornar mil en la funcion ObtenerTerminacion
					else resultado +="un "; //si al bloque de numeros le sigue "millon"
				else resultado += unidades[auxiliar] + " ";	
			}
			else resultado += unidades[auxiliar] + " ";	
		}
		
		auxiliar %= divisor; //nos quedamos con los dos digitos de la derecha
		divisor /= 10; //dividimos el divisor entre 10 para reducir el divisor
	}
	return resultado;
}

string ObtenerTerminacion(int clave, bool plural){ //Obtiene la terminacion de mil (1) o millon (2)
	switch(clave){
		case 0:{
			return "";
			break;
		}
		case 1:{
			return "mil ";
			break;
		}
		case 2:{
			if(plural) return "millones ";
			else return "un millon ";
			break;
		}
	}
}

string ObtenerCasoEspacialDecena(int clave){ //Obtiene los numeros del 11 al 15 en palabras
	switch(clave){
		case 1:{//11
			return "once";
			break;
		}
		case 2:{//12
			return "doce";
			break;
		}
		case 3:{//13
			return "trece";
			break;
		}
		case 4:{//14
			return "catorce";
			break;
		}
		case 5:{//15
			return "quince";
			break;
		}
	}
}
string ObtenerCasoEspacialCentena(int clave){ //Obtiene los numeros de 500, 700, 900 en palabras
	switch(clave){
		case 5:{ //500
			return "quinientos";
			break;
		}
		case 7:{ //700
			return "setecientos";
			break;
		}
		case 9:{ //900
			return "novecientos";
			break;
		}
	}
}
bool ValidarEntrada(string entrada){ //true - es valida       false - no es valida 
	int contadorPunto = 0; //variable para determinar cuantos '.' hay en la entrada
	for(int i = 0; i < entrada.length(); i++) //recorre todas las posiciones del string de entrada
	{
		if(entrada[i] == '.') //si el caracter de la posicion es '.'
		{
			if(entrada.length() > 1) //si la entrada tiene mas de un caracter
			{
				contadorPunto++; //agrega al contador
				if(contadorPunto > 1) return false; //si la entrada tiene mas de un signo '.'
				
				if(i == 0 || i == entrada.length() - 1) return false; //si el signo '.' esta en la primera o ultima posicion
			}
			else //si tiene un caracter o menos de un caracter
			{
				return false;
			}
		}
		if(isdigit(entrada[i])==false && entrada[i] != '.') return false; //si no es un digito ni es el signo de '.'
	}
	if(SepararEntrada(entrada, true).length() > 9) return false; //si la parte entera del numero tiene mas de 9 digitos
	return true;	
}

void CapturarEntrada(string mensaje, string resultado[2])			  
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
			cout << "Entrada no valida. Solo se permite un numero decimal positivo escrito correctamente cuya parte entera no debe sobrepasar los 9 digitos"<<endl;
			system("pause");
		}
		cout << endl;
	} while (correcta == false); //repetir mientras que la entrada no sea valida
	resultado[0] = SepararEntrada(entrada, true); //almacena la parte entera en la posicion 0
	resultado[1] = SepararEntrada(entrada, false); //almacena la parte decimal en la posicion 1
	
}

string SepararEntrada(string entrada, bool entero){ //retorna la parte decimal o entera del numero introducido
	string resultado = "";
	if(entero){ //si se necesita la parte entera
		for(int i = 0; entrada[i] != '\0'; i++){
			if(entrada[i] == '.') break; //cuanto encuentre un punto, sal del bucle
			else{
				resultado += entrada[i]; //si no encuentra agrega ese caracter a la cadena de resultado
			}
		}
	}
	else{
		bool punto = false; //valida si ya paso por un punto
		for(int i = 0; entrada[i] != '\0'; i++){
			if(punto) resultado += entrada[i]; //si la paso por un punto, agrega los caracteres a la cadena resultado

			if(entrada[i] == '.') punto = true; //si es un punto, marca la bandera
			
		}
	}
	return resultado; //retorna el resultado
}
