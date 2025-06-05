#pragma once
#include <iostream>
#include <string>
#include"SingletonStock.h"
using namespace std;
class Cajero 
{
private:
	int ci;
	string nombre;
	int celular;
	string cargo;
public:
	Cajero();
	Cajero(int ci, string nombre, int celular, string cargo);
	~Cajero();
	void ejecutar();

};

