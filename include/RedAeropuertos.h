#ifndef REDAEROPUERTOS_H_INCLUDED
#define REDAEROPUERTOS_H_INCLUDED
#include <iostream>
#include "Grafo.h"
#include "Aeropuerto.h"
#include <vector>
#include <cassert>
#include <list>
#include <string>

using namespace std;

class RedAeropuertos
{
public:
class Vuelos{
public:
    Vuelos();
    ~Vuelos();
    Vuelos(bool cabotaje, float distancia);
    bool Cabotaje() const;
    float Distancia() const;
    void AgregarAerolinea(string aerolinea,int asientos);
    void ObtenerAerolineas(map<string,int> & aero)const;
    bool existeAerolinea(string aerolinea) const;
    int CantAsientos(string aerolinea) const;

private:
    bool cabotaje;
    float distancia;
    map<string,int> aerolineas;
};

    RedAeropuertos();
    ~RedAeropuertos();
    void AgregarAeropuerto(string nombre, string pais, string ciudad);
    void AgregarReserva(int origen,int destino, string aerolinea, int asientos);
    void AgregarVuelo(int origen, int destino, Vuelos infovuelo);
    void AeropuertosAdy(int origen ,vector<int> &aerop) const;
    void ObtenerReservas(map<int, map<int, map<string, int>>> & res) const;
    bool ExisteVuelo(int origen, int destino) const;
    bool ExisteReserva(int origen,int destino, string aeropuerto) const;
    const Vuelos ObtenerVuelos(int origen, int destino) const;
    void obtenerAerolineas(int origen, int destino, vector<string> &nombres)const;
    int asientosdispo(int origen, int destino, string aerolinea) const;
    int IdAeropuerto(string aeropuerto) const;
    string NombreAeropuerto(int aeropuerto) const;
    string CiudadAeropuerto(int aeropuerto) const;
    string PaisAeropuerto(int aeropuerto) const;
    int cantidadAeropuertos() const;
    float Distancia(int origen, int destino) const;

private:
    Grafo<Vuelos> RedVuelos;
    vector<Aeropuerto> aeropuertos;
    int CantAeropuertos;
    map<int,map<int,map<string,int>>> reservas;

};

//class vuelos

RedAeropuertos::Vuelos::Vuelos(){
}

RedAeropuertos::Vuelos::Vuelos(bool cabotaje, float distancia){
    this->cabotaje=cabotaje;
    this->distancia=distancia;
}

RedAeropuertos::Vuelos::~Vuelos(){
}

bool RedAeropuertos::Vuelos::Cabotaje() const{
    return this->cabotaje;
}

float RedAeropuertos::Vuelos::Distancia() const{
    return this->distancia;
}

void RedAeropuertos::Vuelos::AgregarAerolinea(string aerolinea,int asientos)
{
    aerolineas[aerolinea]=asientos;
}

void RedAeropuertos::Vuelos::ObtenerAerolineas(map<string,int> & aero)const{
    aero=this->aerolineas;
}

bool RedAeropuertos::Vuelos::existeAerolinea(string aerolinea) const{
    return (aerolineas.find(aerolinea)!=aerolineas.end());
}

int RedAeropuertos::Vuelos::CantAsientos(string aerolinea) const{
    return aerolineas.find(aerolinea)->second;
}

//class red aeropuertos

RedAeropuertos::RedAeropuertos(){
    CantAeropuertos=0;
}

RedAeropuertos::~RedAeropuertos(){
}

void RedAeropuertos::AgregarAeropuerto(string nombre, string pais, string ciudad){
    RedVuelos.agregar_vertice(CantAeropuertos);
    Aeropuerto a(nombre,ciudad,pais);
    aeropuertos.push_back(a);
    CantAeropuertos++;
}

void RedAeropuertos::AgregarReserva(int origen,int destino, string aerolinea, int asientos){
    if (RedVuelos.existe_arco(origen,destino)){
        reservas[origen][destino][aerolinea]=asientos;
    }
}

void RedAeropuertos::AgregarVuelo(int origen, int destino, Vuelos infovuelo){
    if (RedVuelos.existe_vertice(origen) && RedVuelos.existe_vertice(destino)){
        RedVuelos.agregar_arco(origen,destino,infovuelo);
        RedVuelos.agregar_arco(destino,origen,infovuelo);
    }
}

