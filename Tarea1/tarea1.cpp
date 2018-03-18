/*
* 	Autor: Raul Perez
*	Fecha: 18/03/2018
*
*/
#include <graphics.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <windows.h>
#define MAXVIEW 700
#define CENTRO MAXVIEW/2
using namespace std;

int menu();
bool estaFuera(int, int);
void Linea(int, int, int, int);
void pintaPuntosCirculo(int, int, int);
void circuloPuntoMedio(int);
void circuloSegundoOrden(int);
void pintaPuntosElipse(int, int, int);
void elipse(int, int);
void pintaPuntosParabola(int, int, int);
void parabola(int);
void pintaPuntosHiperbola(int, int, int);
void hiperbola(int, int);

int main(int argc, char *argv[]){
	int opcion, radio;
	int x0, y0, xf, yf; 
	int a, b, abertura;
	opcion = menu();

	switch(opcion){
		case 1:
			cout << "X0: "; cin >> x0;
			cout << "Y0: "; cin >> y0;
			cout << "Xf: "; cin >> xf;
			cout << "Yf: "; cin >> yf;
			initwindow(MAXVIEW, MAXVIEW);
			Linea(x0, -y0, xf, -yf);
			break;
			
		case 2:
			do{
				cout << "Radio: "; cin >> radio;
			}while( radio < 1 );
			initwindow(MAXVIEW, MAXVIEW);
			circuloPuntoMedio(radio);
			break;
		
		case 3:
			do{
				cout << "Radio: "; cin >> radio;
			}while( radio < 1 );
			initwindow(MAXVIEW, MAXVIEW);
			circuloSegundoOrden(radio);
			break;
		
		case 4:
			do{
				cout << "a: "; cin >> a;
			}while( a < 1 );
			do{
				cout << "b: "; cin >> b;
			}while( b < 1 );
			initwindow(MAXVIEW, MAXVIEW);
			elipse(a, b);
			break;
		
		case 5:
			do{
				cout << "abertura: "; cin >> abertura;
			}while( abertura < 1 );
			initwindow(MAXVIEW, MAXVIEW);
			parabola(abertura);
			break;
		
		case 6:
			do{
				cout << "a: "; cin >> a;
			}while(a < 1);
			do{
				cout << "b: "; cin >> b;
			}while(b < 1);
			initwindow(MAXVIEW, MAXVIEW);
			hiperbola(a, b);
			break;	
	};
	outtextxy(10, MAXVIEW-30, "Raul Perez");
	while(!kbhit()) delay(1);
	closegraph();
	return 0;				
}

int menu(){
	int opcion;
	do{
		cout << ">> Graficas" << endl << endl;
		cout << "\t1) Linea (Punto medio)" << endl;
		cout << "\t2) Circulo (Punto medio)" << endl;
		cout << "\t3) Circulo (Diferencia de segundo orden)" << endl;
		cout << "\t4) Elipse" << endl;
		cout << "\t5) Parabola" << endl;
		cout << "\t6) Hiperbola" << endl;
		cout << "\t>> Opcion: "; cin >> opcion;
		system("cls");
	}while(opcion<1 || opcion>6);
		
	return opcion;
}

bool estaFuera(int x, int y){
	return ((CENTRO + x > MAXVIEW) || (CENTRO + x < 0) || 
		(CENTRO + y > MAXVIEW) || (CENTRO + y < 0));
}

void Linea(int x0, int y0, int xf, int yf){
  	int color = 10;
	int x, y, dx, dy, d, dE, dNE, incX, incY;
	bool fuera = false;

    dx = (xf - x0);
    dy = (yf - y0);

    if(dy < 0) { 
		dy = -dy; 
		incY = -1; 
    }else{
      	incY = 1;
    }

    if(dx < 0) {  
		dx = -dx;  
		incX = -1; 
    }else{
     	incX = 1;
    }

    x = x0;
    y = y0;
  
    putpixel( CENTRO + x, CENTRO + y,  color);

    if(dx > dy){
		d = 2*dy - dx;
		dE = 2*dy;
		dNE = 2*(dy-dx);
		while(x != xf && !fuera){
			x = x + incX;
			if(d < 0){
				d += dE;
			}
			else{
				y = y + incY;
				d += dNE;
			}
			fuera = estaFuera(x, y);
			Sleep(1);
			putpixel( CENTRO + x, CENTRO + y,  color);
		}
    }else{
		d = 2*dx - dy;
		dE = 2*dx;
		dNE = 2*(dx-dy);
		while (y != yf && !fuera ){
			y = y + incY;
			if (d < 0){
				d += dE;
			}else {
				x = x + incX;
				d += dNE;
			}
			fuera = estaFuera(x, y);
			Sleep(1);
			putpixel( CENTRO + x, CENTRO + y,  color);
		}
    }
}

