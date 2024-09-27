//Nombre: Edwin Noe Argueta Flores
//Cuenta : 32111584

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <ostream>

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::copy;
using std::fixed;
using std::ios;
using std::left;
using std::right;
using std::showpoint;

using std::setw;
using std::setprecision;

using std::string;

using std::fstream;


void impresion(int  , string , double , int ); 

class DatosCliente {
    private:
        int numeroCuenta;
        char nombre[10];
        double saldo;
        int numCtaRelacionada;
    public:
        void setCuenta(int cuentaNueva) {
            numeroCuenta = cuentaNueva;
        };

        int getCuenta() {
            return numeroCuenta;
        };

        void setNombre(string nuevoNombre) {
            string valorNombre;
            int longitud = nuevoNombre.size();
            longitud = (longitud < 10 ? longitud : 9);
            nuevoNombre.copy(nombre, longitud);
            nombre[longitud] = '\0';
        };

        string getNombre() {
            return nombre;
        };

        void setSaldo(double nuevoSaldo) {
            saldo = nuevoSaldo;
        };

        double getSaldo() {
            return saldo;
        };

        void setNumeroCuentaRelacionado(int nuevoNumCtaRelacionada){
            numCtaRelacionada=nuevoNumCtaRelacionada;
        };
        int getnumeroCuentaRelacionado(){
            return numCtaRelacionada;
        };
        //double getSaldoTodasCuentas();

        DatosCliente(int miCuenta = 0, string miNombre = "", double miSaldo = 0.0, int minumCtaRelacionada = 0) {
            setCuenta(miCuenta);
            setNombre(miNombre);
            setSaldo(miSaldo);
            setNumeroCuentaRelacionado(minumCtaRelacionada);
        }

};

