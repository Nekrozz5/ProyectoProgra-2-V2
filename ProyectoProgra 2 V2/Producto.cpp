#include "Producto.h"


Producto::Producto()
{
	nombre = "";
	cantidad = 0;
}

Producto::Producto(string nombre, int cantidad)
{
    this->nombre = nombre;
    this->cantidad = cantidad;
	
}

Producto::~Producto()
{
}

int Producto::getCantidad()
{
    return cantidad;
}



string Producto::getNombre()
{
	return nombre;
}

string Producto::toJson()
{
	stringstream json;
	json << "{";
	json << "\"nombre\":\"" << nombre <<"\",";
	json << "\"cantidad\":"<<cantidad;
	json << "}";
	return json.str();
}

void Producto::incrementarCantidad(int cantidad) {
	this->cantidad += cantidad;
}

void Producto::disminuirCantidad(int cantidad) {
	this->cantidad -= cantidad;
}



