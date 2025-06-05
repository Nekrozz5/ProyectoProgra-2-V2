#pragma once
#include <iostream>
#include"VectorGenerico.h"
#include "Producto.h"

#include <fstream>
#include <sstream>
using namespace std;

class SingletonStock
{
private:
	VectorGenerico<Producto> productos;
private:
	SingletonStock();
public:
	
	SingletonStock(int cantidadMaxima);
	~SingletonStock();
	static SingletonStock& getInstance();
	void registrarProducto(Producto* producto);
	string toJson();
	Producto* buscarProductoPorNombre(string nombre);

	
};