int main() {
    int cCuenta, opcion, cuentaBuscar, cNumCtaRelacionada;
    string cNombre;
    double cSaldo, nuevoSaldo ;
    char res = 'S', confirmacion;
    bool encontrado;

    fstream ArchivoClientes100("Clientes100.p3b",  ios::in | ios::out | ios::binary);

    // Prueba de Clase y sus metodos
   /*
    cout << "Cuenta : ";
    cin >> cCuenta;
    cout << "Nombre : ";
    cin >> cNombre;
    cout << "Saldo : ";
    cin >> cSaldo;        

    DatosCliente Prueba(cCuenta, cNombre, cSaldo);
    cout << "\n Los datos son " << Prueba.getCuenta() << " "  << Prueba.getNombre() << " " << Prueba.getSaldo() << endl;
  
*/
    cout << "Tamano de clase DC " << sizeof(DatosCliente) << endl;
    while ((res == 'S') || (res == 's')) {
        cout << " 1. Ingreso de Cliente \n";
        cout << " 2. Leer archivos Clientes \n";        
        cout << " 3. Consulta de Cliente \n";
        cout << " 4. Actualizacion de Cliente \n";
        cout << " 5. Borrado de Cliente \n";
        cout << " Ingrese su opcion: " ;
        cin >> opcion;

        switch (opcion) {
            case 1:
                {
                    cout << " Ingreso" << endl;

                    cout << "Cuenta : " ;
                    cin >> cCuenta;
                    cout << "\nNombre: ";
                    cin >> cNombre;
                    cout << "\nSaldo: ";
                    cin >> cSaldo;
                    cout << "\nnumero cuenta relacionado ";
                    cin >> cNumCtaRelacionada;


                    DatosCliente ClienteNuevo(cCuenta, cNombre, cSaldo,cNumCtaRelacionada);

                    ArchivoClientes100.clear(); 
                    ArchivoClientes100.seekp((cCuenta-1)*sizeof(DatosCliente), ios::beg); // se posiciona 
                    cout << cCuenta << " se almacenara en la posicion " << ArchivoClientes100.tellp() << endl;

                    ArchivoClientes100.write(reinterpret_cast <const char *>(&ClienteNuevo), sizeof(DatosCliente)); //escribe

                }
                break;
            case 2:
                {
                    cout << " Leer Archivo" << endl; 
                    cout << left << setw(10) << "Cuenta" << setw(10) << "Nombre" << right << setw(12) << "Saldo" << setw(10) << "           cuenta Relacionada" << fixed << showpoint << endl;
                    
                    ArchivoClientes100.clear();

                    DatosCliente ClientesLeer (111, "prueba", 0.0 , 0); // se inicializa instancia
                    ArchivoClientes100.seekg(0, ios::beg); //se posiciona al inicio

                    cout << "leyendo de pos : " << ArchivoClientes100.tellg() << endl;
                    ArchivoClientes100.read(reinterpret_cast <char *>(&ClientesLeer), sizeof(DatosCliente));// lee el archivo y sobreescribe los valores de la instancia

                    while(ArchivoClientes100 && !ArchivoClientes100.eof()){ // imprime
                        if (ClientesLeer.getCuenta() != 9999){
                            impresion(ClientesLeer.getCuenta(), ClientesLeer.getNombre(), ClientesLeer.getSaldo(), ClientesLeer.getnumeroCuentaRelacionado());
                        }
                        // cout << "leyendo de pos : " << ArchivoClientes100.tellg() << endl;
                        ArchivoClientes100.read(reinterpret_cast <char *>(&ClientesLeer), sizeof(DatosCliente));
                    }
                }
                break;                 
            case 3:
                {
                    // leer la cuenta a bscar
                    cout << " Consulta" << endl; 
                    cout << "Ingrese un numero de cuenta: ";
                    cin >> cuentaBuscar; // 1-100

                    ArchivoClientes100.clear();
                    //ArchivoClientes100.seekg(cuentaBuscar, ios::beg);
                    cout << "Registro en la posisiion " <<  ArchivoClientes100.tellg() << endl; //Posicion del puntero antes 
                    ArchivoClientes100.seekg((cuentaBuscar-1)*sizeof(DatosCliente), ios::beg); // Posicionamiento del puntero despues , es deciir , en el archivo:

                    DatosCliente ClientesLeer (111, "prueba", 0.0); // Creación de la instancia:
                    ArchivoClientes100.read(reinterpret_cast <char *>(&ClientesLeer), sizeof(DatosCliente));// Almacenar en la instancia 
                    cout << left << setw(10) << "Cuenta" << setw(10) << "Nombre" << right << setw(12) << "Saldo" << setw(10) << "           cuenta Relacionada" << fixed << showpoint << endl;
                    impresion(ClientesLeer.getCuenta(), ClientesLeer.getNombre(), ClientesLeer.getSaldo(), ClientesLeer.getnumeroCuentaRelacionado());// imprimir Instancia 
                }
                break;                
            case 4:
                {
                    cout << " Actualizacion" << endl;    

                    cout << "Ingrese un numero de cuenta: ";
                    cin >> cuentaBuscar; // 1-100
                    //instrucciones para ir al inicio del archivo
                    ArchivoClientes100.clear();
                    ArchivoClientes100.seekg(cuentaBuscar, ios::beg);

                    cout << "Registro en la posisiion " <<  ArchivoClientes100.tellg() << endl;
                    ArchivoClientes100.seekg((cuentaBuscar-1)*sizeof(DatosCliente), ios::beg);

                    DatosCliente ClientesLeer (111, "prueba", 0.0);

                    ArchivoClientes100.read(reinterpret_cast <char *>(&ClientesLeer), sizeof(DatosCliente));

                    if (ClientesLeer.getCuenta() !=9999){
                        cout << left << setw(10) << "Cuenta" << setw(10) << "Nombre" << right << setw(12) << "Saldo" << setw(10) << "           cuenta Relacionada" << fixed << showpoint << endl;
                        impresion(ClientesLeer.getCuenta(), ClientesLeer.getNombre(), ClientesLeer.getSaldo(), ClientesLeer.getnumeroCuentaRelacionado());

                       cout << "Ingrese el nuevo saldo : " ;
                       cin >> nuevoSaldo;
                       ClientesLeer.setSaldo(nuevoSaldo);
                       ArchivoClientes100.clear();
                       ArchivoClientes100.seekp( (cuentaBuscar - 1) * sizeof(DatosCliente), ios::beg);  //posisiiona el puntero en el archivo para leer
                       ArchivoClientes100.write(reinterpret_cast <const char *>(&ClientesLeer), sizeof(DatosCliente));
                       cout << "Datos del cliente " << ClientesLeer.getCuenta() << " han sido actualizados! " << endl;

                    }else {
                        cout << "Numero no existe ";
                    }

                }                    
                break;                
            case 5:
                {
                    cout << " Eliminacion" << endl; 

                    cout << "Ingrese la cuenta a eliminar : " << endl;
                    cin >> cuentaBuscar;

                    //instrucciones para ir al inicio del archivo
                    ArchivoClientes100.clear();
                    // obtener posicion donde se encuentra el registro
                    ArchivoClientes100.seekg((cuentaBuscar-1)*sizeof(DatosCliente), ios::beg);
                    DatosCliente ClientesLeer (111, "prueba", 0.0);
                    ArchivoClientes100.read(reinterpret_cast <char *>(&ClientesLeer), sizeof(DatosCliente));

                    if (ClientesLeer.getCuenta()!=9999){
                        encontrado=true;
                    }else {
                        encontrado=false;
                    }
                    // validar si existe o no el registro
                   // if (registro encontrado ) {
                   if (encontrado) {
                        cout << "Seguro de confirmar la eliminacion (S/N) ? " ;
                        cin >> confirmacion;
                        if ((confirmacion == 'S') || (confirmacion == 's')) {
                           ArchivoClientes100.seekp( (cuentaBuscar - 1) * sizeof(DatosCliente));
                           DatosCliente ClienteVacio(9999,"XXXXXXXXXX", 9999.99, 9 );
                           ArchivoClientes100.write(reinterpret_cast <const char *>(&ClienteVacio), sizeof(DatosCliente));
                           cout << "\nCliente ha sido eliminado!" << endl;
                        }
                        else{
                           cout << "\nCliente no ha sido eliminado!" << endl;
                        }


                    }
                    else{
                        cout << " Registro no encontrado " << endl;
                    }

                    //instrucciones para ir al inicio del archivo
                }
                break;
            default:
                {
                    cout << "Opcion No Valida!" << endl;
                    res = 'S';
                }
                break;
        }

        if ((opcion >=1 ) && (opcion <= 5)) {
            cout << "Desea continuar (S/N) ? " << endl;
            cin >> res;
        }

    }
    
    return 0;
}

void impresion(int cuentaImprimir, string nombreImprimir, double saldoImprimir, int cuentaRelacionada) {
    cout << left << setw(10) << cuentaImprimir  << setw(13) << nombreImprimir << setw(12) << setprecision(2) << right << saldoImprimir << setw(12) << cuentaRelacionada << endl;    
}