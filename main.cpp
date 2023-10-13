#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <string.h>
#include <fstream> //cabecera para trabajar con archivos

using namespace std;

const char rutaArchivo[] = "cuentas.bin";

struct Cuenta{
	int cuenta;
	char nombre[50];
	char telefono[50];
	int edad;
	float monto;
} cuenta[50];
	
//funciones de archivo
void crearArchivo(); //Solo se ejecutara una vez cuando el archivo no exista
void cargarArchivoCreado();


//funcion para generar numero de cuenta aleatorio
int generarNumeroDeCuenta();


//funciones de las 6 opciones
void agregar();// 1. funcion para abrir y agregar Cuenta al archivo
void eliminar();// 2. funcion para buscar y eliminar una Cuenta en el archivo
void modificar(); //3. funcion para buscar y editar la informacion de la cuenta(Nombre, Teléfono, Edad)
void buscar();// 4. funcion para buscar cuenta por cuenta o por nombre


//funcion para mostrar todas las cuentas en el archivo
void mostrarTodosLosRegistros();

int main(){
		
	int opc;
	
	do{
		cargarArchivoCreado();
		cout << endl << "\tBienvenido" <<endl;
		cout<<"\n1.Agregar"<<endl;
		cout<<"2.Eliminar"<<endl;
		cout<<"3.Modificar"<<endl;
		cout<<"4.Buscar"<<endl;
		cout<<"5.Manejo de Cuenta"<<endl;
		cout<<"6.Reportes"<<endl;
		cout<<"7.Salir"<<endl;
		cout<<"\nQue opcion deseas realizar: ";
		cin>>opc;
		
		switch(opc){
			case 1:
				agregar();
				system("pause");
				break;
			case 2:
				eliminar();
				system("pause");
				break;
			case 3:
				modificar();
				break;
			case 4:
				buscar();
				system("pause");
				break;
			case 5:
				//Eliminar
				break;
			case 6:
				mostrarTodosLosRegistros();
				system("pause");
				break;
			case 7:
				//salir
				break;
			default:
				cout << endl << "Digita un opcion valida" <<endl;
				system("pause");
				break;
		}
	}
	while(opc != 7);

	return 0;
}

//Esta funcion es para mostrar todas las cuentas creadas 
void mostrarTodosLosRegistros(){
	             
	FILE* archivo = fopen(rutaArchivo, "rb"); // "rb:" Read Binary
	
	if(archivo != NULL){
		
		Cuenta cuentaActual;

		cout << endl << "\tMostrar cuentas creadas " << endl << endl;

        while (fread(&cuentaActual, sizeof(Cuenta), 1, archivo) == 1) {
            // Muestra los datos de la cuenta en pantalla
			cout << "Numero de cuenta: " << cuentaActual.cuenta << endl;
            cout << "Nombre: " << cuentaActual.nombre << endl;
            cout << "Telefono: " << cuentaActual.telefono << endl;
            cout << "Edad: " << cuentaActual.edad << endl;
            cout << "Monto: " << cuentaActual.monto << endl <<endl;
        }		
        cout << "------------------------" << endl << endl;
		fclose(archivo);
		
	} else{
		cout << "No se pudo abrir el archivo" << rutaArchivo << endl;
		cout << "Por lo tanto no se mostraran las cuentas" << endl;
	}
}

void cargarArchivoCreado(){
	
	// Intenta abrir el archivo en modo lectura (para verificar si existe)
	ifstream archivo(rutaArchivo, ios::binary);
    
    if (!archivo) {
        // Si el archivo no existe, llama a la función crearArchivo() para crearlo
        crearArchivo();
    } else { // Si el archivo existe
        cout << "Archivo cargado exitosamente" << endl;
        archivo.close();
    }
	
}

