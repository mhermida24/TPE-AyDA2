#include <iostream>
#include <fstream>
#include <vector>
#include<string>
#include <utility>
#include<limits>
#include "include/RedAeropuertos.h"
#include "include/Aeropuerto.h"

using namespace std;

void cargar_aeropuertos(string path, RedAeropuertos &red);
void cargar_reservas(string path, RedAeropuertos &red);
void cargar_aeropuertos_rutas(string path, RedAeropuertos::Vuelos & vuelo);
void cargar_rutas(string path, RedAeropuertos &red);

void menu(RedAeropuertos & red);

void listarAeropuertos(const RedAeropuertos &red);

void listarReservas(const RedAeropuertos &red);

void listarAerolineas(const RedAeropuertos &red, int origen, int destino, string & aerolinea);

void servicio1(RedAeropuertos & red,int origen, int destino, string aerolinea);

void servicio2(RedAeropuertos & red, int origen, int destino);
void dfs(RedAeropuertos & red, int origen, int  destino, vector<pair<string,vector<int>>> & caminos, vector<int> caminoactual,bool visitados[],string aerolinea, float km);

void servicio3(RedAeropuertos & red);
bool valido(RedAeropuertos & red, int actual,int siguiente, vector<bool> visitados,int distanciaActual,int distanciaFinal);
void solServicio3(RedAeropuertos & red,int AeropSalida,int aeropLlegada, vector<bool> visitados, int cantVisitados, int km, int & kmFinal,vector <int> solucionAux, vector <int> & solucionFinal);


int main()
{
    RedAeropuertos red;
    cargar_aeropuertos("datasets/Aeropuertos2.txt", red);
    cargar_rutas("datasets/Rutas2.txt", red);
    cargar_reservas("datasets/Reservas2.txt", red);

    menu(red);

    return 0;
}


void cargar_aeropuertos(string path, RedAeropuertos &red)
{
    ifstream origen(path.c_str());
    if (!origen.is_open())
        cout << "No se pudo abrir el archivo: " << path << endl;
    else {
        //cout << "AEROPUERTOS " << endl;
        //cout << "------------------------" << endl;
        while (!origen.eof()) {
            string linea;
            getline(origen,linea);
            size_t primera_pos = linea.find(',');
            string nombre_aeropuerto = linea.substr(0, primera_pos);
            size_t segunda_pos = linea.find(',', primera_pos + 1);
            string nombre_ciudad = linea.substr(primera_pos + 1, segunda_pos - primera_pos - 1);
            string pais = linea.substr(segunda_pos + 1);
            red.AgregarAeropuerto(nombre_aeropuerto,pais,nombre_ciudad);
            //cout <<nombre_aeropuerto << " - " << nombre_ciudad << " - " << pais << endl;
        }
    }
}

void cargar_aerolineas_rutas(string aerolineas, RedAeropuertos::Vuelos &vuelo)
{
    //Se elimina la llave inicial
    aerolineas = aerolineas.substr(1);
    size_t inicial = 0;
    size_t pos = 0;
    size_t pos_final = aerolineas.find('}');
    while ((pos != std::string::npos) && (pos + 1 < pos_final)) {
        pos = aerolineas.find(',', inicial);
        string dato_aerolinea = aerolineas.substr(inicial, pos - inicial);
        size_t pos_separador = dato_aerolinea.find('-');
        string aerolinea = dato_aerolinea.substr(0, pos_separador);
        string asientos_texto = dato_aerolinea.substr(pos_separador + 1);
        int asientos = atoi(asientos_texto.c_str());

        //cout <<"[ " << aerolinea << " - " << asientos << " ]" << endl;
        inicial = pos + 1;

        vuelo.AgregarAerolinea(aerolinea,asientos);
    }
}

