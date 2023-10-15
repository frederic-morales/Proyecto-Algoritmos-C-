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
	char telefono[10];
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
void manejoDeCuenta(); //5. funcion para depositar o debitar


//funcion para mostrar todas las cuentas en el archivo
void mostrarTodosLosRegistros();


int main(){
		
	int opc;
	
	do{
		system("cls");
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
				system("cls");
				agregar();
				system("pause");
				break;
			case 2:
				system("cls");
				eliminar();
				system("pause");
				break;
			case 3:
				system("cls");
				modificar();
				system("pause");
				break;
			case 4:
				system("cls");
				buscar();
				system("pause");
				break;
			case 5:
				system("cls");
				manejoDeCuenta();
				system("pause");
				break;
			case 6:
				system("cls");
				mostrarTodosLosRegistros();
				system("pause");
				break;
			case 7:
				//salir
				break;
			default:
				cout << endl << "Digita una opcion valida" <<endl;
				system("pause");
				system("cls");
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

        // Escribimos la nueva cuenta al final del archivo
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
                
                cout << endl << "Cuenta encontrada:" << endl;
                cout << "Numero de cuenta: " << cuentaActual.cuenta << endl;
                cout << "Nombre: " << cuentaActual.nombre << endl;
                cout << "Telefono: " << cuentaActual.telefono << endl;
                cout << "Edad: " << cuentaActual.edad << endl;
                cout << "Monto: " << cuentaActual.monto << endl;

                char confirmacion;
                //Pedimos la confirmacion de la eliminacion de la cuenta
                cout << "Seguro que desea eliminar esta cuenta? Presione '1' para eliminar, cualquier otra tecla para cancelar: ";
                cin >> confirmacion;

                if (confirmacion == '1') {
                    // Creamos un nuevo archivo para escribir las cuentas que no se borrarán
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

                        // Elimnamos el archivo original
                        remove(rutaArchivo);

                        // Renombramos el archivo temporal al nombre del archivo original
                        rename("temp.bin", rutaArchivo);
                        cout << "Cuenta eliminada exitosamente." << endl << endl;
                    } else {
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

void modificar() {
    FILE* archivo = fopen(rutaArchivo, "r+b"); 

    if (archivo != NULL) {
        Cuenta cuentaActual;
        bool cuentaEncontrada = false;

            int numeroCuenta;
   		 	cout << "Busca la cuenta que deseas modificar" << endl;
            cout << "Ingrese el numero de cuenta: ";
            cin >> numeroCuenta;

            while (fread(&cuentaActual, sizeof(Cuenta), 1, archivo) == 1) {
                if (cuentaActual.cuenta == numeroCuenta) {
                    // Mostrar los datos de la cuenta en pantalla
                    cout << endl << "Cuenta encontrada:" << endl;
                    cout << "Numero de cuenta: " << cuentaActual.cuenta << endl;
                    cout << "Nombre: " << cuentaActual.nombre << endl;
                    cout << "Telefono: " << cuentaActual.telefono << endl;
                    cout << "Edad: " << cuentaActual.edad << endl;
                    cout << "Monto: " << cuentaActual.monto << endl << endl;

                    // Permitir al usuario modificar los datos
                    cout << "Ingrese el nuevo nombre: ";
                    cin.ignore();
                    cin.getline(cuentaActual.nombre, sizeof(cuentaActual.nombre));
                    cout << "Ingrese el nuevo telefono: ";
                    cin.getline(cuentaActual.telefono, sizeof(cuentaActual.telefono));
                    cout << "Ingrese la nueva edad: ";
                    cin >> cuentaActual.edad;

                    // Colocar el puntero en la posición adecuada para sobrescribir los datos
                    long long puntero = -sizeof(Cuenta);
                    fseek(archivo, puntero, SEEK_CUR);
                    fwrite(&cuentaActual, sizeof(Cuenta), 1, archivo);
                    cuentaEncontrada = true;

                    // Mostrar los datos modificados
                    cout << endl << "Cuenta modificada:" << endl;
                    cout << "Numero de cuenta: " << cuentaActual.cuenta << endl;
                    cout << "Nombre: " << cuentaActual.nombre << endl;
                    cout << "Telefono: " << cuentaActual.telefono << endl;
                    cout << "Edad: " << cuentaActual.edad << endl;
                    cout << "Monto: " << cuentaActual.monto << endl;
                    break;
                }
            }
        if (!cuentaEncontrada) {
            cout << endl<< "La cuenta no existe." << endl << endl << endl;
        }
        fclose(archivo);
    } else {
        cout << "Error al intentar modificar la cuenta, cierre el programa e intente de nuevo, por favor." << endl;
    }
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
        bool cuentaEncontrada = false;

        if (opcionBusqueda == 1) {
            int numeroCuenta;
            cout << "Ingrese el numero de cuenta a buscar: ";
            cin >> numeroCuenta;

            while (fread(&cuentaActual, sizeof(Cuenta), 1, archivo) == 1) {
                if (cuentaActual.cuenta == numeroCuenta) {
                	
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
        } else if (opcionBusqueda == 2) {
            cin.ignore();
            char nombreBusqueda[50];
            cout << "Ingrese el nombre de cuenta a buscar: ";
            cin.getline(nombreBusqueda, sizeof(nombreBusqueda));

            while (fread(&cuentaActual, sizeof(Cuenta), 1, archivo) == 1) {
                if (strcmp(cuentaActual.nombre, nombreBusqueda) == 0) {
                	
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
            cout << endl<< "La cuenta no existe" << endl << endl << endl;
        }
        fclose(archivo);
    } else {
        cout << "Error al intentar buscar la cuenta, cierre el programa e intente de nuevo" << endl;
    }
}

void manejoDeCuenta(){
	
	int opc;
	cout << "1. Depositar " << endl;
	cout << "2. Retirar " << endl;
	cout << "Que transaccion que desea realizar: ";
	cin >> opc;
	
	FILE* archivo = fopen(rutaArchivo, "r+b");
	
	if(archivo != NULL){
        Cuenta cuentaActual;
        bool cuentaEncontrada = false;
        int numeroCuenta;
        float deposito, retiro, montoFinal;
		
		switch(opc){
			case 1:
			cout << "Ingrese el numero de cuenta: ";	
			cin >> numeroCuenta;
			
			while (fread(&cuentaActual, sizeof(Cuenta), 1, archivo) == 1) {
                if (cuentaActual.cuenta == numeroCuenta){
                	
					cout << endl << "Cuenta encontrada:" << endl;
                    cout << "Numero de cuenta: " << cuentaActual.cuenta << endl;
                    cout << "Nombre: " << cuentaActual.nombre << endl;
                    cout << "Telefono: " << cuentaActual.telefono << endl;
                    cout << "Edad: " << cuentaActual.edad << endl;
                    cout << "Monto: " << cuentaActual.monto << endl << endl;
                    
                    // Pedirle al usuario cuanto va a depositar
                    cout << "Ingrese la cantidad a depositar: ";
                    cin >> deposito;
                    montoFinal = cuentaActual.monto + deposito;
                    cuentaActual.monto = montoFinal;
                    
                    long long puntero = -sizeof(Cuenta);
                    fseek(archivo, puntero, SEEK_CUR);
                    fwrite(&cuentaActual, sizeof(Cuenta), 1, archivo);
                    cuentaEncontrada = true;
                    
                    cout << endl << "Se deposito " << deposito << " a su cuenta" << endl;
                    cout << "Su monto actual es de: " << cuentaActual.monto << endl << endl ;
                    break;
				} 
        	}
        	if (!cuentaEncontrada) {
            	cout << endl<< "La cuenta no existe."<< endl << endl;
        	}
        	fclose(archivo);
			break;
			case 2:
			cout << "Ingrese el numero de cuenta: ";	
			cin >> numeroCuenta;
			
			while (fread(&cuentaActual, sizeof(Cuenta), 1, archivo) == 1) {
                if (cuentaActual.cuenta == numeroCuenta){
                	
					cout << endl << "Cuenta encontrada:" << endl;
                    cout << "Numero de cuenta: " << cuentaActual.cuenta << endl;
                    cout << "Nombre: " << cuentaActual.nombre << endl;
                    cout << "Telefono: " << cuentaActual.telefono << endl;
                    cout << "Edad: " << cuentaActual.edad << endl;
                    cout << "Monto: " << cuentaActual.monto << endl << endl;
                    
                    // Pedirle al usurio cuanto va a depositar
                    cout << "Ingrese la cantidad a retirar: ";
                    cin >> retiro;
                    
                    if(retiro <= cuentaActual.monto){
                    	montoFinal = cuentaActual.monto - retiro;
                    	cuentaActual.monto = montoFinal;
                    
                   		long long puntero = -sizeof(Cuenta);
                    	fseek(archivo, puntero, SEEK_CUR);
                    	fwrite(&cuentaActual, sizeof(Cuenta), 1, archivo);
                    	cuentaEncontrada = true;
                    
                    	cout << endl << "Se retiro " << retiro << " de su cuenta" << endl;
                    	cout << "Su monto actual es de: " << cuentaActual.monto << endl << endl ;
					} else{
						cout << endl << "No puede retirar esa cantidad" << endl;
						cout << "No existen fondos suficientes" << endl;
					}
                    break;
				} 
        	}
        	if (!cuentaEncontrada) {
            	cout << endl<< "La cuenta no existe."<< endl << endl;
        	}
        	fclose(archivo);
			break;
		}
		
	} else{
		cout << "Error al intentar realizar la transaccion";
	}
		
}