void pintaPuntosCirculo(int x, int y, int color){
	Sleep(1);
	putpixel(CENTRO + x, CENTRO + y, color);
	putpixel(CENTRO - x, CENTRO - y, color);
	putpixel(CENTRO + x, CENTRO - y, color);
	putpixel(CENTRO - x, CENTRO + y, color);
	putpixel(CENTRO + y, CENTRO + x, color);
	putpixel(CENTRO - y, CENTRO - x, color);
	putpixel(CENTRO + y, CENTRO - x, color);
	putpixel(CENTRO +-y, CENTRO + x, color);
}

void circuloPuntoMedio(int radio){
	int color = 10;
	int x = 0;
	int y = radio;
	int d = 1 - radio;

	pintaPuntosCirculo(x, y, color);
	
	while (x < y){
	    x += 1;
	    if (d < 0){ 
			d += 2*x + 1;
		}else {
	      	y -=1;
	      	d += 2*(x - y) + 1;
	    }
	    pintaPuntosCirculo(x, y, color);
   }
}

void circuloSegundoOrden(int radio){
	int color = 10;
	int x = 0;
	int y = radio;
	int dE = 3;
	int dSE = -2 * radio + 5;  
	int d = 1 - radio;

	pintaPuntosCirculo(x, y, color);
	
	while (x < y){
	    x += 1;
	    if (d < 0){
	    	d += dE;
			dSE += 2;	
		}else {
			y -= 1;
			d += dSE;
			dSE += 4;
	    }
	    dE += 2;
	    pintaPuntosCirculo(x, y, color);
   }
}

void pintaPuntosElipse(int x, int y, int color){
	Sleep(1);
	putpixel(CENTRO + x, CENTRO + y, color);
  	putpixel(CENTRO - x, CENTRO + y, color);
	putpixel(CENTRO + x, CENTRO - y, color);
	putpixel(CENTRO - x, CENTRO - y, color);
}

void elipse(int a, int b){
	int color = 10;
	int x = 0;
	int y = b; 
	float a2 = a*a;
	float b2 = b*b; 
	float d1 = b2 - (a2 * b) + (0.25 * a2); 
	float d2 = b2 * ((x+0.5)*(x+0.5)) + a2 * ((y-1)*(y-1)) - (a2 * b2);
	
	pintaPuntosElipse(x, y, color);
	// Region 1
	while( (b2 * x) < (a2 * y) ) {
		x++;
		if(d1 < 0){ 
			d1 += (2 * b2 * x) + b2;
		}else{
			y--;
			d1 += (2 * b2 * x) - (2 * a2 * y) + b2;
		}
	  	pintaPuntosElipse(x, y, color);
	}
	// Region 2
	while(y > 0){
		y--;
		if(d2 > 0){ 
			d2 += - (2 * a2 * y) + a2;
		}else{
			x++; 
			d2 += (2 * b2 * x) - (2 * a2 * y) + a2;
		}
		pintaPuntosElipse(x, y, color);
	}
}

void pintaPuntosParabola(int x, int y, int color){
	Sleep(1);
	putpixel(CENTRO + x, CENTRO + y, color);
  	putpixel(CENTRO - x, CENTRO + y, color);
}

void parabola(int p){
	int color = 10;
	int x = 0;
	int y = 0;
	int d = 1 - p;
	int p4 = 4 * p;
	//region 1
	pintaPuntosParabola(x, -y, color);
	while(y < p && x <= CENTRO){
		if(d >= 0){
			y++;
			d -= p4;
		}
		x++;
		d += 2 * x + 3;
		pintaPuntosParabola(x, -y, color);
	}
	//region 2
	while( x <= CENTRO && y < CENTRO){
		if(d <= 0){
			x++;
			d += 2 * x + 2;
		}
		y++;
		d -= p4;
		pintaPuntosParabola(x, -y, color);
	}
}

void pintaPuntosHiperbola(int x, int y, int color){
	Sleep(1);
	putpixel(CENTRO + x, CENTRO + y, color);
  	putpixel(CENTRO - x, CENTRO + y, color);
	putpixel(CENTRO + x, CENTRO - y, color);
	putpixel(CENTRO - x, CENTRO - y, color);
}

void hiperbola(int a, int b){
	int color = 10;
	//valores iniciales
	int x  = a;
	int y = 0;
	int a2 = a * a;
	int b2 = b * b;
	int d = -5 * a2;
	//region 1
	while(2 * b2 * x > 2 * a2 * y && y < CENTRO){
		pintaPuntosHiperbola(x, y, color);
		if(d < 0){
		  x++;
		  d += 2 * b2 * ( x + 1);
		}
		y++;
		d -= a2 * (2 * y - 3);
	}
	//region 2
	while( y < CENTRO && x < CENTRO){
		pintaPuntosHiperbola(x, y, color);
		if(d > 0){
				d -= a2 * (3 * y + 2);
				y++;
		}
		x++;
		d += b2 * (2 * x + 3);
	}
}