void cargar_rutas(string path, RedAeropuertos & red)
{
    ifstream origen(path.c_str());
    if (!origen.is_open()){
        cout << "No se pudo abrir el archivo: " << path << endl;
    }else {
        //cout << "RUTAS " << endl;
        //cout << "------------------------" << endl;
        while (!origen.eof()) {
            string linea;
            getline(origen,linea);
            size_t primera_pos = linea.find(',');
            string nombre_aeropuerto_origen = linea.substr(0, primera_pos);

            size_t segunda_pos = linea.find(',', primera_pos + 1);
            string nombre_aeropuerto_destino = linea.substr(primera_pos + 1, segunda_pos - primera_pos - 1);

            size_t tercera_pos = linea.find(',', segunda_pos + 1);
            string distancia_texto = linea.substr(segunda_pos + 1, tercera_pos - segunda_pos - 1);
            double distancia = atof(distancia_texto.c_str());

            size_t cuarta_pos = linea.find(',', tercera_pos + 1);
            string cabotaje_texto = linea.substr(tercera_pos + 1, cuarta_pos - tercera_pos - 1);
            bool cabotaje_bool = (cabotaje_texto == "1");
            string aerolineas = linea.substr(cuarta_pos + 1);
            RedAeropuertos::Vuelos vuelo(cabotaje_bool, distancia);

            //cout << nombre_aeropuerto_origen << " - " << nombre_aeropuerto_destino << " - " << distancia << " - "
               // << cabotaje_texto << " - ";

            cargar_aerolineas_rutas(aerolineas, vuelo);
            int origen = red.IdAeropuerto(nombre_aeropuerto_origen);
            int destino = red.IdAeropuerto(nombre_aeropuerto_destino);
            red.AgregarVuelo(origen,destino ,vuelo);
        }
    }
}

void cargar_reservas(string path, RedAeropuertos & red)
{
    ifstream origen(path.c_str());
    if (!origen.is_open()){
        //cout << "No se pudo abrir el archivo: " << path << endl;
    }else {
        //cout << "RESERVAS " << endl;
        //cout << "------------------------" << endl;
        while (!origen.eof()) {
            string linea;
            getline(origen,linea);
            size_t primera_pos = linea.find(',');
            string nombre_aeropuerto_origen = linea.substr(0, primera_pos);

            size_t segunda_pos = linea.find(',', primera_pos + 1);
            string nombre_aeropuerto_destino = linea.substr(primera_pos + 1, segunda_pos - primera_pos - 1);

            size_t tercera_pos = linea.find(',', segunda_pos + 1);
            string aerolinea = linea.substr(segunda_pos + 1, tercera_pos - segunda_pos - 1);

            string asientos_reservados_texto = linea.substr(tercera_pos + 1);
            int asientos_reservados = atoi(asientos_reservados_texto.c_str());

           // cout <<nombre_aeropuerto_origen << " - " << nombre_aeropuerto_destino << " - " << aerolinea
             //   << " - " << asientos_reservados << endl;

            int origen=red.IdAeropuerto(nombre_aeropuerto_origen);
            int destino=red.IdAeropuerto(nombre_aeropuerto_destino);
            red.AgregarReserva(origen,destino,aerolinea,asientos_reservados);
        }
    }
}

void menu(RedAeropuertos & red){
        int opcion;
    do {
        cout << "Menu:" <<endl;
        cout << "1. Listar todos los aeropuertos." <<endl;
        cout << "2. Listar todas las reservas realizadas." <<endl;
        cout << "3. Verificar vuelo directo entre 2 aeropuertos." <<endl;
        cout << "4. Obtener vuelos de la misma aerolinea, directos o con escalas para 2 aeropuertos" <<endl;
        cout << "5. Circuito de aeropuertos." <<endl;
        cout << "0. Salir." <<endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:{
                cout<<"Listado de aeropuertos:"<<endl;
                listarAeropuertos(red);
            }
                break;
            case 2:{
                cout << "Listado de Reservas:" << endl;
                listarReservas(red);
            }
                break;
            case 3:{
                int origen;
                int destino;
                string aerolinea;
                cout<<"Aeropuertos disponibles:"<<endl;
                listarAeropuertos(red);
                cout<<"Ingrese el numero correspondiente al aeropuerto origen"<<endl;
                cin>>origen;
                cout<<"Ingrese el numero correspondiente al aeropuerto destino"<<endl;
                cin>>destino;
                listarAerolineas(red, origen, destino, aerolinea);
                servicio1(red,origen,destino,aerolinea);
            }
                break;
            case 4:{
                int origen;
                int destino;
                cout<<"Aeropuertos disponibles:"<<endl;
                listarAeropuertos(red);
                cout<<"Ingrese aeropuerto origen"<<endl;
                cin>>origen;
                cout<<"Ingrese aeropuerto destino"<<endl;
                cin>>destino;
                servicio2(red,origen,destino);
            }
                break;
            case 5:
                servicio3(red);
                break;
            default:
                cout << "Opcion no valida" <<endl;
        }
    } while (opcion != 0);
}

