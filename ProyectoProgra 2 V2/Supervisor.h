#pragma once
#include <iostream>
#include <string>

#include"SingletonStock.h"
using namespace std;
class Supervisor 
{
private:
	int ci;
	string nombre;
	int celular;
	string cargo;
public: 
	Supervisor();
	Supervisor(int ci,string nombre,int celular,string cargo);
	~Supervisor();
	void ejecutar() ;


};

