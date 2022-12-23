/*

Triangulo.cpp
Materia - Estructuras de Datos y Algoritmos II

Asunto: 

Realizar un programa que realice un triangulo de sierpinski utilizando aleatoriedad.

Autor:  Pazzis Paulino 1103790
        Huan Hao Wu 1104326
        Johan Contreras 1106473
        Luis Adames 1106170
        Paola Saldana 1104081
        
Fecha: 22 - Diciembre - 2022

*/


#include <graphics.h>
#include <iostream>
#include <cstdlib>

// dimenciones de la pantalla
const int ANCHO = 640;
const int LARGO = 480;

//Estructura para los puntos
struct Punto{
	int x, y;
};

void PuntoMedio(Punto*& p, int x, int y){ //Funcion que recibe por referencia el Punto 4 y cambia sus coordenadas con las del punto medio
	p -> x = (p -> x + x) / 2;
    p -> y = (p -> y + y) / 2;
}


//Funcion para generar numeros aleatorios del 1 al 3
int dado()
{
    return rand() % 3 + 1;
}

int main()
{
    //Inicializamos la pantalla con un ancho y un largo constante.
    initwindow(ANCHO, LARGO);

    //Instanciamos los puntos del triangulo
    Punto* p1 = new Punto();
    Punto* p2 = new Punto();
    Punto* p3 = new Punto();
    
    //Instanciamos el punto externo al triangulo
    Punto* p4 = new Punto();
    
    //Asigmanos las coordenadas del punto de cada vertice del triangulo
	p1 -> x = ANCHO / 2;
    p1 -> y = 0;
    p2 -> x = 0;
    p2 -> y = LARGO;
    p3 -> x = ANCHO;
    p3 -> y = LARGO;
    
    // se coloca el 4to punto fuera del triangulo
    p4 -> x = ANCHO / 2;
    p4 -> y = LARGO / 2;

    //Colocamos los puntos iniciales del problema
	putpixel(p1 -> x, p1 -> y, YELLOW);
    putpixel(p2 -> x, p2 -> y, YELLOW);
    putpixel(p3 -> x, p3 -> y, YELLOW);
    putpixel(p4 -> x, p4 -> y, YELLOW);
    
    
    // loop para lanzar 1000 veces el dado
    for (int i = 0; i < 100000; i++)
    {
        int lanzarDado = dado();

        // mover el 4to punto dependiendo de donde haya caido el dado
        if (lanzarDado == 1)
        {
        	PuntoMedio(p4, p1 -> x, p1 -> y);
        }
        else if (lanzarDado == 2)
        {
            PuntoMedio(p4, p2 -> x, p2 -> y);
        }
        else
        {
        	PuntoMedio(p4, p3 -> x, p3 -> y);
        }
        
		//Dibuja el punto 4 con sus nuevas coordenadas
		putpixel(p4 -> x, p4 -> y, YELLOW);
    }

    // pausar el programa hasta que el usuario cierre la pestana
    getch();
    closegraph();

    return 0;
}
