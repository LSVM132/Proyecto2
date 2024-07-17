#include <iostream>
#include<stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
#include<ctype.h>

using namespace std;

//atributo para color de letra
HANDLE hConsoleHandle = GetStdHandle (STD_OUTPUT_HANDLE);
// Variables Globales
int opcionMenu;
//Areglos
int cantidadEstudiantes[3] = {0,0,0};
float promedioEstudiantes[3] = {0,0,0}, promediosFinales[3] = {0,0,0}, calificaciones[4]{0,0,0,0},porcentajesGraficos[3] = {0,0,0};

// Funcion para las cordenadas en consola
void gotoxy(int x ,int y)
{
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

// Funcion para crear los graficos
  void hacerGraficos(int a,int y){
int i;int j=20;
for (i=1; i<=a; i++){
        gotoxy(j,y); printf("%c",178);
		j++;
	}
  }

  // Funcion para dibujar un cuadro en consola
void cuadro(int x1, int y1, int x2, int y2)
{
	int i;

	for (i=x1; i<=x2;i++)
	{
		gotoxy(i,y1); printf("%c",205);
		gotoxy(i,y2); printf("%c",205);
	}

	for (i=y1; i<=y2;i++)
	{
		gotoxy(x1,i); printf("%c",186);
		gotoxy(x2,i); printf("%c",186);
	}


	gotoxy(x1,y1); printf("%c",201);
	gotoxy(x1,y2); printf("%c",200);
	gotoxy(x2,y1); printf("%c",187);
	gotoxy(x2,y2); printf("%c",188);

}
// Funcion para implementar los graficos
void graficos(){
    system("cls");
    int totalEstudiantes=cantidadEstudiantes[0]+cantidadEstudiantes[1]+cantidadEstudiantes[2];
    // procedimiento para sacar los porcentajes
    porcentajesGraficos[0]=cantidadEstudiantes[0]*100/totalEstudiantes;
    porcentajesGraficos[1]=cantidadEstudiantes[1]*100/totalEstudiantes;
    porcentajesGraficos[2]=cantidadEstudiantes[2]*100/totalEstudiantes;
    SetConsoleTextAttribute (hConsoleHandle, 14);
   	gotoxy(10,1); cout << "::::::::::::::::::::::Graficos de Estudiantes::::::::::::::::::::::";
	gotoxy(2,4);	printf("Admitidos");
	SetConsoleTextAttribute (hConsoleHandle, 8);
	hacerGraficos(porcentajesGraficos[0],4);
	SetConsoleTextAttribute (hConsoleHandle, 14);cout << " " << porcentajesGraficos[0] << "%";
	gotoxy(2,6);	printf("En Espera");
	SetConsoleTextAttribute (hConsoleHandle, 8);
	hacerGraficos(porcentajesGraficos[1],6);
    SetConsoleTextAttribute (hConsoleHandle, 14);cout << " " << porcentajesGraficos[1] << "%";
	gotoxy(2,8);	printf("No Admitidos");
	SetConsoleTextAttribute (hConsoleHandle, 8);
	hacerGraficos(porcentajesGraficos[2],8);
    SetConsoleTextAttribute (hConsoleHandle, 14);cout << " " << porcentajesGraficos[2] << "%";
    SetConsoleTextAttribute (hConsoleHandle, 4);
    gotoxy(16,12); cout << "<Pulse cualquier tecla para salir>";
	getch();
}
// Funcion de Estadisticas
void estadisticas() {
    system("cls");
    // Los promedios los calculamos aqui para mantenerlos actualizados
    promediosFinales[0] = promedioEstudiantes[0]/cantidadEstudiantes[0];
    promediosFinales[1] = promedioEstudiantes[1]/cantidadEstudiantes[1];
    promediosFinales[2] = promedioEstudiantes[1]/cantidadEstudiantes[2];
    gotoxy(8,1); cout << "::::::::::::::::::::::Estadisticas::::::::::::::::::::::";
    gotoxy(4,3);cout << "Cantidad Estudiantes Admitidos: " << cantidadEstudiantes[0] << "\n";
    gotoxy(4,4);cout << "Promedio Estudiantes Admitidos: " << promediosFinales[0] << "\n";
    gotoxy(4,5);cout << "Cantidad Estudiantes En Espera: " << cantidadEstudiantes[1] << "\n";
    gotoxy(4,6);cout << "Promedio Estudiantes En Espera: " << promediosFinales[1] << "\n";
    gotoxy(4,7);cout << "Cantidad Estudiantes No Admitidos: " << cantidadEstudiantes[2] << "\n";
    gotoxy(4,8);cout << "Promedio de Estudiantes No Admitidos: " << promediosFinales[2] << "\n";
    SetConsoleTextAttribute (hConsoleHandle, 4);
    gotoxy(16,12); cout << "<Pulse cualquier tecla para salir>";
	getch();
}

// Funcion de Registro y evaluacion
void ingresarDatos() {
//Constantes
const int anioActual = 2024;
//variables
int numeroCedula,anioNacimiento,edad,totalEstudiantes;
char opcionDatos;
string nombreEstudiante,calificacion;
    do {
                 system("cls");
    SetConsoleTextAttribute (hConsoleHandle, 8);
    cuadro(20,2,44,6); //Cuadra Registro
    cuadro(2,8,72,18); //Cuadra Ingreseso datos
    SetConsoleTextAttribute (hConsoleHandle, 14);
    gotoxy(24,4);cout << "Registro de datos\n";
    float promedios=0,notaExamAdm=0,promedioFinal=0,porcentajeCriterio=0,porcentajeExamAdm=0,promedioAdmicion=0;
    gotoxy(3,9);cout << "Ingrese numero de cedula del estudiante: ";
    cin >> numeroCedula;
    gotoxy(3,10);cout << "Ingrese el nombre del estudiante: ";
    cin >> nombreEstudiante;
    gotoxy(3,11);cout << "Ingrese anio de Nacimiento del estudiante: ";
    cin >> anioNacimiento;
    gotoxy(3,12);cout << "Ingrese promedios finales del ultimo anio de Colegio de las materias:\n";
    gotoxy(3,13);cout << "Matematicas, Espanol, Ciencias y Estudios Sociales\n";
    SetConsoleTextAttribute (hConsoleHandle, 8);
     //Cuadros calificaciones
     cuadro(10,14,16,16);
     cuadro(20,14,26,16);
     cuadro(30,14,36,16);
     cuadro(40,14,46,16);
     SetConsoleTextAttribute (hConsoleHandle, 14);
     int x = 12;
    for (int c =0;c<=3;c++){
        gotoxy(x,15); cin >> calificaciones[c];
        promedios+= calificaciones[c];
        x+=10;
    }
    gotoxy(3,17); cout << "Ingrese la nota del examen de admision: ";
    cin >> notaExamAdm;

    edad = -anioNacimiento - -anioActual;
    promedioFinal = promedios / 4;
    porcentajeCriterio = promedioFinal * 40 / 100;
    porcentajeExamAdm = notaExamAdm * 60 / 100;
    promedioAdmicion = porcentajeCriterio + porcentajeExamAdm;

    if (promedioAdmicion >= 85) {
        calificacion = "Admitido";
        cantidadEstudiantes[0] += 1;
        promedioEstudiantes[0] += promedioAdmicion;
    } else if (promedioAdmicion >= 75 && promedioAdmicion < 85) {
        calificacion = "En Espera";
        cantidadEstudiantes[1] += 1;
        promedioEstudiantes[1] += promedioAdmicion;
    } else {
        calificacion = "No Admitido";
        cantidadEstudiantes[2] += 1;
        promedioEstudiantes[2] += promedioAdmicion;
    }
    SetConsoleTextAttribute (hConsoleHandle, 8);
    cuadro(74,8,118,23); //Cuadro Recopilacion
    SetConsoleTextAttribute (hConsoleHandle, 14);
    gotoxy(84,9);cout << "RECOPILANDO DATOS";
    gotoxy(75,10);cout << "Cedula: " << numeroCedula;
    gotoxy(75,11);cout << "Nombre: " << nombreEstudiante;
    gotoxy(75,12);cout << "Anio Nacimiento: " << anioNacimiento;
    gotoxy(75,13);cout << "Edad: " << edad;
    gotoxy(75,14);cout << "Calificacionesde Materias: ";
    for (int c=0; c <= 3; c++) {
     cout << calificaciones[c] << " ";
    }
    gotoxy(75,15);cout << "Promedio Colegio: " << promedioFinal;
    gotoxy(75,16);cout << "Porcentaje Criterio Colegio: " << porcentajeCriterio;
    gotoxy(75,17);cout << "Porcentaje Examen Admision: " << porcentajeExamAdm;
    gotoxy(75,18);cout << "promedio Admicion: " << promedioAdmicion;
    SetConsoleTextAttribute (hConsoleHandle, 4);
    cuadro(78,20,103,22); // cuadro calificacion
    gotoxy(79,21);cout << "Calificacion: " << calificacion;
    SetConsoleTextAttribute (hConsoleHandle, 8);
    cuadro(6,20,22,24);
    SetConsoleTextAttribute (hConsoleHandle, 14);
    gotoxy(7,21);cout << "S) Continuar";
    gotoxy(7,22);cout << "N) Salir\n";
    gotoxy(7,23);cout << "Su opcion: ";
    cin >> opcionDatos;
    } while (opcionDatos!= 'N' && opcionDatos!= 'n');
}
// Menu principal
void menuPrincipal() {
    do {
        system("cls");
    SetConsoleTextAttribute (hConsoleHandle, 8);
    cuadro(20,4,40,8); //Cuadra Menu
    cuadro(8,10,50,18);//Cuadro Grande
    cuadro(8,20,50,22);//Cuadro Opcion
    SetConsoleTextAttribute (hConsoleHandle, 4);
    cuadro(36,15,48,17);//Cuadro Salir
    SetConsoleTextAttribute (hConsoleHandle, 14);
    gotoxy(10,2); cout << "Preseleccionador de estudiantes primer ingreso para la Carrera de Ingenieria de Sistemas\n";
    gotoxy(24,6);cout << "MENU PRINCIPAL";
    gotoxy(12,12);cout << "1) Ingresar Datos\n";
    gotoxy(12,13);cout << "2) Estadisticas\n";
    gotoxy(12,14);cout << "3) Grafico\n";
    gotoxy(38,16);cout << "4) Salir\n";
    gotoxy(12,21);cout << "Su opcion es: ";
    cin >> opcionMenu;
    switch(opcionMenu) {
  case 1:
      ingresarDatos();
    break;
  case 2:
      estadisticas();
    break;
  case 3:
    graficos();
    break;
    }
    } while (opcionMenu != 4);
}
int main() {
   menuPrincipal();
  return 0;
}
