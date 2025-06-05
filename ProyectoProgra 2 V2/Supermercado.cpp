#include "Supermercado.h"
#include <mutex>


mutex globalMutex;


Supermercado::Supermercado() {
    
    hiloCajero = thread(&Cajero::ejecutar, &cajero);
    hiloSupervisor = thread(&Supervisor::ejecutar, &supervisor);
}

Supermercado::~Supermercado() {
    
    hiloCajero.join();
    hiloSupervisor.join();

    
    cout << "Estado final del stock:\n";
    cout << SingletonStock::getInstance().toJson() << std::endl;
}