void listarAeropuertos(const RedAeropuertos &red){
    for (int i=0;i<red.cantidadAeropuertos();i++){
        cout<<i<<". "<<red.NombreAeropuerto(i)<<", "<< red.CiudadAeropuerto(i) <<", "<< red.PaisAeropuerto(i)<<endl;
    }
}

void listarReservas(const RedAeropuertos &red){
    map<int, map<int, map<string, int>>> reservas;
    red.ObtenerReservas(reservas);
    for (const auto &origenDestino : reservas) {
        int origen = origenDestino.first;
        for (const auto &destinoAerolineas : origenDestino.second) {
            int destino = destinoAerolineas.first;
            for (const auto &aerolineaAsientos : destinoAerolineas.second) {
                string aerolinea = aerolineaAsientos.first;
                int asientos = aerolineaAsientos.second;
                cout << "Origen: " << red.NombreAeropuerto(origen) <<", "<< red.CiudadAeropuerto(origen) <<", "<< red.PaisAeropuerto(origen)<< endl;
                cout << "Destino: " << red.NombreAeropuerto(destino) <<", "<< red.CiudadAeropuerto(destino) <<", "<< red.PaisAeropuerto(destino)<< endl;
                cout << "Aerolinea: " << aerolinea << endl;
                cout << "Asientos Reservados: " << asientos << endl;
                cout << "-----------------------------" << endl;
            }
        }
    }
}

void listarAerolineas(const RedAeropuertos &red, int origen, int destino, string & aerolinea){
    if (red.ExisteVuelo(origen,destino)){
        cout<<"Ingrese con que aerolinea desea viajar"<<endl;
        vector<string> aerolineas;
        red.obtenerAerolineas(origen,destino, aerolineas);
        for (int i = 0; i < aerolineas.size(); i++){
            cout<<aerolineas[i];
            if (i < aerolineas.size()-1) {
                            cout<<", ";
            }
        }
        cout<<endl;
        cin>>ws;
        getline(cin,aerolinea);
    }
}

void servicio1(RedAeropuertos & red,int origen, int destino, string aerolinea){
    string nombre= "servicio_1.txt";
    ofstream archivo(nombre);
    string texto;
    if (red.ExisteVuelo(origen,destino)){
        int asient=red.asientosdispo(origen,destino,aerolinea);
        if (asient!=-1){
            float distancia=red.Distancia(origen,destino);
            texto+= "La distancia entre: " + red.NombreAeropuerto(origen)+", " + red.CiudadAeropuerto(origen) + ", "+ red.PaisAeropuerto(origen)+  " y " + red.NombreAeropuerto(destino) +", " + red.CiudadAeropuerto(destino) + ", "+ red.PaisAeropuerto(destino)+ " es de " + to_string(distancia) + " y para la aerolinea " + aerolinea + " hay " + to_string(asient) + " asientos disponibles";
        }else{
            texto+="La aerolinea no existe";
        }
    }else{
        texto+="No hay un viaje entre estos aeropuertos";
    }
    cout<<texto<<endl;
    archivo<<texto;
    archivo.close();
}

void servicio2(RedAeropuertos & red, int origen, int destino){
    vector<int>  caminoac;
    vector<pair<string,vector<int>>> caminos;
    float km=0;
    int cant=red.cantidadAeropuertos();
    bool visitados[cant];
    for (int i=0;i<cant;i++){
        visitados[i]=false;
    }
        string aerolinea;
        dfs(red, origen, destino, caminos, caminoac,visitados, aerolinea, km);
        string nombre= "servicio_2.txt";
        ofstream archivo(nombre);
        string texto;
        string aero1=red.NombreAeropuerto(origen);
        string aero2=red.NombreAeropuerto(destino);
        if(caminos.empty()){
            texto+="No existen caminos para ir desde " + aero1 + " hacia " + aero2;
        }else{
            texto+="Para ir desde " + aero1 + " hacia " + aero2 + " se pueden seguir los siguientes caminos: \n\n";
            for (const auto &camino : caminos) {
                string aerolinea = camino.first;
                vector<int> nodos = camino.second;
                texto+="Aerolinea: "+aerolinea+"\n";
                if ((nodos.size())<4){
                    texto+="vuelo directo \n";
                }else{
                    texto+="Cantidad de escalas: "+ to_string(nodos.size()-3)+ "\n";
                }
                for (int i=0;i<nodos.size()-1;i++){
                    texto+=red.NombreAeropuerto(nodos[i])+", " + red.CiudadAeropuerto(nodos[i]) + ", "+ red.PaisAeropuerto(nodos[i]);
                    if (i < nodos.size() - 2) {
                        texto+=" -> ";
                    }
                }
                texto+= "\ncantidad de kilometros: "+to_string(nodos[nodos.size()-1])+"\n";
                texto+= "-------------------------------------\n";
            }
        }
    cout<<texto<<endl;
    archivo<<texto;
    archivo.close();
}

