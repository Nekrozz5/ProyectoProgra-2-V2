#pragma once
#include<iostream>
#include<string>
#include<exception>
using namespace std;
template <typename T>
class VectorGenerico
{

public:

	VectorGenerico(int cantidadMaxima);
	~VectorGenerico();
	void registrar(T* elemento);
	T* operator[](int posicion);
	int getCantidadActual();
	int getCantidadMaxima();

private:
	int cantidadMaxima;
	int cantidadActual;

	T** elementos;
};

template<typename T>
inline VectorGenerico<T>::VectorGenerico(int cantidadMaxima)
{
	this->cantidadActual = 0;
	this->cantidadMaxima = cantidadMaxima;
	elementos = new T * [cantidadMaxima];
}

template<typename T>
inline VectorGenerico<T>::~VectorGenerico()
{
	for (int i = 0; i < cantidadActual; i++)
	{
		delete elementos[i];
	}
	delete[] elementos;
}

template<typename T>
inline void VectorGenerico<T>::registrar(T* elemento)
{
	if (cantidadActual < cantidadMaxima)
	{
		elementos[cantidadActual] = elemento;
		cantidadActual++;
	}
	else
	{
		throw exception("se llego al limite de  elementos");
	}
}

template<typename T>
inline T* VectorGenerico<T>::operator[](int posicion)
{
	return elementos[posicion];
}

template<typename T>
inline int VectorGenerico<T>::getCantidadActual()
{
	return cantidadActual;
}

template<typename T>
inline int VectorGenerico<T>::getCantidadMaxima()
{
	return cantidadMaxima;
}


