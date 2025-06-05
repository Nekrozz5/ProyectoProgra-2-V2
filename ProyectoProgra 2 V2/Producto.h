#pragma once
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
class Producto
{
private:
	string nombre;
	int cantidad;
public:
	Producto();
	Producto(string nombre, int cantidad);
	~Producto();
	int getCantidad();
	string getNombre();
	string toJson();
	void incrementarCantidad(int cantidad);
	void disminuirCantidad(int cantidad);

};