void dfs (RedAeropuertos & red, int origen, int  destino, vector<pair<string,vector<int>>> & caminos, vector<int> caminoactual,bool visitados[],string aerolinea, float km) {
    visitados[origen]= true;
    caminoactual.push_back(origen);
    if (origen == destino) {
        caminoactual.push_back(km); //guardo cantidad km en ultima posicion
        caminos.push_back(make_pair(aerolinea, caminoactual));
    }else{
        vector<int> adyacentes;
        red.AeropuertosAdy(origen, adyacentes);
        for (int ady : adyacentes) {
            if (!visitados[ady]){
                RedAeropuertos::Vuelos vuelo = red.ObtenerVuelos(origen, ady);
                if (aerolinea.empty()){
                    map<string, int> aerolineasDisponibles;
                    vuelo.ObtenerAerolineas(aerolineasDisponibles);
                    for (const auto &aero : aerolineasDisponibles) {
                        string nuevaAerolinea = aero.first;
                        if (red.asientosdispo(origen, ady, nuevaAerolinea) > 0) {
                            dfs(red, ady, destino, caminos, caminoactual, visitados, nuevaAerolinea,km+vuelo.Distancia());
                        }
                }
                }else{
                    if (vuelo.existeAerolinea(aerolinea)){
                        if (red.asientosdispo(origen, ady, aerolinea)> 0){
                            dfs(red, ady, destino, caminos, caminoactual,visitados ,aerolinea,km+vuelo.Distancia());
                        }
                    }
                }
            }
        }

    }
    visitados[origen] = false;
    caminoactual.pop_back();
}

void servicio3(RedAeropuertos & red){
    int cantAerop = red.cantidadAeropuertos();
    vector<bool> visitados (cantAerop,false);
    vector<int> solucionAux;
    vector<int> solucionFinal;
    int distanciaFinal= numeric_limits<int>::max();
    for (int i = 0 ; i < cantAerop; i++){
        solServicio3(red, i, i, visitados, 1, 0, distanciaFinal, solucionAux, solucionFinal);
    }
    string nombre= "servicio_3.txt";
    ofstream archivo(nombre);
    string texto;
    if (solucionFinal.empty()){
        texto= "No se encontro circuito que recorra todos los aeropuertos y vuelva al mismo de origen\n";
    }else{
        texto= "El circuito que recorre todos los aeropuertos es: \n";
        texto+= red.NombreAeropuerto(solucionFinal.back()) + " -> ";
        for (int aeropuerto : solucionFinal){
            texto+= red.NombreAeropuerto(aeropuerto) + " -> ";
        }
        texto.erase(texto.size()-4,4);
        texto+= "\n se recorren " + to_string(distanciaFinal) + "km.\n";
    }
    cout<<texto;
    archivo<<texto;
}

bool valido(RedAeropuertos & red, int actual,int siguiente, vector<bool> visitados,int distanciaActual,int distanciaFinal){
    if (!visitados[siguiente]){
        int distancia = red.Distancia(actual,siguiente);
        if (distanciaActual + distancia < distanciaFinal){
            return true;
        }
    }
    return false;
}

void solServicio3(RedAeropuertos & red,int AeropSalida, int aeropLlegada, vector<bool> visitados, int cantVisitados, int km, int & kmFinal,vector <int> solucionAux, vector <int> & solucionFinal){
    if((cantVisitados == red.cantidadAeropuertos()+1) && AeropSalida == aeropLlegada){
        if(km < kmFinal){
            kmFinal = km;
            solucionFinal = solucionAux;
        }
    }else{
        vector<int> adyacentes;
        red.AeropuertosAdy(AeropSalida, adyacentes);
        for (int ady : adyacentes){
            if (valido(red,AeropSalida,ady,visitados,km,kmFinal)){
                visitados[ady]=true;
                solucionAux.push_back(ady);
                int a=red.Distancia(AeropSalida,ady);
                solServicio3(red,ady,aeropLlegada,visitados,cantVisitados+1,km+a,kmFinal,solucionAux,solucionFinal);
                visitados[ady]=false;
                solucionAux.pop_back();
            }
        }
    }
}
