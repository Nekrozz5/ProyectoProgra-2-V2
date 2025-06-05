#include "Cajero.h"
#include <fstream>
#include <mutex>


Cajero::Cajero()
{
    this->ci = 0;
    this->nombre = "Sin nombre";
    this->celular = 0;
	this->cargo = "cajero";
}

Cajero::Cajero(int ci, string nombre, int celular, string cargo) 
	
{
			this->ci = ci;
		this->nombre = nombre;
		this->celular = celular;
		this->cargo = "cajero";
}

Cajero::~Cajero()
{
}

void Cajero::ejecutar() {
   

    cout << "Cajero procesando ventas..." << endl;
    ifstream archivo("ventas.txt");

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
            p->disminuirCantidad(cantidad); 
        }
        else {
            cerr << "Producto no encontrado en stock: " << nombre << endl;
        }
    }

    archivo.close();
}
	
