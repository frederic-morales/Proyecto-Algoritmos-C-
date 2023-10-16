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
void crearArchivo(); //Solo se ejecutara una vez cuando el archivo no exista, osea no existen cuentas
void cargarArchivoCreado();


//funcion para generar numero de cuenta aleatorio
int generarNumeroDeCuenta();


//funciones de las 6 opciones
void agregar();// 1. funcion para abrir y agregar Cuenta al archivo
void eliminar();// 2. funcion para buscar y eliminar una Cuenta en el archivo
void modificar(); //3. funcion para buscar y editar la informacion de la cuenta(Nombre, Teléfono, Edad)
void buscar();// 4. funcion para buscar cuenta por cuenta o por nombre
void manejoDeCuenta(); //5. funcion para depositar o debitar
void reportes();//6. funcion para imprimir diferentes tipos de reportes

//funciones de los reportes
void mostrarTodosLosRegistros();//funcion para mostrar todas las cuentas en el archivo - funcion 1 de los reportes
void reportePorEdad(int edadMinima, int edadMaxima);//fucion para mostrar cuentas por edad - funcion 2 de los reportes
void reportePorMonto(float montMinimo, float montMaximo);//fucion para mostrar cuentas por monto - funcion 3 de los reportes
void reportePorCuenta(int numCuenta);//fucion para mostrar cuentas por numero de cuenta - funcion 4 de los reportes

int main(){
		
	int opc;
	
	do{
		system("cls");
		cargarArchivoCreado();
		cout << "\tBienvenido" <<endl;
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
				reportes();
				system("pause");
				break;
			default:
				cout << endl << "Saliendo del programa" <<endl;
			break;
		}
	}
	while(opc < 7);

	return 0;
}

void cargarArchivoCreado(){
	
	// abrimos el archivo para verificar si existe el archivo
	ifstream archivo(rutaArchivo, ios::binary);
    
    if (!archivo) {
        // Si el archivo no existe, llama a la función crearArchivo() para crearlo
        crearArchivo();
    } else { // Si el archivo existe lo cerramos 
        //cout << "Archivo cargado exitosamente" << endl;
        archivo.close();
    }
	
}

void crearArchivo(){
	
	ofstream archivo(rutaArchivo, ios::binary);
	
	if(!archivo){	
		cout << "Error al crear el archivo" <<endl; //si el archivo no se crea correctamente
	} else{
		//Cerramos el archivo
		archivo.close();
		// cout << "Archivo Creado exitosamente " << endl << endl;
	}
	
}

int generarNumeroDeCuenta(){

	//utilizamos el tiempo para que los numeros sean diferentes cada vez que se llame la funcion
	srand(static_cast<unsigned int>(time(nullptr)));
	
	int numeroAleatorio = 10000 + rand() % 90000;
	
	return numeroAleatorio;
}

