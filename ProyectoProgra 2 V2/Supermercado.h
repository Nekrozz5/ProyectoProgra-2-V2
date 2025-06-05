#pragma once
#include "Cajero.h"
#include "Supervisor.h"
#include <thread>
using namespace std;

class Supermercado {
private:
    Cajero cajero;
    Supervisor supervisor;
    thread hiloCajero;
    thread hiloSupervisor;

public:
    Supermercado();
    ~Supermercado();
};