void crearArchivo(){
	
	ofstream archivo(rutaArchivo, ios::binary);
	
	if(!archivo){	
		cout << "Error al crear el archivo" <<endl; //si el archivo no se crea correctamente se crea un mensaje de error
	} else{
		
		//Cerramos el archivo
		archivo.close();
		
		cout << "Archivo Creado exitosamente " << endl << endl;
	}
	
}

int generarNumeroDeCuenta(){

	//utilizamos el tiempo para que los numeros sean diferentes cada vez que se llame la funcion
	srand(static_cast<unsigned int>(time(nullptr)));
	
	int numeroAleatorio = 10000 + rand() % 90000;
	
	return numeroAleatorio;
}

void agregar(){
	
	FILE* archivo = fopen(rutaArchivo, "ab"); // "wb": para abrir en modo añadir (Append Binary)
	
	if(archivo != NULL){
		
		// Obtener la posición de la última cuenta en el archivo
        fseek(archivo, 0, SEEK_END);
        long posicion = ftell(archivo);

        Cuenta nuevaCuenta;
        // nuevaCuenta.cuenta = (posicion / sizeof(Cuenta)) + 1; // Calcula el número de cuenta
        nuevaCuenta.cuenta = generarNumeroDeCuenta(); // Calcula el número de cuenta

        cout << endl << "Su numero de cuenta es: " << nuevaCuenta.cuenta << endl;
        cout << "Ingresa el nombre: ";
        cin.ignore();
        cin.getline(nuevaCuenta.nombre, sizeof(nuevaCuenta.nombre));
        cout << "Ingrese el numero de telefono: ";
        cin.getline(nuevaCuenta.telefono, sizeof(nuevaCuenta.telefono));
        cout << "Ingrese la edad: ";
        cin >> nuevaCuenta.edad;
        cout << "Ingrese el monto: ";
        cin >> nuevaCuenta.monto;

        // Escribir la nueva cuenta al final del archivo
        fwrite(&nuevaCuenta, sizeof(Cuenta), 1, archivo);
        fclose(archivo);

        cout << "Cuenta agregada exitosamente." << endl;
        cout << "------------------------" << endl << endl;
		
	} else{
		cout << "No se pudo abrir el archivo" << rutaArchivo << endl;
		cout << "Por lo tanto no se puede agregar una nueva cuenta" << endl;
	}
}

void eliminar() {
    int numeroCuenta;
    cout << "Ingrese el numero de cuenta que desea eliminar: ";
    cin >> numeroCuenta;

    FILE* archivo = fopen(rutaArchivo, "r+b"); // "r+b": Lectura y escritura binaria

    if (archivo != NULL) {
        Cuenta cuentaActual;
        bool cuentaEncontrada = false;

        while (fread(&cuentaActual, sizeof(Cuenta), 1, archivo) == 1) {
            if (cuentaActual.cuenta == numeroCuenta) {
                // Muestra los datos de la cuenta a elimnar en pantalla
                cout << endl << "Cuenta encontrada:" << endl;
                cout << "Numero de cuenta: " << cuentaActual.cuenta << endl;
                cout << "Nombre: " << cuentaActual.nombre << endl;
                cout << "Telefono: " << cuentaActual.telefono << endl;
                cout << "Edad: " << cuentaActual.edad << endl;
                cout << "Monto: " << cuentaActual.monto << endl;

                char confirmacion;
                cout << "Seguro que desea eliminar esta cuenta? Presione '1' para eliminar, cualquier otra tecla para cancelar: ";
                cin >> confirmacion;

                if (confirmacion == '1') {
                    // Crear un archivo temporal para guardar las cuentas que no se eliminarán
                    FILE* archivoTemporal = fopen("temp.bin", "wb");
                    if (archivoTemporal != NULL) {
                        fseek(archivo, 0, SEEK_SET);

                        while (fread(&cuentaActual, sizeof(Cuenta), 1, archivo) == 1) {
                            if (cuentaActual.cuenta != numeroCuenta) {
                                fwrite(&cuentaActual, sizeof(Cuenta), 1, archivoTemporal);
                            }
                        }

                        fclose(archivo);
                        fclose(archivoTemporal);

                        // Eliminar el archivo original
                        remove(rutaArchivo);

                        // Renombrar el archivo temporal al nombre original
                        rename("temp.bin", rutaArchivo);
                        cout << "Cuenta eliminada exitosamente." << endl << endl;
                    } else {
                    	//Error al abrir el archiv temporal
                        cout << "Error al elimnar la cuenta, cierre el programa e intente de nuevo" << endl;
                    }
                } else {
                    cout << "Eliminacion cancelada." << endl << endl;
                }

                cuentaEncontrada = true;
                break;
            }
        }

        if (!cuentaEncontrada) {
            cout << "No se encontro ninguna cuenta con ese numero de cuenta" << endl << endl;
        }
    } else {
    	// No se pudo abrir el archivo
        cout << "Error al elimnar la cuenta, cierre el programa e intente de nuevo" << endl << endl;
    }
}

