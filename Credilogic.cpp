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
    float monto, tasaEntera, limiteMonto, interesTotal, totalPagar;
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

    // 1. Validar datos de entrada (Caso de prueba #5)
    if (tipoCliente < 1 || tipoCliente > 4 || monto <= 0 || plazo <= 0) {
        cout << "\nRESULTADO: Datos de entrada invalidos." << endl;
        return 0;
    }

    // 2. Definir limites y tasas (Usando la escala de la imagen: 0.6% -> 6)
    if (tipoCliente == 1) { // Estudiante
        limiteMonto = (tieneCodeudor == 1) ? 5000000 : 2000000;
        tasaEntera = 6; 
        plazoMaximo = (monto <= 2000000) ? 12 : 24;
    } 
    else if (tipoCliente == 2) { // Empleado
        limiteMonto = (tieneCodeudor == 1) ? 10000000 : 5000000;
        tasaEntera = 7;
        plazoMaximo = (monto <= 5000000) ? 24 : 48;
    } 
    else if (tipoCliente == 3) { // Pensionado
        limiteMonto = (tieneCodeudor == 1) ? 7000000 : 3000000;
        tasaEntera = 4;
        plazoMaximo = (monto <= 3000000) ? 24 : 36;
    } 
    else { // Desempleado
        limiteMonto = 2000000;
        tasaEntera = 8;
        plazoMaximo = 12;
        if (tieneCodeudor == 0) {
            aprobado = false;
            motivoRechazo = "RECHAZADO. Desempleados solo pueden aplicar si tienen codeudor.";
        }
    }

    // 3. Evaluar limites de credito (Caso de prueba #3)
    if (aprobado && monto > limiteMonto) {
        aprobado = false;
        motivoRechazo = (tieneCodeudor == 1) ? "RECHAZADO. El monto excede el limite con codeudor." 
                                             : "RECHAZADO. El monto excede el limite sin codeudor.";
    }

    // 4. Evaluar plazo permitido (Caso de prueba #4)
    if (aprobado && plazo > plazoMaximo) {
        aprobado = false;
        float umbralBajo = (tipoCliente == 1) ? 2000000 : (tipoCliente == 2) ? 5000000 : 3000000;
        if (monto <= umbralBajo)
            motivoRechazo = "RECHAZADO. El plazo excede el maximo permitido para montos bajos.";
        else
            motivoRechazo = "RECHAZADO. El plazo excede el maximo permitido para montos altos.";
    }

    // 5. Mostrar Resultados
    cout << fixed << setprecision(0); 
    if (aprobado) {
        // FORMULA FINAL: (Monto * TasaEntera * Plazo) / 100
        interesTotal = (monto * tasaEntera * plazo) / 100.0; 
        totalPagar = monto + interesTotal;

        cout << "\nEl prestamo solicitado por un monto de $" << monto 
             << " a un plazo de " << plazo << " meses es APROBADO con una Tasa del " 
             << setprecision(1) << (tasaEntera / 10.0) << "%." << endl;
        cout << "Total a pagar: $" << setprecision(0) << totalPagar << endl;
    } else {
        cout << "\n" << motivoRechazo << endl;
    }

    return 0;
}
