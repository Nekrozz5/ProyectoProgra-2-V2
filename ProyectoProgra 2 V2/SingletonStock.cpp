#include "SingletonStock.h"
SingletonStock::SingletonStock() :SingletonStock(10)
{
    ifstream archivo("stock.txt"); 

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo stock.txt\n";
        return;
    }

    string nombre;
    int cantidad;

    while (archivo >> nombre >> cantidad) {
        Producto* nuevoProducto = new Producto(nombre, cantidad); 
        try {
            registrarProducto(nuevoProducto);
        }
        catch (const exception& e) {
            cerr << "Error al registrar el producto '" << nombre << "'." << endl;
            delete nuevoProducto;
        }
    }

    archivo.close();
}



SingletonStock::SingletonStock(int cantidadMaxima) :productos(cantidadMaxima)
{

}

SingletonStock::~SingletonStock()
{
	  
}

SingletonStock& SingletonStock::getInstance()
{
	static SingletonStock instancia;
	return instancia;
}

void SingletonStock::registrarProducto(Producto* producto)
{
	if (buscarProductoPorNombre(producto->getNombre()) != nullptr) {
		throw exception("Ya existe un usuario con el numero registrado");
	}
	productos.registrar(producto);
}
string SingletonStock::toJson() {
    stringstream json;
    json << "[";
    for (size_t i = 0; i <productos.getCantidadActual() ; ++i) {
        json << productos[i]->toJson(); if (i<productos.getCantidadActual()-1)
        {
			json << ",";
        }
    }
    json << "]";
    return json.str();
}
Producto* SingletonStock::buscarProductoPorNombre(string nombre)
{
	for (int i = 0; i < productos.getCantidadActual(); i++) {
		if (productos[i]->getNombre() == nombre) {
			return productos[i];
		}
	}
	return nullptr;
}