void modificar(){
	
		
			
}

void buscar() {
    int opcionBusqueda;
    cout << endl << "Opciones de busqueda:" << endl;
    cout << "1. Buscar por numero de cuenta" << endl;
    cout << "2. Buscar por nombre de cuenta" << endl;
    cout << "Elija una opcion: ";
    cin >> opcionBusqueda;

    FILE* archivo = fopen(rutaArchivo, "rb"); // "rb: Read Binary" - Abre el archivo en modo lectura binaria

    if (archivo != NULL) {
        Cuenta cuentaActual;
        bool cuentaEncontrada = false; // Variable para indicar si se encontró una cuenta

        if (opcionBusqueda == 1) { // Buscar por número de cuenta
            int numeroCuenta;
            cout << "Ingrese el numero de cuenta a buscar: ";
            cin >> numeroCuenta;

            while (fread(&cuentaActual, sizeof(Cuenta), 1, archivo) == 1) {
                if (cuentaActual.cuenta == numeroCuenta) {
                    // Muestra los datos de la cuenta en pantalla
                    cout << endl << endl << "Cuenta encontrada:" << endl;
                    cout << "Numero de cuenta: " << cuentaActual.cuenta << endl;
                    cout << "Nombre: " << cuentaActual.nombre << endl;
                    cout << "Telefono: " << cuentaActual.telefono << endl;
                    cout << "Edad: " << cuentaActual.edad << endl;
                    cout << "Monto: " << cuentaActual.monto << endl << endl;
                    cuentaEncontrada = true;
                    break;
                }
            }
        } else if (opcionBusqueda == 2) { // Buscar por nombre de cuenta
            cin.ignore();
            char nombreBusqueda[50];
            cout << "Ingrese el nombre de cuenta a buscar: ";
            cin.getline(nombreBusqueda, sizeof(nombreBusqueda));

            while (fread(&cuentaActual, sizeof(Cuenta), 1, archivo) == 1) {
                if (strcmp(cuentaActual.nombre, nombreBusqueda) == 0) {
                    // Muestra los datos de la cuenta en pantalla
                    cout << endl << endl << "Cuenta encontrada:" << endl;
                    cout << "Numero de cuenta: " << cuentaActual.cuenta << endl;
                    cout << "Nombre: " << cuentaActual.nombre << endl;
                    cout << "Telefono: " << cuentaActual.telefono << endl;
                    cout << "Edad: " << cuentaActual.edad << endl;
                    cout << "Monto: " << cuentaActual.monto << endl;
                    cuentaEncontrada = true;
                }
            }
        }

        if (!cuentaEncontrada) {
            cout << endl<< "La cuenta no existe." << endl << endl << endl;
        }
        fclose(archivo);
    } else {
        cout << "No se pudo abrir el archivo " << rutaArchivo << endl;
        cout << "No se pueden buscar cuentas." << endl;
    }
}


