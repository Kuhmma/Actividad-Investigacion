#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>



using namespace std;
//mostrara los archivos

void mostrarArchivo(const string& rutaArchivo) {
    ifstream archivo(rutaArchivo.c_str());
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }
    string linea;
    cout << "Rutinas de ejercicios:" << endl;
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }
    archivo.close();
}

//cuenta cuantas veces aparece una palabra
int contarpalabra(const string& rutaArchivo, const string& palabra){
	ifstream archivo(rutaArchivo.c_str());
	string linea;
	int contador=0;
	while(getline(archivo,linea)){
		size_t pos=linea.find(palabra);
		while(pos !=string::npos){
			contador++;
			pos=linea.find(palabra, pos+palabra.size());
		}
	}
	archivo.close();
	return contador;
}

void reemplazarpalabra(const string& rutaArchivo, const string& viejapalabra, const string& nuevapalabra){	
	ifstream archivo(rutaArchivo.c_str());
	string contenido, linea;
	while (getline(archivo, linea)){
		size_t pos=linea.find(viejapalabra);
		while(pos !=string::npos){
			linea.replace(pos, viejapalabra.size(), nuevapalabra);//esta linea es la que encuentra y reemplaza
			pos=linea.find(viejapalabra, pos + nuevapalabra.size());
		}
		contenido += linea + "\n";
	}
	archivo.close();
		
	ofstream archivoSalida(rutaArchivo.c_str());
	archivoSalida<<contenido;
	archivoSalida.close();
}

void agregarRutina(const string& rutaArchivo, const string& nuevarutina){
	ofstream archivo(rutaArchivo.c_str(), ios::app);
	archivo<<nuevarutina<<endl;
	archivo.close();
}
int stringToInt(const string& str){
	int num;
	istringstream iss(str);
	iss>>num;
	if(iss.fail()){
		throw invalid_argument("no se convirtio ");
	}
	return num;
}
double calcularcalorias(const string& rutaArchivo){
    ifstream archivo(rutaArchivo.c_str());
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return 0.0;
    }
    int suma=0, contador=0;
    string linea;
    
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        string palabra;
        while (iss >> palabra) {
            if (palabra == "quemo" || palabra == "quemo,") {
                try {
                    string caloriasStr;
                    iss >> caloriasStr;
                    int calorias = stringToInt(caloriasStr);
                    suma += calorias;
                    contador++;
                    cout << "Calorías quemadas en este día: " << calorias << endl;
                }
                catch (const invalid_argument& e) {
                    cout << "No se pudo convertir calorías en la línea: " << linea << endl;
                }
            }
        }
    }
    archivo.close();
    if(contador==0){
        cout << "No se encontraron registros de calorías." << endl;
        return 0.0;
    }
    cout << "Suma total de calorías: " << suma << ", Total de registros: " << contador << endl;

    return static_cast<double>(suma) / contador;
}



void copiarcontenido(const string& origen, const string& destino){
	ifstream archivoOrigen(origen.c_str());
	ofstream archivoDestino(destino.c_str());
	string linea;
	while(getline(archivoOrigen,linea)){
		archivoDestino<<linea<<endl;
	}
	archivoOrigen.close();
    archivoDestino.close();
}
int main(){
	string rutaArchivo="C:\\Users\\Usuario\\Desktop\\INVESTIGACION PROGRAMACION\\Programa\\fitness.txt";
	
	int op=0;
	while (op !=7){
		cout <<"MENU: "<<endl;
		cout <<"1. Mostrar las rutinas de ejercicios"<<endl;
		cout <<"2. Cuantas veces se repite un ejercicio especifico"<<endl;
		cout <<"3. Reemplazar el nombre de un ejercicio"<<endl;
		cout <<"4. Agregar una nueva rutina"<<endl;
		cout <<"5. Realizar la media aritmetica de las calorias quemadas"<<endl;
		cout <<"6. Copiar el contenido de fitness.txt a resultado.txt"<<endl;
		cout <<"7.Salir"<<endl;
		cout <<"Seleccione una opcion: ";
		cin  >>op;
		
		switch (op){
			case 1:
				mostrarArchivo(rutaArchivo);
				break;
			
			case 2:{
				string ejercicio;
				cout<<"Ingrese el nombre del ejercicio: ";
				cin.ignore();
				getline(cin, ejercicio);
				int repeticiones=contarpalabra(rutaArchivo, ejercicio);
				cout<< "El ejercicio' "<<ejercicio<<"' se repite "<<repeticiones<<" veces."<<endl;
				break;
			}
			case 3:{
				string viejonombre, nuevonombre;
				cout<<"Ingrese el nombre del ejercicio que desea reemplazar: ";
				cin.ignore();
				getline(cin, viejonombre);
				cout<<"Ingrese el nuevo nombre: ";
				getline(cin, nuevonombre);
				reemplazarpalabra(rutaArchivo, viejonombre, nuevonombre);
				cout<<"se ha reemplazado la palabra."<<endl;
				break;
			}
			
			case 4:{
				string nuevarutina;
				cout<<"Ingrese la nueva rutina (NUMERO. EJERCICIO-CALORIAS): ";
				cin.ignore();
				getline(cin, nuevarutina);
				agregarRutina(rutaArchivo, nuevarutina);
				cout<<"Rutina agregada"<<endl;
				break;
			}
			
			case 5:{
				double media=calcularcalorias(rutaArchivo);
				ofstream archivoOperaciones("operaciones.txt");
				archivoOperaciones<<"Media de calorias quemadas en este mes: "<<media<<"kcal"<<endl;
				archivoOperaciones.close();
				cout<<"guardado correctamente."<<endl;
				cout<<"la media aritmetica de calorias quemadas en este mes es de: "<<media<<"kcal"<<endl;
				break;
			}
			
			case 6:{
				copiarcontenido(rutaArchivo, "resultado.txt");
				cout<<"El contenido se a copiado al documento resultado"<<endl;
				break;
			}
			
			case 7:
				cout<<"Sliendo del programa."<<endl;
				break;
				
			default:
				cout<<"Opcion invalida, intente de nuevo."<<endl;
		}
	}
	return 0;
}