void agregar(){
	
	FILE* archivo = fopen(rutaArchivo, "ab"); // "wb": para abrir en modo añadir
	
	if(archivo != NULL){
		
		// Obtener la posición de la última cuenta en el archivo
        fseek(archivo, 0, SEEK_END);
        long posicion = ftell(archivo);

        Cuenta nuevaCuenta;
        nuevaCuenta.cuenta = generarNumeroDeCuenta();

        cout << "Su numero de cuenta es: " << nuevaCuenta.cuenta << endl;
        cout << "Ingresa el nombre: ";
        cin.ignore();
        cin.getline(nuevaCuenta.nombre, sizeof(nuevaCuenta.nombre));
        cout << "Ingrese el numero de telefono: ";
        cin.getline(nuevaCuenta.telefono, sizeof(nuevaCuenta.telefono));
        cout << "Ingrese la edad: ";
        cin >> nuevaCuenta.edad;
        cout << "Ingrese el monto: ";
        cin >> nuevaCuenta.monto;

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

    FILE* archivo = fopen(rutaArchivo, "r+b");

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
                cout << "Monto: Q" << cuentaActual.monto << endl;

                char confirmacion;

                cout << endl << "Seguro que desea eliminar esta cuenta? Presione '1' para eliminar, cualquier otra tecla para cancelar: ";
                cin >> confirmacion;

                if (confirmacion == '1') {

                    FILE* archivoTemporal = fopen("temp.bin", "wb");// Creamos un nuevo archivo para escribir las cuentas que no se borrarán
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
            cout << endl << "No se encontro ninguna cuenta con ese numero de cuenta" << endl << endl;
        }
    } else {
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

                    cout << endl << "Cuenta encontrada:" << endl;
                    cout << "Numero de cuenta: " << cuentaActual.cuenta << endl;
                    cout << "Nombre: " << cuentaActual.nombre << endl;
                    cout << "Telefono: " << cuentaActual.telefono << endl;
                    cout << "Edad: " << cuentaActual.edad << endl;
                    cout << "Monto: Q" << cuentaActual.monto << endl << endl;

                    cout << "Ingrese el nuevo nombre: ";
                    cin.ignore();
                    cin.getline(cuentaActual.nombre, sizeof(cuentaActual.nombre));
                    cout << "Ingrese el nuevo telefono: ";
                    cin.getline(cuentaActual.telefono, sizeof(cuentaActual.telefono));
                    cout << "Ingrese la nueva edad: ";
                    cin >> cuentaActual.edad;

                    long long puntero = -sizeof(Cuenta);
                    fseek(archivo, puntero, SEEK_CUR);
                    fwrite(&cuentaActual, sizeof(Cuenta), 1, archivo);
                    cuentaEncontrada = true;

                    cout << endl << "Cuenta modificada:" << endl;
                    cout << "Numero de cuenta: " << cuentaActual.cuenta << endl;
                    cout << "Nombre: " << cuentaActual.nombre << endl;
                    cout << "Telefono: " << cuentaActual.telefono << endl;
                    cout << "Edad: " << cuentaActual.edad << endl;
                    cout << "Monto: Q" << cuentaActual.monto << endl;
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
    cout << "Opciones de busqueda:" << endl;
    cout << "1. Buscar por numero de cuenta" << endl;
    cout << "2. Buscar por nombre de cuenta" << endl;
    cout << "Elija una opcion: ";
    cin >> opcionBusqueda;

    FILE* archivo = fopen(rutaArchivo, "rb"); 

    if (archivo != NULL) {
        Cuenta cuentaActual;
        bool cuentaEncontrada = false;

        if (opcionBusqueda == 1) {
            int numeroCuenta;
            cout << "Ingrese el numero de cuenta a buscar: ";
            cin >> numeroCuenta;

            while (fread(&cuentaActual, sizeof(Cuenta), 1, archivo) == 1) {
                if (cuentaActual.cuenta == numeroCuenta) {
                	
                    cout << endl << "Cuenta encontrada:" << endl;
                    cout << "Numero de cuenta: " << cuentaActual.cuenta << endl;
                    cout << "Nombre: " << cuentaActual.nombre << endl;
                    cout << "Telefono: " << cuentaActual.telefono << endl;
                    cout << "Edad: " << cuentaActual.edad << endl;
                    cout << "Monto: Q" << cuentaActual.monto << endl << endl;
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
                	
                    cout << endl << "Cuenta encontrada:" << endl;
                    cout << "Numero de cuenta: " << cuentaActual.cuenta << endl;
                    cout << "Nombre: " << cuentaActual.nombre << endl;
                    cout << "Telefono: " << cuentaActual.telefono << endl;
                    cout << "Edad: " << cuentaActual.edad << endl;
                    cout << "Monto: Q" << cuentaActual.monto << endl;
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
                    cout << "Monto: Q" << cuentaActual.monto << endl << endl;
                    
                    cout << "Ingrese la cantidad a depositar: ";
                    cin >> deposito;
                    montoFinal = cuentaActual.monto + deposito;
                    cuentaActual.monto = montoFinal;
                    
                    long long puntero = -sizeof(Cuenta);
                    fseek(archivo, puntero, SEEK_CUR);
                    fwrite(&cuentaActual, sizeof(Cuenta), 1, archivo);
                    cuentaEncontrada = true;
                    
                    cout << endl << "Se deposito Q" << deposito << " a su cuenta" << endl;
                    cout << "Su monto actual es de: Q" << cuentaActual.monto << endl << endl ;
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
                    cout << "Monto: Q" << cuentaActual.monto << endl << endl;
                    
                    cout << "Ingrese la cantidad a retirar: ";
                    cin >> retiro;
                    
                    if(retiro <= cuentaActual.monto){
                    	montoFinal = cuentaActual.monto - retiro;
                    	cuentaActual.monto = montoFinal;
                    
                   		long long puntero = -sizeof(Cuenta);
                    	fseek(archivo, puntero, SEEK_CUR);
                    	fwrite(&cuentaActual, sizeof(Cuenta), 1, archivo);
                    	cuentaEncontrada = true;
                    
                    	cout << endl << "Se retiro Q" << retiro << " de su cuenta" << endl;
                    	cout << "Su monto actual es de: Q" << cuentaActual.monto << endl << endl ;
					} else{
						cout << endl << "No puede retirar esa cantidad" << endl;
						cout << "No existen fondos suficientes" << endl << endl;
						cuentaEncontrada = true;
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

// REPORTES

void reportes(){
	
	int opc;
	
	cout << "\tReportes" << endl << endl;
	cout << "1.Reporte General de Cuentahabientes" << endl;
	cout << "2.Reporte Cuenthabientes por Edad" << endl;
	cout << "3.Reporte de Cuenthabientes por Monto" << endl;
	cout << "4.Reporte de una Cuenta" << endl;
	cout << "O.Salir" << endl;
	cout << endl << "Que opcion desea realizar: ";
	cin >> opc;
	
	switch(opc){
		case 1:
			system("cls");
			mostrarTodosLosRegistros();
			break;
		case 2:
			system("cls");
			int edadMinima, edadMaxima;
			cout << "Ingrese la edad minima: ";
			cin >> edadMinima;
			cout << "Ingrese la edad minima: ";
			cin >> edadMaxima;
			reportePorEdad(edadMinima, edadMaxima);
			break;
		case 3:
			system("cls");
			float montMinimo, montMaximo;
			cout << "Ingrese el monto minimo: ";
			cin >> montMinimo;
			cout << "Ingrese el monto maximo: ";
			cin >> montMaximo;
			reportePorMonto(montMinimo, montMaximo);
			break;
		case 4:
			system("cls");
			int numeroDeCuenta;
			cout << "Ingrese el numero de cuenta: ";
			cin >> numeroDeCuenta;
			reportePorCuenta(numeroDeCuenta);
			break;
		default:
			break;
	}
	
		
}

void mostrarTodosLosRegistros(){
	            
	int opc;
	bool cuentaEncontrada = false;
	
	FILE* archivo = fopen(rutaArchivo, "rb");
	
	if(archivo != NULL){
		
		Cuenta cuentaActual;
		cout << endl << "\tMostrar cuentas creadas " << endl << endl;
        while (fread(&cuentaActual, sizeof(Cuenta), 1, archivo) == 1) {
			cout << "Numero de cuenta: " << cuentaActual.cuenta << endl;
            cout << "Nombre: " << cuentaActual.nombre << endl;
            cout << "Telefono: " << cuentaActual.telefono << endl;
            cout << "Edad: " << cuentaActual.edad << endl;
            cout << "Monto: Q" << cuentaActual.monto << endl <<endl;
            cuentaEncontrada = true;
        }		
        cout << "------------------------" << endl << endl;
		fclose(archivo);
		
		if(cuentaEncontrada) {
			
			cout << "Desea generar un archivo de texto para este reporte?" << endl;
        	cout << "Escriba 1 para confirmar 2 para cancelar: ";
    		cin >> opc;
    		
    		if(opc == 1){
    			
				char nomArchivoTexto[50];
            	cout << endl << "Como desea llamar a su reporte?" << endl;
				cout << "debe agregarle extension .txt: ";
                cin.ignore();
                cin.getline(nomArchivoTexto, sizeof(nomArchivoTexto));
                
                // le pedimos al usuario el nombre del archivo de texto donde se guardaran las cuentas
                
				ofstream archivoDeTexto(nomArchivoTexto);
                archivoDeTexto << "Cuentas encontradas: " << endl << endl;
                
                //Volvemos a abrir el archivo binario para guardar la informacion e el nuevo archivo de texto
                FILE* archivo = fopen(rutaArchivo, "rb");
            	Cuenta cuentaActual;
                
                while (fread(&cuentaActual, sizeof(Cuenta), 1, archivo) == 1) {

					archivoDeTexto << "Numero de cuenta: " << cuentaActual.cuenta << endl;
					archivoDeTexto << "Nombre: " << cuentaActual.nombre << endl;
              		archivoDeTexto << "Telefono: " << cuentaActual.telefono << endl;
                	archivoDeTexto << "Edad: " << cuentaActual.edad << endl;
                	archivoDeTexto << "Monto: Q" << cuentaActual.monto << endl << endl ;
             	
        		}
    			archivoDeTexto.close();
    			fclose(archivo);
			}
		}
		
	} else{
		cout << "No se pudo abrir el archivo" << rutaArchivo << endl;
		cout << "Por lo tanto no se mostraran las cuentas" << endl;
	}
}

void reportePorEdad(int edadMinima, int edadMaxima){
	
	int opc;
	bool cuentaEncontrada = false;
	
	FILE* archivo = fopen(rutaArchivo, "rb");
	
	if (archivo != NULL){	
		Cuenta cuentaActual;
		
		cout << endl << "Cuentas encontradas por el rango de edad:" << endl << endl;
		while (fread(&cuentaActual, sizeof(Cuenta), 1, archivo) == 1) {
        	if (cuentaActual.edad >= edadMinima && cuentaActual.edad <= edadMaxima) {
            	cout << "Numero de cuenta: " << cuentaActual.cuenta << endl;
           		cout << "Nombre: " << cuentaActual.nombre << endl;
                cout << "Telefono: " << cuentaActual.telefono << endl;
                cout << "Edad: " << cuentaActual.edad << endl;
                cout << "Monto: Q" << cuentaActual.monto << endl << endl ;
                cuentaEncontrada = true;
            }
        }
        cout << "------------------------" << endl << endl;
		fclose(archivo);
		
		if(cuentaEncontrada) {
			
			cout << "Desea generar un archivo de texto para este reporte?" << endl;
        	cout << "Escriba 1 para confirmar 2 para cancelar: ";
    		cin >> opc;
    		
    		if(opc == 1){
    			
				char nomArchivoTexto[50];
            	cout << endl << "Como desea llamar a su reporte?" << endl;
				cout << "debe agregarle extension .txt: ";
                cin.ignore();
                cin.getline(nomArchivoTexto, sizeof(nomArchivoTexto));
                
				ofstream archivoDeTexto(nomArchivoTexto);
                archivoDeTexto << "Cuentas encontradas por el rango de edad: " << endl << endl;
                
                FILE* archivo = fopen(rutaArchivo, "rb");
            	Cuenta cuentaActual;
                
                while (fread(&cuentaActual, sizeof(Cuenta), 1, archivo) == 1) {
        			if (cuentaActual.edad >= edadMinima && cuentaActual.edad <= edadMaxima) {

						archivoDeTexto << "Numero de cuenta: " << cuentaActual.cuenta << endl;
           				archivoDeTexto << "Nombre: " << cuentaActual.nombre << endl;
                		archivoDeTexto << "Telefono: " << cuentaActual.telefono << endl;
                		archivoDeTexto << "Edad: " << cuentaActual.edad << endl;
                		archivoDeTexto << "Monto: Q" << cuentaActual.monto << endl << endl ;
             	
            		}
        		}
    			archivoDeTexto.close();
    			fclose(archivo);
			}
		}		
		
	} else {
		cout << "Error al buscar las cuentas";
	}
}

void reportePorMonto(float montMinimo, float montMaximo){
	
	int opc;
	bool cuentaEncontrada = false;
	
	FILE* archivo = fopen(rutaArchivo, "rb");
	
	if (archivo != NULL){	
		Cuenta cuentaActual;
		
		cout << endl << "Cuentas encontradas por el rango del monto:" << endl << endl;
		while (fread(&cuentaActual, sizeof(Cuenta), 1, archivo) == 1) {
        	if (cuentaActual.monto>= montMinimo && cuentaActual.monto <= montMaximo) {
            	cout << "Numero de cuenta: " << cuentaActual.cuenta << endl;
           		cout << "Nombre: " << cuentaActual.nombre << endl;
                cout << "Telefono: " << cuentaActual.telefono << endl;
                cout << "Edad: " << cuentaActual.edad << endl;
                cout << "Monto: Q" << cuentaActual.monto << endl << endl ;
                cuentaEncontrada = true;
            }
        }
		cout << "------------------------" << endl << endl;
		fclose(archivo);
		
		if(cuentaEncontrada) {
			
			cout << "Desea generar un archivo de texto para este reporte?" << endl;
        	cout << "Escriba 1 para confirmar 2 para cancelar: ";
    		cin >> opc;
    		
    		if(opc == 1){
    			
				char nomArchivoTexto[50];
            	cout << endl << "Como desea llamar a su reporte?" << endl;
				cout << "debe agregarle extension .txt: ";
                cin.ignore();
                cin.getline(nomArchivoTexto, sizeof(nomArchivoTexto));
                
				ofstream archivoDeTexto(nomArchivoTexto);
                archivoDeTexto << "Cuentas encontradas por el rango del monto: " << endl;
                
                FILE* archivo = fopen(rutaArchivo, "rb");
            	Cuenta cuentaActual;
                
                while (fread(&cuentaActual, sizeof(Cuenta), 1, archivo) == 1) {
        			if (cuentaActual.monto>= montMinimo && cuentaActual.monto <= montMaximo) {

						archivoDeTexto << "Numero de cuenta: " << cuentaActual.cuenta << endl;
           				archivoDeTexto << "Nombre: " << cuentaActual.nombre << endl;
                		archivoDeTexto << "Telefono: " << cuentaActual.telefono << endl;
                		archivoDeTexto << "Edad: " << cuentaActual.edad << endl;
                		archivoDeTexto << "Monto: Q" << cuentaActual.monto << endl << endl ;
             	
            		}
        		}
    			archivoDeTexto.close();
    			fclose(archivo);
			}
		}    	
        
	} else {
		cout << "Error al buscar las cuentas";
	}
}

void reportePorCuenta(int numCuenta){
	
	int opc;
	
	FILE * archivo = fopen(rutaArchivo, "rb");
	
	if(archivo != NULL){
		Cuenta cuentaActual;
		
		while(fread(&cuentaActual, sizeof(Cuenta), 1, archivo) == 1){
			if(cuentaActual.cuenta == numCuenta){
				cout << endl << "Cuenta econtrada" << endl;
				cout << "Numero de cuenta: " << cuentaActual.cuenta << endl;
           		cout << "Nombre: " << cuentaActual.nombre << endl;
                cout << "Telefono: " << cuentaActual.telefono << endl;
                cout << "Edad: " << cuentaActual.edad << endl;
                cout << "Monto: Q" << cuentaActual.monto << endl << endl ;
                cout << "---------------------------" << endl << endl;
                
                cout << "Desea generar un archivo de texto para este reporte?" << endl;
                cout << "Escriba 1 para confirmar 2 para cancelar: ";
                cin >> opc;
                
                if(opc == 1){
                	
					char nomArchivoTexto[50];
                	cout << endl << "Como desea llamar a su reporte?" << endl;
					cout << "debe agregarle extension .txt: ";
                	cin.ignore();
					cin.getline(nomArchivoTexto, sizeof(nomArchivoTexto));
                	
					ofstream archivoDeTexto(nomArchivoTexto);
  					archivoDeTexto << "Cuenta econtrada" << endl;
					archivoDeTexto << "Numero de cuenta: " << cuentaActual.cuenta << endl;
           			archivoDeTexto << "Nombre: " << cuentaActual.nombre << endl;
                	archivoDeTexto << "Telefono: " << cuentaActual.telefono << endl;
                	archivoDeTexto << "Edad: " << cuentaActual.edad << endl;
                	archivoDeTexto << "Monto: Q" << cuentaActual.monto << endl << endl ;
                	
                	archivoDeTexto.close();
                	
                	cout << "archivo creado exitosamente" << endl;
				}
			}
		}

		fclose(archivo);
	} else{
		cout << "Error al buscar las cuentas";
	}
	
}

