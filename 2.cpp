#include <iostream>
#include <vector>
#include <conio.h>
#include <limits>
#include <windows.h> // Para manejar el mouse y gotoxy()

using namespace std;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct Vehiculo {
    int numeroPlaca;
    string marca;
    string modelo;
    int tipoVehiculo;
    int tipoLavado;
    int precio;
};

vector<Vehiculo> vehiculos;
int contadorFactura = 1;

void detectarClick(int &x, int &y) {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD events;
    INPUT_RECORD inputRecord;
    SetConsoleMode(hInput, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

    while (true) {
        ReadConsoleInput(hInput, &inputRecord, 1, &events);
        if (inputRecord.EventType == MOUSE_EVENT) {
            if (inputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                x = inputRecord.Event.MouseEvent.dwMousePosition.X;
                y = inputRecord.Event.MouseEvent.dwMousePosition.Y;
                break;
            }
        }
    }
}

void menu();
void ingresarDatosVehiculos();
void verEstadisticasVehiculosPorTipo();
void verEstadisticasVehiculosPorLavado();
void verGraficoVehiculosPorTipo();
void verGraficoVehiculosPorLavado();
int calcularPrecio(int tipoVehiculo, int tipoLavado);

void menu() {
    int opcion;
    int x, y;
    do {
        system("cls");
        gotoxy(10, 2);
        cout << "Menu Principal";
        gotoxy(10, 4);
        cout << "1- Ingresar Datos Vehiculos";
        gotoxy(10, 5);
        cout << "2- Ver Estadisticas Vehiculos Lavados segun tipo de Vehiculo";
        gotoxy(10, 6);
        cout << "3- Ver Estadisticas Vehiculos Lavados segun tipo de Lavado";
        gotoxy(10, 7);
        cout << "4- Ver Grafico Vehiculos Lavados por Tipo de Vehiculo";
        gotoxy(10, 8);
        cout << "5- Ver Grafico Vehiculos Lavados por Tipo de Lavado";
        gotoxy(10, 9);
        cout << "6- Salir";

        detectarClick(x, y);

        if (y == 4) opcion = 1;
        else if (y == 5) opcion = 2;
        else if (y == 6) opcion = 3;
        else if (y == 7) opcion = 4;
        else if (y == 8) opcion = 5;
        else if (y == 9) opcion = 6;
        else opcion = -1;

        switch (opcion) {
            case 1: ingresarDatosVehiculos(); break;
            case 2: verEstadisticasVehiculosPorTipo(); break;
            case 3: verEstadisticasVehiculosPorLavado(); break;
            case 4: verGraficoVehiculosPorTipo(); break;
            case 5: verGraficoVehiculosPorLavado(); break;
            case 6: exit(0);
            default: gotoxy(10, 13); cout << "Opcion invalida. Intente de nuevo."; _getch(); break;
        }
    } while (opcion != 6);
}

void ingresarDatosVehiculos() {
    char continuar = 'S'; // Inicializamos con 'S' para entrar al bucle la primera vez

    do {
        system("cls");
        Vehiculo vehiculo;
        gotoxy(10, 2);
        cout << "Ingresar Datos del Vehiculo";
        gotoxy(10, 4);
        cout << "Numero de Placa: ";
        cin >> vehiculo.numeroPlaca;
        gotoxy(10, 5);
        cout << "Marca: ";
        cin >> vehiculo.marca;
        gotoxy(10, 6);
        cout << "Modelo: ";
        cin >> vehiculo.modelo;
        gotoxy(10, 7);
        cout << "Tipo de Vehiculo (1=Sencillo, 2=4x4, 3=Microbus o Camion): ";
        cin >> vehiculo.tipoVehiculo;
        gotoxy(10, 8);
        cout << "Tipo de Lavado (1=Solo Lavado, 2=Lavado, Aspirado y Encerado): ";
        cin >> vehiculo.tipoLavado;
        vehiculo.precio = calcularPrecio(vehiculo.tipoVehiculo, vehiculo.tipoLavado);

        vehiculos.push_back(vehiculo);

        // Mostrar datos del vehiculo ingresado
        gotoxy(10, 10);
        cout << "Factura #" << contadorFactura++;
        gotoxy(10, 11);
        cout << "Numero de Placa: " << vehiculo.numeroPlaca;
        gotoxy(10, 12);
        cout << "Marca: " << vehiculo.marca;
        gotoxy(10, 13);
        cout << "Modelo: " << vehiculo.modelo;
        gotoxy(10, 14);
        cout << "Tipo de Vehiculo: " << vehiculo.tipoVehiculo;
        gotoxy(10, 15);
        cout << "Tipo de Lavado: " << vehiculo.tipoLavado;
        gotoxy(10, 16);
        cout << "Precio: " << vehiculo.precio << " colones";

        gotoxy(10, 18);
        cout << "Desea ingresar otro vehiculo? (S/N): ";
        cin >> continuar;

        // Limpiar el buffer de entrada para evitar problemas con _getch() posterior
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (continuar == 'S' || continuar == 's');
}

int calcularPrecio(int tipoVehiculo, int tipoLavado) {
    if (tipoVehiculo == 1) {
        if (tipoLavado == 1) return 3000;
        else return 5000;
    } else if (tipoVehiculo == 2) {
        if (tipoLavado == 1) return 5000;
        else return 7000;
    } else if (tipoVehiculo == 3) {
        if (tipoLavado == 1) return 7000;
        else return 12000;
    }
    return 0;
}

void verEstadisticasVehiculosPorTipo() {
    int sencillo = 0, tipo4x4 = 0, microbusCamion = 0;
    int dineroSencillo = 0, dinero4x4 = 0, dineroMicrobusCamion = 0;

    for (size_t i = 0; i < vehiculos.size(); i++) {
        if (vehiculos[i].tipoVehiculo == 1) {
            sencillo++;
            dineroSencillo += vehiculos[i].precio;
        } else if (vehiculos[i].tipoVehiculo == 2) {
            tipo4x4++;
            dinero4x4 += vehiculos[i].precio;
        } else if (vehiculos[i].tipoVehiculo == 3) {
            microbusCamion++;
            dineroMicrobusCamion += vehiculos[i].precio;
        }
    }

    system("cls");
    gotoxy(10, 2);
    cout << "Estadisticas Vehiculos Lavados segun tipo de Vehiculo";
    gotoxy(10, 4);
    cout << "Cantidad de Vehiculos Tipo Sencillos: " << sencillo;
    gotoxy(10, 5);
    cout << "Dinero Recaudado por Vehiculos Tipo Sencillos: " << dineroSencillo << " colones";
    gotoxy(10, 6);
    cout << "Cantidad de Vehiculos Tipo 4x4: " << tipo4x4;
    gotoxy(10, 7);
    cout << "Dinero Recaudado por Vehiculos Tipo 4x4: " << dinero4x4 << " colones";
    gotoxy(10, 8);
    cout << "Cantidad de Vehiculos Tipo Microbus o Camion: " << microbusCamion;
    gotoxy(10, 9);
    cout << "Dinero Recaudado por Vehiculos Tipo Microbus o Camion: " << dineroMicrobusCamion << " colones";

    gotoxy(10, 11);
    cout << "Presione cualquier tecla para regresar al menu.";
    _getch();
}

void verEstadisticasVehiculosPorLavado() {
    int soloLavado = 0, completo = 0;
    int dineroSoloLavado = 0, dineroCompleto = 0;

    for (size_t i = 0; i < vehiculos.size(); i++) {
        if (vehiculos[i].tipoLavado == 1) {
            soloLavado++;
            dineroSoloLavado += vehiculos[i].precio;
        } else if (vehiculos[i].tipoLavado == 2) {
            completo++;
            dineroCompleto += vehiculos[i].precio;
        }
    }

    system("cls");
    gotoxy(10, 2);
    cout << "Estadisticas Vehiculos Lavados segun tipo de Lavado";
    gotoxy(10, 4);
    cout << "Cantidad de Vehiculos con Solo Lavado: " << soloLavado;
    gotoxy(10, 5);
    cout << "Dinero Recaudado por Vehiculos con Solo Lavado: " << dineroSoloLavado << " colones";
    gotoxy(10, 6);
    cout << "Promedio Dinero Recaudado por Vehiculos con Solo Lavado: " << (soloLavado ? dineroSoloLavado / soloLavado : 0) << " colones";
    gotoxy(10, 7);
    cout << "Cantidad de Vehiculos con Lavado, Aspirado y Encerado: " << completo;
    gotoxy(10, 8);
    cout << "Dinero Recaudado por Vehiculos con Lavado, Aspirado y Encerado: " << dineroCompleto << " colones";
    gotoxy(10, 9);
    cout << "Promedio Dinero Recaudado por Vehiculos con Lavado, Aspirado y Encerado: " << (completo ? dineroCompleto / completo : 0) << " colones";

    gotoxy(10, 11);
    cout << "Presione cualquier tecla para regresar al menu.";
    _getch();
}

void verGraficoVehiculosPorTipo() {
    int sencillo = 0, tipo4x4 = 0, microbusCamion = 0;

    for (size_t i = 0; i < vehiculos.size(); i++) {
        if (vehiculos[i].tipoVehiculo == 1) sencillo++;
        else if (vehiculos[i].tipoVehiculo == 2) tipo4x4++;
        else if (vehiculos[i].tipoVehiculo == 3) microbusCamion++;
    }

    system("cls");
    gotoxy(10, 2);
    cout << "Grafico Vehiculos Lavados por Tipo de Vehiculo";
    gotoxy(10, 4);
    cout << "Veh. Sencillos   ";
    for (int i = 0; i < sencillo; i++) cout << (char)219;
    gotoxy(10, 5);
    cout << "Veh. 4x4         ";
    for (int i = 0; i < tipo4x4; i++) cout << (char)219;
    gotoxy(10, 6);
    cout << "Veh. Pesados     ";
    for (int i = 0; i < microbusCamion; i++) cout << (char)219;

    gotoxy(10, 8);
    cout << "Presione cualquier tecla para regresar al menu.";
    _getch();
}

void verGraficoVehiculosPorLavado() {
    int soloLavado = 0, completo = 0;

    for (size_t i = 0; i < vehiculos.size(); i++) {
        if (vehiculos[i].tipoLavado == 1) soloLavado++;
        else if (vehiculos[i].tipoLavado == 2) completo++;
    }

    system("cls");
    gotoxy(10, 2);
    cout << "Grafico Vehiculos Lavados por Tipo de Lavado";
    gotoxy(10, 4);
    cout << "Solo Lavado      ";
    for (int i = 0; i < soloLavado; i++) cout << (char)219;
    gotoxy(10, 5);
    cout << "Completo         ";
    for (int i = 0; i < completo; i++) cout << (char)219;

    gotoxy(10, 7);
    cout << "Presione cualquier tecla para regresar al menu.";
    _getch();
}

int main() {
    menu();
    return 0;
}

