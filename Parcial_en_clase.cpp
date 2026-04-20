#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

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

    // 1. Validaciones iniciales
    if (tipoCliente < 1 || tipoCliente > 4 || monto <= 0 || plazo <= 0) {
        cout << "\nRESULTADO: Datos de entrada invalidos." << endl;
        return 0;
    }

    // 2. Definir límites y plazos (Ajustados para permitir las nuevas reglas)
    if (tipoCliente == 1) { // Estudiante
        limiteMonto = (tieneCodeudor == 1) ? 5000000 : 2000000;
        tasaEntera = 6; 
        plazoMaximo = (monto <= 2000000) ? 12 : 24;
    } 
    else if (tipoCliente == 2) { // Empleado
        limiteMonto = (tieneCodeudor == 1) ? 10000000 : 5000000;
        tasaEntera = 7;
        plazoMaximo = 60; // Se aumenta para permitir plazos largos > 36
    } 
    else if (tipoCliente == 3) { // Pensionado
        limiteMonto = (tieneCodeudor == 1) ? 7000000 : 3000000;
        tasaEntera = 4;
        plazoMaximo = 60; // Se aumenta para permitir plazos largos > 36
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

    // 3. MEJORA 1: Incremento de tasa por plazo largo (> 36 meses)
    // El incremento del 1.5% se suma a la tasa entera (escala 10)
    if (plazo > 36) {
        tasaEntera += 15; 
    }

    // 4. Evaluar límites de crédito
    if (aprobado && monto > limiteMonto) {
        aprobado = false;
        motivoRechazo = (tieneCodeudor == 1) ? "RECHAZADO. El monto excede el limite con codeudor." 
                                             : "RECHAZADO. El monto excede el limite sin codeudor.";
    }

    // 5. Evaluar plazo permitido
    if (aprobado && plazo > plazoMaximo) {
        aprobado = false;
        motivoRechazo = "RECHAZADO. El plazo excede el maximo permitido para su perfil.";
    }

    // 6. Mostrar Resultados y aplicar MEJORA 2
    cout << fixed << setprecision(0); 
    if (aprobado) {
        // Cálculo del interés (dividido 1000 por la escala de tasaEntera)
        interesTotal = (monto * (tasaEntera / 1000.0) * plazo);

        // MEJORA 2: Descuento del 10% sobre el interés si es Empleado/Pensionado con codeudor
        if ((tipoCliente == 2 || tipoCliente == 3) && tieneCodeudor == 1) {
            interesTotal = interesTotal * 0.90;
        }

        totalPagar = monto + interesTotal;

        cout << "\n---------------------------------------------------" << endl;
        cout << "ESTADO: APROBADO" << endl;
        cout << "Cliente: " << nombreCliente(tipoCliente) << endl;
        cout << "Tasa aplicada: " << setprecision(1) << (tasaEntera / 10.0) << "%" << endl;
        cout << "Interes total: $" << setprecision(0) << interesTotal << endl;
        cout << "Total a pagar: $" << totalPagar << endl;
        cout << "---------------------------------------------------" << endl;
    } else {
        cout << "\n" << motivoRechazo << endl;
    }

    return 0;
}
