#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Función para obtener el nombre del tipo de cliente
string nombreCliente(int tipo) {
    switch (tipo) {
        case 1: return "Estudiante";
        case 2: return "Empleado";
        case 3: return "Pensionado";
        case 4: return "Desempleado";
        default: return "Desconocido";
    }
}

int main() {
    int tipoCliente, plazo, tieneCodeudor;
    float monto, tasaInteres, limiteMonto, interesTotal, totalPagar;
    int plazoMaximo;
    bool aprobado = true;
    string motivoRechazo = "";

    cout << "--- Sistema de Evaluacion de Prestamos Bancarios ---" << endl;
    cout << "1. Estudiante\n2. Empleado\n3. Pensionado\n4. Desempleado" << endl;
    cout << "Seleccione tipo de cliente: ";
    cin >> tipoCliente;

    cout << "Monto solicitado: ";
    cin >> monto;

    cout << "Plazo (meses): ";
    cin >> plazo;

    cout << "Tiene codeudor? (1 = Si, 0 = No): ";
    cin >> tieneCodeudor;

    // 1. Validar datos de entrada
    if (tipoCliente < 1 || tipoCliente > 4 || monto <= 0 || plazo <= 0) {
        cout << "\nRESULTADO: Datos de entrada invalidos." << endl;
        return 0;
    }

    // 2. Definir limites y tasas segun tipo de cliente
    if (tipoCliente == 1) { // Estudiante
        limiteMonto = (tieneCodeudor) ? 5000000 : 2000000;
        tasaInteres = 0.006; // 0.6%
        plazoMaximo = (monto <= 2000000) ? 12 : 24;
    } 
    else if (tipoCliente == 2) { // Empleado
        limiteMonto = (tieneCodeudor) ? 10000000 : 5000000;
        tasaInteres = 0.007; // 0.7%
        plazoMaximo = (monto <= 5000000) ? 24 : 48;
    } 
    else if (tipoCliente == 3) { // Pensionado
        limiteMonto = (tieneCodeudor) ? 7000000 : 3000000;
        tasaInteres = 0.004; // 0.4%
        plazoMaximo = (monto <= 3000000) ? 24 : 36;
    } 
    else { // Desempleado
        if (!tieneCodeudor) {
            aprobado = false;
            motivoRechazo = "Desempleados solo pueden aplicar si tienen codeudor.";
        }
        limiteMonto = 2000000;
        tasaInteres = 0.008; // 0.8%
        plazoMaximo = 12;
    }

    // 3. Evaluar limites de credito y plazo
    if (aprobado) {
        if (monto > limiteMonto) {
            aprobado = false;
            motivoRechazo = (tieneCodeudor) ? "El monto excede el limite con codeudor." : "El monto excede el limite sin codeudor.";
        } else if (plazo > plazoMaximo) {
            aprobado = false;
            motivoRechazo = "El plazo excede el maximo permitido para este monto.";
        }
    }

    // 4. Mostrar Resultados
    cout << fixed << setprecision(0); // Para mostrar montos sin decimales
    if (aprobado) {
        interesTotal = monto * tasaInteres * plazo;
        totalPagar = monto + interesTotal;

        cout << "\n--- PRESTAMO APROBADO ---" << endl;
        cout << "Cliente: " << nombreCliente(tipoCliente) << endl;
        cout << "Monto: $" << monto << endl;
        cout << "Plazo: " << plazo << " meses" << endl;
        cout << "Tasa mensual: " << (tasaInteres * 100) << "%" << endl;
        cout << "Total a pagar: $" << totalPagar << endl;
    } else {
        cout << "\n--- RECHAZADO ---" << endl;
        cout << "Motivo: " << motivoRechazo << endl;
    }

    return 0;
}
