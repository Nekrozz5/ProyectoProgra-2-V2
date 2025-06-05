#include "Supermercado.h"
#include <fstream>      // Necesario para operar con archivos
#include <sstream>      // Necesario para stringstream
#include <iostream>     // Necesario para cout, cerr
#include <string>       // Para usar string
#include <mutex>        // Para std::mutex

// Declara la mutex como 'extern' si está definida en otro archivo (ej. main.cpp)
// Si la defines aquí, quita 'extern' y asegúrate de que no haya otra definición global en otro lugar.
// Basado en tu main.cpp, parece que está declarada globalmente allí.
extern std::mutex globalMutex;


Supermercado::Supermercado() :
    cajero(), // Llama al constructor por defecto de Cajero
    supervisor() // Llama al constructor por defecto de Supervisor
{
    // Asegúrate de que las funciones ejecutar de Cajero y Supervisor sean correctas.
    // En tu código anterior, habías puesto &Cajero::ejecutar para el supervisor,
    // lo corregí a &Supervisor::ejecutar.
    hiloCajero = thread(&Cajero::ejecutar, &cajero);
    hiloSupervisor = thread(&Supervisor::ejecutar, &supervisor);
}

Supermercado::~Supermercado() {
    hiloCajero.join();
    hiloSupervisor.join();

    cout << "\n--- Estado final del stock ---\n";
    cout << SingletonStock::getInstance().toJson() << std::endl;

    int cereal_unidades_vendidas = 0;
    double cereal_monto_recaudado = 0.0;
    double cereal_ultimo_precio_adquisicion = 0.0; 
    double cereal_ganancia = 0.0;

    int leche_unidades_vendidas = 0;
    double leche_monto_recaudado = 0.0;
    double leche_ultimo_precio_adquisicion = 0.0; 
    double leche_ganancia = 0.0;

    int galleta_unidades_vendidas = 0;
    double galleta_monto_recaudado = 0.0;
    double galleta_ultimo_precio_adquisicion = 0.0; 
    double galleta_ganancia = 0.0;
    ifstream archivoVentas("ventas.txt");
    if (archivoVentas.is_open()) {
        string nombre_producto;
        int cantidad_transaccion;
        double precio_unitario;
        while (archivoVentas >> nombre_producto >> cantidad_transaccion >> precio_unitario) {
            if (nombre_producto == "Cereal") {
                cereal_unidades_vendidas += cantidad_transaccion;
                cereal_monto_recaudado += (cantidad_transaccion * precio_unitario);
            }
            else if (nombre_producto == "Leche") {
                leche_unidades_vendidas += cantidad_transaccion;
                leche_monto_recaudado += (cantidad_transaccion * precio_unitario);
            }
            else if (nombre_producto == "Galleta") {
                galleta_unidades_vendidas += cantidad_transaccion;
                galleta_monto_recaudado += (cantidad_transaccion * precio_unitario);
            }
        }
        archivoVentas.close();
    }
    else {
        cout << "Error";
    }

    ifstream archivoAdquisiciones("adquisiciones.txt");
    if (archivoAdquisiciones.is_open()) {
        string nombre_producto;
        int cantidad_transaccion; 
        double precio_unitario;
        while (archivoAdquisiciones >> nombre_producto >> cantidad_transaccion >> precio_unitario) {
            if (nombre_producto == "Cereal") {
                cereal_ultimo_precio_adquisicion = precio_unitario; 
            }
            else if (nombre_producto == "Leche") {
                leche_ultimo_precio_adquisicion = precio_unitario;
            }
            else if (nombre_producto == "Galleta") {
                galleta_ultimo_precio_adquisicion = precio_unitario;
            }
        }
        archivoAdquisiciones.close();
    }
    else {
        cout << "Error";
    }

  

    if (cereal_unidades_vendidas > 0) {
       
        cereal_ganancia = cereal_monto_recaudado - (cereal_unidades_vendidas * cereal_ultimo_precio_adquisicion);
    }
    else {
        cereal_ganancia = 0.0; 
    }

    if (leche_unidades_vendidas > 0) {
        leche_ganancia = leche_monto_recaudado - (leche_unidades_vendidas * leche_ultimo_precio_adquisicion);
    }
    else {
        leche_ganancia = 0.0;
    }

    if (galleta_unidades_vendidas > 0) {
        galleta_ganancia = galleta_monto_recaudado - (galleta_unidades_vendidas * galleta_ultimo_precio_adquisicion);
    }
    else {
        galleta_ganancia = 0.0;
    }

    cout << "\n--- Reporte de los 3 productos mas vendidos ---\n";
    string top1_ventas_nombre = ""; int top1_ventas_unidades = -1; double top1_ventas_ingresos = -1.0;
    string top2_ventas_nombre = ""; int top2_ventas_unidades = -1; double top2_ventas_ingresos = -1.0;
    string top3_ventas_nombre = ""; int top3_ventas_unidades = -1; double top3_ventas_ingresos = -1.0;

    if (cereal_unidades_vendidas > top1_ventas_unidades) {
        top3_ventas_nombre = top2_ventas_nombre; top3_ventas_unidades = top2_ventas_unidades; top3_ventas_ingresos = top2_ventas_ingresos;
        top2_ventas_nombre = top1_ventas_nombre; top2_ventas_unidades = top1_ventas_unidades; top2_ventas_ingresos = top1_ventas_ingresos;
        top1_ventas_nombre = "Cereal"; top1_ventas_unidades = cereal_unidades_vendidas; top1_ventas_ingresos = cereal_monto_recaudado;
    }
    else if (cereal_unidades_vendidas > top2_ventas_unidades) {
        top3_ventas_nombre = top2_ventas_nombre; top3_ventas_unidades = top2_ventas_unidades; top3_ventas_ingresos = top2_ventas_ingresos;
        top2_ventas_nombre = "Cereal"; top2_ventas_unidades = cereal_unidades_vendidas; top2_ventas_ingresos = cereal_monto_recaudado;
    }
    else if (cereal_unidades_vendidas > top3_ventas_unidades) {
        top3_ventas_nombre = "Cereal"; top3_ventas_unidades = cereal_unidades_vendidas; top3_ventas_ingresos = cereal_monto_recaudado;
    }

    if (leche_unidades_vendidas > top1_ventas_unidades) {
        top3_ventas_nombre = top2_ventas_nombre; top3_ventas_unidades = top2_ventas_unidades; top3_ventas_ingresos = top2_ventas_ingresos;
        top2_ventas_nombre = top1_ventas_nombre; top2_ventas_unidades = top1_ventas_unidades; top2_ventas_ingresos = top1_ventas_ingresos;
        top1_ventas_nombre = "Leche"; top1_ventas_unidades = leche_unidades_vendidas; top1_ventas_ingresos = leche_monto_recaudado;
    }
    else if (leche_unidades_vendidas > top2_ventas_unidades) {
        top3_ventas_nombre = top2_ventas_nombre; top3_ventas_unidades = top2_ventas_unidades; top3_ventas_ingresos = top2_ventas_ingresos;
        top2_ventas_nombre = "Leche"; top2_ventas_unidades = leche_unidades_vendidas; top2_ventas_ingresos = leche_monto_recaudado;
    }
    else if (leche_unidades_vendidas > top3_ventas_unidades) {
        top3_ventas_nombre = "Leche"; top3_ventas_unidades = leche_unidades_vendidas; top3_ventas_ingresos = leche_monto_recaudado;
    }

    if (galleta_unidades_vendidas > top1_ventas_unidades) {
        top3_ventas_nombre = top2_ventas_nombre; top3_ventas_unidades = top2_ventas_unidades; top3_ventas_ingresos = top2_ventas_ingresos;
        top2_ventas_nombre = top1_ventas_nombre; top2_ventas_unidades = top1_ventas_unidades; top2_ventas_ingresos = top1_ventas_ingresos;
        top1_ventas_nombre = "Galleta"; top1_ventas_unidades = galleta_unidades_vendidas; top1_ventas_ingresos = galleta_monto_recaudado;
    }
    else if (galleta_unidades_vendidas > top2_ventas_unidades) {
        top3_ventas_nombre = top2_ventas_nombre; top3_ventas_unidades = top2_ventas_unidades; top3_ventas_ingresos = top2_ventas_ingresos;
        top2_ventas_nombre = "Galleta"; top2_ventas_unidades = galleta_unidades_vendidas; top2_ventas_ingresos = galleta_monto_recaudado;
    }
    else if (galleta_unidades_vendidas > top3_ventas_unidades) {
        top3_ventas_nombre = "Galleta"; top3_ventas_unidades = galleta_unidades_vendidas; top3_ventas_ingresos = galleta_monto_recaudado;
    }

    if (top1_ventas_unidades != -1) {
        cout << "1. " << top1_ventas_nombre << ": " << top1_ventas_unidades << " unidades vendidas, Monto Recaudado: " << top1_ventas_ingresos << "\n";
    }
    if (top2_ventas_unidades != -1) {
        cout << "2. " << top2_ventas_nombre << ": " << top2_ventas_unidades << " unidades vendidas, Monto Recaudado: " << top2_ventas_ingresos << "\n";
    }
    if (top3_ventas_unidades != -1) {
        cout << "3. " << top3_ventas_nombre << ": " << top3_ventas_unidades << " unidades vendidas, Monto Recaudado: " << top3_ventas_ingresos << "\n";
    }
    cout << "\n--- Reporte de los 3 productos que representan una mayor ganancia ---\n";

    string top1_ganancia_nombre = ""; double top1_ganancia = -999999999.0; 
    string top2_ganancia_nombre = ""; double top2_ganancia = -999999999.0;
    string top3_ganancia_nombre = ""; double top3_ganancia = -999999999.0;

    if (cereal_ganancia > top1_ganancia) {
        top3_ganancia_nombre = top2_ganancia_nombre; top3_ganancia = top2_ganancia;
        top2_ganancia_nombre = top1_ganancia_nombre; top2_ganancia = top1_ganancia;
        top1_ganancia_nombre = "Cereal"; top1_ganancia = cereal_ganancia;
    }
    else if (cereal_ganancia > top2_ganancia) {
        top3_ganancia_nombre = top2_ganancia_nombre; top3_ganancia = top2_ganancia;
        top2_ganancia_nombre = "Cereal"; top2_ganancia = cereal_ganancia;
    }
    else if (cereal_ganancia > top3_ganancia) {
        top3_ganancia_nombre = "Cereal"; top3_ganancia = cereal_ganancia;
    }
    if (leche_ganancia > top1_ganancia) {
        top3_ganancia_nombre = top2_ganancia_nombre; top3_ganancia = top2_ganancia;
        top2_ganancia_nombre = top1_ganancia_nombre; top2_ganancia = top1_ganancia;
        top1_ganancia_nombre = "Leche"; top1_ganancia = leche_ganancia;
    }
    else if (leche_ganancia > top2_ganancia) {
        top3_ganancia_nombre = top2_ganancia_nombre; top3_ganancia = top2_ganancia;
        top2_ganancia_nombre = "Leche"; top2_ganancia = leche_ganancia;
    }
    else if (leche_ganancia > top3_ganancia) {
        top3_ganancia_nombre = "Leche"; top3_ganancia = leche_ganancia;
    }

    if (galleta_ganancia > top1_ganancia) {
        top3_ganancia_nombre = top2_ganancia_nombre; top3_ganancia = top2_ganancia;
        top2_ganancia_nombre = top1_ganancia_nombre; top2_ganancia = top1_ganancia;
        top1_ganancia_nombre = "Galleta"; top1_ganancia = galleta_ganancia;
    }
    else if (galleta_ganancia > top2_ganancia) {
        top3_ganancia_nombre = top2_ganancia_nombre; top3_ganancia = top2_ganancia;
        top2_ganancia_nombre = "Galleta"; top2_ganancia = galleta_ganancia;
    }
    else if (galleta_ganancia > top3_ganancia) {
        top3_ganancia_nombre = "Galleta"; top3_ganancia = galleta_ganancia;
    }

    if (top1_ganancia_nombre != "") { 
        cout << "1. " << top1_ganancia_nombre << ": Ganancia: " << top1_ganancia << "\n";
    }
    if (top2_ganancia_nombre != "") {
        cout << "2. " << top2_ganancia_nombre << ": Ganancia: " << top2_ganancia << "\n";
    }
    if (top3_ganancia_nombre != "") {
        cout << "3. " << top3_ganancia_nombre << ": Ganancia: " << top3_ganancia << "\n";
    }
}