void RedAeropuertos::AeropuertosAdy(int origen,vector<int> &aerop) const{
    list<Grafo<Vuelos>::Arco> adyacentes;
    RedVuelos.devolver_adyacentes(origen, adyacentes);
    for (const auto &arco : adyacentes) {
        int aeropuertoID = arco.devolver_adyacente();
        aerop.push_back(aeropuertoID);
    }
}

void RedAeropuertos::ObtenerReservas(map<int, map<int, map<string, int>>> & res) const{
    res=reservas;
}

bool RedAeropuertos::ExisteVuelo(int origen, int destino)const {
    return (RedVuelos.existe_arco(origen, destino));
}

bool RedAeropuertos::ExisteReserva(int origen,int destino, string aerolinea)const{
    map<int,map<int,map<string,int>>>::const_iterator reservasOrigen = reservas.find(origen);
    if(reservasOrigen != reservas.end()){
        map<int,map<string,int>>::const_iterator reservasDestino = (*reservasOrigen).second.find(destino);
        if(reservasDestino != reservasOrigen->second.end()){
            map<string,int>::const_iterator reservasAerolinea = (*reservasDestino).second.find(aerolinea);
            if (reservasAerolinea != reservasDestino->second.end())
                return true;
        }
    }
    return false;
}

const RedAeropuertos::Vuelos RedAeropuertos::ObtenerVuelos(int origen, int destino) const{
    return RedVuelos.costo_arco(origen, destino);
}

void RedAeropuertos::obtenerAerolineas(int origen, int destino, vector<string> &nombresAerolineas) const //checkear esto, pq la clase vuelo tiene uno tmb
{
    nombresAerolineas.clear();
    RedAeropuertos::Vuelos vuelo = ObtenerVuelos(origen,destino);
    map<string,int> aerolineas;
    vuelo.ObtenerAerolineas(aerolineas);
    map<string,int>::iterator it = aerolineas.begin();
    while (it != aerolineas.end()){
        nombresAerolineas.push_back(it->first);
        it++;
    }
}

int RedAeropuertos::asientosdispo(int origen, int destino, string aerolinea) const{
    if (ExisteVuelo(origen,destino)){
        Vuelos infovuelos=ObtenerVuelos(origen,destino);
        if (infovuelos.existeAerolinea(aerolinea)){
            map<string,int> mapa;
            infovuelos.ObtenerAerolineas(mapa);
            int asientos=mapa.find(aerolinea)->second;
            if (ExisteReserva(origen,destino,aerolinea)){
                int reservados= reservas.find(origen)->second.find(destino)->second.find(aerolinea)->second;
                return asientos-reservados;
            }else{
                return asientos;
            }
        }
    }
    return -1;
}

int RedAeropuertos::IdAeropuerto(string aeropuerto) const{
        for(int i = 0; i < aeropuertos.size(); i++){
        if (aeropuertos[i].Nombre()==aeropuerto){
            return i;
        }
    }
    bool existe=false;
    assert(existe);
}

string RedAeropuertos::NombreAeropuerto(int aeropuerto) const{
    if (aeropuerto>=0 && aeropuerto<CantAeropuertos){
    return aeropuertos[aeropuerto].Nombre();
    }
}

string RedAeropuertos::CiudadAeropuerto(int aeropuerto) const{
    if (aeropuerto>=0 && aeropuerto<CantAeropuertos){
    return aeropuertos[aeropuerto].Ciudad();
    }
}

string RedAeropuertos::PaisAeropuerto(int aeropuerto) const{
    if (aeropuerto>=0 && aeropuerto<CantAeropuertos){
    return aeropuertos[aeropuerto].Pais();
    }
}

int RedAeropuertos::cantidadAeropuertos() const{
    return CantAeropuertos;
}

float RedAeropuertos::Distancia(int origen, int destino) const{
    Vuelos infovuelo=ObtenerVuelos(origen,destino);
    return infovuelo.Distancia();
}

#endif // REDAEROPUERTOS_H_INCLUDED
