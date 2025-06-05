#include "Supervisor.h"
#include <fstream>
#include <mutex>

Supervisor::Supervisor()
{
    this->ci = 0;
    this->nombre = "Sin nombre";
    this->celular = 0;
	this->cargo = "Supervisor";
}

Supervisor::Supervisor(int ci, string nombre, int celular, string cargo) 
{
	this->ci = ci;
	this->nombre = nombre;
	this->celular = celular;
	this->cargo = "Supervisor";
}

Supervisor::~Supervisor()
{
}

void Supervisor::ejecutar()
{
    

    cout << "Cajero procesando ventas..." << endl;
    ifstream archivo("adquisiciones.txt");

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo ventas.txt\n";
        return;
    }

    string nombre;
    int cantidad;
    float precio;

    while (archivo >> nombre >> cantidad >> precio) {
        

        Producto* p = SingletonStock::getInstance().buscarProductoPorNombre(nombre);
        if (p != nullptr) {
            p->incrementarCantidad(cantidad); 
        }
        else {
            cerr << "Producto no encontrado en stock: " << nombre << endl;
        }
    }

    archivo.close();
}





